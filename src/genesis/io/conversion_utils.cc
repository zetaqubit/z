#include "src/genesis/io/conversion_utils.h"

#include <stdint.h>
#include <fstream>
#include <iostream>

#include "src/genesis/visualization/image_viewer.h"
#include "src/third_party/glog/src/glog/logging.h"

using std::ios;
using std::fstream;
using std::string;

namespace {

// Converts an array of values in range [0, 256) to a normalized range [0, 1),
// and then subtract the mean from each value.
void NormalizeAndSubtractMean(genesis::Image* img) {
  *img /= 256.0f;
  float mean = img->mean();
  *img -= mean;
}

void ScaleImage(genesis::Image* img, int scaled_w, int scaled_h) {
  // Experiment with cropping and keeping only the center region of image.
  //int x_bound = (orig_w + scaled_w) / 4;
  //int y_bound = (orig_h + scaled_h) / 4;
  //img.crop(x_bound, y_bound, 0, 0, orig_w - x_bound, orig_h - y_bound, 1, 1);

  img->resize(scaled_w, scaled_h, 1 /* size_z */, 1 /* size_c */,
              5 /* cubic interpolation */);
}

genesis::proto::Pose LeapVectorToProto(const Leap::Vector& vector) {
  genesis::proto::Pose pose;
  pose.set_x(vector.x);
  pose.set_y(vector.y);
  pose.set_z(vector.z);
  return pose;
}

}  // namespace

