#include "src/genesis/io/conversion_utils.h"

#include <glog/logging.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <valarray>

#include "src/genesis/visualization/image_viewer.h"
#include "src/third_party/cimg/CImg.h"

using cimg_library::CImg;
using std::ios;
using std::fstream;
using std::string;

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

proto::Image ConvertImageToProto(const Leap::Image& image) {
  proto::Image proto;
  proto.set_width(image.width());
  proto.set_height(image.height());

  for (int r = 0; r < image.height(); r++) {
    for (int c = 0; c < image.width(); c++) {
      uint8_t pixel = image.data()[c + r * image.width()];
      proto.add_data(pixel);
    }
  }
  return proto;
}

// Converts an array of values in range [0, 255] to a normalized range [0, 1],
// and then subtract the mean from each value.
std::vector<float> NormalizeAndSubtractMean(const std::vector<float>& array) {
  std::vector<float> output(array.size());
  double sum = 0;
  for (int i = 0; i < array.size(); i++) {
    sum += array[i];
  }
  float mean = static_cast<float>(sum / array.size());

  for (int i = 0; i < array.size(); i++) {
    output[i] = (array[i] - mean) / 255.0f;
  }
  return output;
}

std::vector<float> ScaleImage(const std::vector<float>& orig, int orig_w,
                              int orig_h, int scaled_w, int scaled_h) {

#if 0
  std::vector<float> output(scaled_w * scaled_h);
  // Naive quantized sampling.
  float x_scale = orig_w / static_cast<float>(scaled_w);
  float y_scale = orig_h / static_cast<float>(scaled_h);
  for (int r = 0; r < scaled_h; r++) {
    for (int c = 0; c < scaled_w; c++) {
      int r_s = r * y_scale;
      int c_s = c * x_scale;
      output[c + r * scaled_w] = orig[c_s + r_s * orig_w];
    }
  }
  return output;
#else
  CImg<float> img(orig.data(), orig_w, orig_h);

  // Experiment with cropping and keeping only the center region of image.
  //int x_bound = (orig_w + scaled_w) / 4;
  //int y_bound = (orig_h + scaled_h) / 4;
  //img.crop(x_bound, y_bound, 0, 0, orig_w - x_bound, orig_h - y_bound, 1, 1);

  img.resize(scaled_w, scaled_h, 1 /* size_z */, 1 /* size_c */,
             5 /* cubic interpolation */);
  return std::vector<float>(img.data(), img.data() + img.size());
#endif
}

std::vector<float> ConvertImageToNetInput(const float* frame, int width,
                                          int height) {
  std::vector<float> orig(frame, frame + width * height);
  std::vector<float> scaled = ScaleImage(orig, width, height, 28, 28);
  std::vector<float> output = NormalizeAndSubtractMean(scaled);
  return output;
}

caffe::Datum ProtoToDatum(const proto::LeapFrame& proto) {
  caffe::Datum datum;

  bool has_hand = proto.has_hand_pose();
  datum.set_label(has_hand ? 1 : 0);

  datum.set_channels(1);

  int width = proto.left().width();
  int height = proto.left().height();

  const float* intensity = proto.left().data().data();
  auto scaled = ConvertImageToNetInput(intensity, width, height);

  datum.set_width(28);
  datum.set_height(28);

  for (int i = 0; i < 28 * 28; i++) {
    datum.add_float_data(scaled[i]);
  }

  static ImageViewer dbg("ProtoToDatum", 128, 128);
  dbg.UpdateNormalized(scaled.data(), 28, 28);

#if 0
  datum.set_width(width);
  datum.set_height(height);

  const bool WRITE_FLOAT_DATA  = false;
  if (WRITE_FLOAT_DATA) {
    //datum.mutable_float_data()->CopyFrom(normalized_pixels.data());
  } else {
    uint8_t* pixels = new uint8_t[width * height];
    for (int i = 0; i < width * height; i++) {
      pixels[i] = proto.left().data().data()[i];
    }
    datum.set_data(pixels, width * height);
    delete[] pixels;
  }
#endif

  return datum;
}

}  // namespace genesis
