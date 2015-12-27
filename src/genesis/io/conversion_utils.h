#ifndef SRC_GENESIS_IO_CONVERSION_UTILS_H_
#define SRC_GENESIS_IO_CONVERSION_UTILS_H_

#include <memory>
#include <string>

#include "src/genesis/io/proto/leap_frame.pb.h"
#include "src/third_party/caffe/src/caffe/proto/caffe.pb.h"
#include "src/third_party/leap_motion/include/Leap.h"

// Utility functions for converting from one format to another, and for reading
// and writing disk.

namespace genesis {

std::unique_ptr<proto::LeapFrame> ReadProto(const std::string& filename);
bool WriteProto(const std::string& filename, const proto::LeapFrame& proto);
proto::Image ConvertImageToProto(const Leap::Image& image);
caffe::Datum ProtoToDatum(const proto::LeapFrame& proto);

std::vector<float> NormalizeAndSubtractMean(const std::vector<float>& array);
std::vector<float> ScaleImage(const std::vector<float>& img, int orig_w,
                              int orig_h, int scaled_w, int scaled_h);
std::vector<float> ConvertImageToNetInput(const float* frame, int width,
                                          int height);

int ExtractLabel(const Leap::Frame& frame);

}  // namespace genesis

#endif  // SRC_GENESIS_IO_CONVERSION_UTILS_H_