namespace genesis {

std::unique_ptr<proto::LeapFrame> ReadProto(const string& filename) {
  fstream input(filename, ios::in | ios::binary);
  if (!input) {
    LOG(INFO) << filename << ": File not found";
    return nullptr;
  }
  std::unique_ptr<proto::LeapFrame> proto(new proto::LeapFrame());
  if (!proto->ParseFromIstream(&input)) {
    LOG(ERROR) << "Failed to parse Leap frame proto.";
    return nullptr;
  }
  return proto;
}

bool WriteProto(const string& filename, const proto::LeapFrame& proto) {
  fstream output(filename, ios::out | ios::trunc | ios::binary);
  if (!output) {
    LOG(ERROR) << "Could not open " << filename << " for writing.";
    return false;
  }
  if (!proto.SerializeToOstream(&output)) {
    LOG(ERROR) << "Failed to write Leap frame proto.";
    return false;
  }
  return true;
}

const Leap::Vector ProjectToScreenUndistorted(const Leap::Vector& p,
                                              const Leap::Image& image) {
  // Convert world position to a ray from the camera POV
  float horizontal_slope = -(p.x + (image.id() == 0 ? -20 : 20)) / p.y;
  float vertical_slope = p.z / p.y;

  // Normalize ray from [-4..4] to [0..1] (the inverse of how the undistorted
  // image was drawn earlier)
  Leap::Vector ndc(
      horizontal_slope * image.rayScaleX() + image.rayOffsetX(),
      vertical_slope   * image.rayScaleY() + image.rayOffsetY(), 0);

  return ndc;
}

const Leap::Vector ProjectToScreenDistorted(const Leap::Vector& p,
                                            const Leap::Image& image) {
  // Convert world position to a ray from the camera POV
  float h_slope = -(p.x + (image.id() == 0 ? -20 : 20)) / p.y;
  float v_slope = p.z / p.y;

  Leap::Vector ndc = image.warp(Leap::Vector(h_slope, v_slope, 0));
  ndc.x /= image.width();
  ndc.y /= image.height();
  return ndc;
}

proto::KeyPoint ExtractKeyPoint(const Leap::Vector& position,
                                const Leap::Frame& frame) {
  proto::KeyPoint key_point;
  *key_point.mutable_world_pose() = LeapVectorToProto(position);

  // Project the world pose into the left and right images.
  Leap::Vector left_coords = ProjectToScreenDistorted(
      position, frame.images()[0]);
  key_point.mutable_left_screen_coords()->set_u(left_coords.x);
  key_point.mutable_left_screen_coords()->set_v(left_coords.y);

  Leap::Vector right_coords = ProjectToScreenDistorted(
      position, frame.images()[1]);
  key_point.mutable_right_screen_coords()->set_u(right_coords.x);
  key_point.mutable_right_screen_coords()->set_v(right_coords.y);
  return key_point;
}

proto::Hand HandToProto(const Leap::Hand& hand, const Leap::Frame& frame) {
  proto::Hand proto;
  if (hand.isLeft()) {
    proto.set_identity(proto::Hand_Identity_LEFT);
  } else if (hand.isRight()) {
    proto.set_identity(proto::Hand_Identity_RIGHT);
  }

  *proto.mutable_palm() = ExtractKeyPoint(hand.palmPosition(), frame);
  proto::KeyPoint* mutable_fingers[] = {
    proto.mutable_thumb(), proto.mutable_index(), proto.mutable_middle(),
    proto.mutable_ring(), proto.mutable_pinky()
  };
  for (int i = 0; i < hand.fingers().count(); i++) {
    Leap::Finger finger = hand.fingers()[i];
    Leap::Bone tip = finger.bone(Leap::Bone::TYPE_DISTAL);
    if (tip.isValid()) {
      *mutable_fingers[i] = ExtractKeyPoint(tip.center(), frame);
    }
  }

  return proto;
}

proto::Image ImageToProto(const Leap::Image& image) {
  int w = image.width(), h = image.height();

  proto::Image proto;
  proto.set_width(w);
  proto.set_height(h);

  const uint8_t* data = image.data();
  proto.mutable_data()->Resize(w * h, 0);
  std::copy(data, data + w * h, proto.mutable_data()->begin());
  return proto;
}

proto::LeapFrame FrameToProto(const Leap::Frame& frame) {
  proto::LeapFrame leap_frame;

  leap_frame.set_timestamp_ms(frame.timestamp());

  // Update image and distortion textures.
  Leap::Image left = frame.images()[0];
  if (left.width() > 0) {
    *leap_frame.mutable_left_image() = ImageToProto(left);
  }
  Leap::Image right = frame.images()[1];
  if (right.width() > 0) {
    *leap_frame.mutable_right_image() = ImageToProto(right);
  }

  bool has_left_hand = false, has_right_hand = false;
  for (int i = 0; i < frame.hands().count(); i++) {
    Leap::Hand hand = frame.hands()[i];
    if (!hand.isValid()) {
      continue;
    }
    if (hand.isLeft() && !has_left_hand) {
      *leap_frame.mutable_left_hand() = HandToProto(hand, frame);
      has_left_hand = true;
    }
    if (hand.isRight() && !has_right_hand) {
      *leap_frame.mutable_right_hand() = HandToProto(hand, frame);
      has_right_hand = true;
    }
  }

  return leap_frame;
}

void ConvertImageToNetInput(Image* image) {
  ScaleImage(image, kNNImageWidth, kNNImageHeight);
  NormalizeAndSubtractMean(image);
}

static void SerializeKeyPoint(const proto::KeyPoint& key_point,
                              std::vector<float>* output) {
  output->push_back(key_point.world_pose().x());
  output->push_back(key_point.world_pose().y());
  output->push_back(key_point.world_pose().z());
  output->push_back(key_point.left_screen_coords().u());
  output->push_back(key_point.left_screen_coords().v());
  output->push_back(key_point.right_screen_coords().u());
  output->push_back(key_point.right_screen_coords().v());
}

static void SerializeKeyPointAsHeatmap(const proto::KeyPoint& key_point,
                                       std::vector<float>* output,
                                       ImageViewer* heatmap_viewer = nullptr) {
  // Serialize palm position as 16x16 heatmap.
  Image image(kHeatmapWidth, kHeatmapHeight, 1, 1, 0);
  if (key_point.has_left_screen_coords()) {
    float u = key_point.left_screen_coords().u(),
          v = key_point.left_screen_coords().v();
    float color = 1.0f;
    image.draw_gaussian(u * kHeatmapWidth, v * kHeatmapHeight, 1.0f /* sigma */,
                        &color);
  }
  output->insert(output->end(), image.data(),
                 image.data() + kHeatmapWidth * kHeatmapHeight);
  if (heatmap_viewer) {
    heatmap_viewer->UpdateNormalized(image);
  }
}

void SerializeHand(const proto::Hand& hand, std::vector<float>* output) {
#if 0
  SerializeKeyPoint(hand.palm(), output);
  SerializeKeyPoint(hand.thumb(), output);
  SerializeKeyPoint(hand.index(), output);
  SerializeKeyPoint(hand.middle(), output);
  SerializeKeyPoint(hand.ring(), output);
  SerializeKeyPoint(hand.pinky(), output);
#else

  static ImageViewer heatmap("Heatmap", kHeatmapWidth, kHeatmapHeight);

  SerializeKeyPointAsHeatmap(hand.palm(), output, &heatmap);
  //SerializeKeyPointAsHeatmap(hand.thumb(), output, &heatmap);
  //SerializeKeyPointAsHeatmap(hand.index(), output, &heatmap);
  //SerializeKeyPointAsHeatmap(hand.middle(), output, &heatmap);
  //SerializeKeyPointAsHeatmap(hand.ring(), output, &heatmap);
  //SerializeKeyPointAsHeatmap(hand.pinky(), output, &heatmap);
  heatmap.EndFrame();
#endif

}

std::vector<float> SerializeInputToNN(const proto::LeapFrame& proto) {
  std::vector<float> input_vector;

  // Serialize the image.
  Image scaled(proto.left_image().data().data(),
               proto.left_image().width(), proto.left_image().height());
  ConvertImageToNetInput(&scaled);
  input_vector.resize(scaled.width() * scaled.height());
  std::copy(scaled.begin(), scaled.end(), input_vector.begin());

  // Serialize the hand.
  SerializeHand(proto.left_hand(), &input_vector);

  // Debug visualization.
  static ImageViewer dbg("ProtoToDatum", scaled.width(), scaled.height());
  dbg.UpdateNormalized(scaled);
  if (proto.has_left_hand()) {
    dbg.DrawHand(proto.left_hand(), LEFT_IMAGE);
  }
  dbg.EndFrame();

  return input_vector;
}

caffe::Datum ProtoToDatum(const proto::LeapFrame& proto) {
  caffe::Datum datum;

  std::vector<float> input = SerializeInputToNN(proto);
  datum.set_channels(input.size());
  datum.set_width(1);
  datum.set_height(1);
  datum.set_label(proto.has_left_hand() ? 1 : 0);

  // Copy the data into Datum.
  datum.mutable_float_data()->Resize(input.size(), 0);
  std::copy(input.begin(), input.end(), datum.mutable_float_data()->begin());

  return datum;
}

}  // namespace genesis
