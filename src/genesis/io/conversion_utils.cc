#include "src/genesis/io/conversion_utils.h"

#include <glog/logging.h>
#include <stdint.h>
#include <fstream>
#include <iostream>

#include "src/genesis/visualization/image_viewer.h"

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

void ConvertImageToNetInput(Image* image) {
  ScaleImage(image, kNNImageWidth, kNNImageHeight);
  NormalizeAndSubtractMean(image);
}

caffe::Datum ProtoToDatum(const proto::LeapFrame& proto) {
  caffe::Datum datum;

  bool has_hand = proto.has_hand_pose();
  datum.set_label(has_hand ? 1 : 0);

  datum.set_channels(1);

  Image scaled(proto.left().data().data(),
               proto.left().width(), proto.left().height());
  ConvertImageToNetInput(&scaled);

  int scaled_w = scaled.width();
  int scaled_h = scaled.height();

  datum.set_width(scaled_w);
  datum.set_height(scaled_h);

  datum.mutable_float_data()->Resize(scaled_w * scaled_h, 0);
  std::copy(scaled.begin(), scaled.end(), datum.mutable_float_data()->begin());

  static ImageViewer dbg("ProtoToDatum", scaled_w, scaled_h);
  dbg.UpdateNormalized(scaled);

  return datum;
}

int ExtractLabel(const Leap::Frame& frame) {
#if 1
  int label = 0;
  Leap::HandList hands = frame.hands();
  for (auto hl = hands.begin(); hl != hands.end(); hl++) {
    Leap::Hand hand = *hl;
    if (hand.isLeft()) {
      label = 1;
      break;
    }
  }
#else
  int label = (frame.hands().Count() > 0 ? 1 : 0);
#endif
  return label;
}

}  // namespace genesis
