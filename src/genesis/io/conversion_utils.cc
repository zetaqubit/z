#include "src/genesis/io/conversion_utils.h"

#include <glog/logging.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <valarray>

#include "src/genesis/visualization/image_viewer.h"

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
std::vector<float> NormalizeAndSubtractMean(const float* array, int length) {
  std::vector<float> output(length);
  double sum = 0;
  for (int i = 0; i < length; i++) {
    sum += array[i];
  }
  float mean = static_cast<float>(sum / length);

  for (int i = 0; i < length; i++) {
    output[i] = (array[i] - mean) / 255.0f;
  }
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
  std::vector<float> normalized_pixels =
      NormalizeAndSubtractMean(intensity, width * height);

  static ImageViewer dbg("ProtoToDatum", 128, 128);

  const bool DOWNSAMPLE = true;
  if (DOWNSAMPLE) {
    float x_scale = width / 28.0f;
    float y_scale = height / 28.0f;
    datum.set_width(28);
    datum.set_height(28);

    uint8_t pixels[28 * 28];
    for (int r = 0; r < 28; r++) {
      for (int c = 0; c < 28; c++) {
        int r_s = r * y_scale;
        int c_s = c * x_scale;
        float scaled_pixel = normalized_pixels[c_s + r_s * width];
        pixels[c + r * 28] = static_cast<uint8_t>(128 * (1.0f + scaled_pixel));
        datum.add_float_data(scaled_pixel);
      }
    }
    dbg.Update(pixels, 28, 28);
    //datum.set_float_data(pixels, 28 * 28);
  } else {
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
  }

  return datum;
}

}  // namespace genesis
