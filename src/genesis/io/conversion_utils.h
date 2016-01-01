#ifndef SRC_GENESIS_IO_CONVERSION_UTILS_H_
#define SRC_GENESIS_IO_CONVERSION_UTILS_H_

#include <memory>
#include <string>

#include "src/genesis/io/datatypes.h"
#include "src/genesis/io/proto/leap_frame.pb.h"
#include "src/third_party/caffe/src/caffe/proto/caffe.pb.h"
#include "src/third_party/leap_motion/include/Leap.h"

// Utility functions for converting from one format to another, and for reading
// and writing disk.

namespace genesis {

// Proto conversions.
std::unique_ptr<proto::LeapFrame> ReadProto(const std::string& filename);
bool WriteProto(const std::string& filename, const proto::LeapFrame& proto);
proto::Image ImageToProto(const Leap::Image& image);
caffe::Datum ProtoToDatum(const proto::LeapFrame& proto);

// Image operations.
void ConvertImageToNetInput(Image* image);

int ExtractLabel(const Leap::Frame& frame);

}  // namespace genesis

#endif  // SRC_GENESIS_IO_CONVERSION_UTILS_H_
