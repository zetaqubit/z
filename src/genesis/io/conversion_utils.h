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

// String logging.
template<typename ... Args>
std::string Format(const std::string& format, Args... args) {
  // Extra space for '\0'
  size_t size = snprintf( nullptr, 0, format.c_str(), args...) + 1;
  std::unique_ptr<char[]> buf(new char[size]);
  snprintf(buf.get(), size, format.c_str(), args...);
  return std::string( buf.get(), buf.get() + size - 1); // strip '\0'
}


// Proto conversions.
std::unique_ptr<proto::LeapFrame> ReadProto(const std::string& filename);
bool WriteProto(const std::string& filename, const proto::LeapFrame& proto);
proto::LeapFrame FrameToProto(const Leap::Frame& frame);
caffe::Datum ProtoToDatum(const proto::LeapFrame& proto);
std::vector<float> SerializeInputToNN(const proto::LeapFrame& proto);
void SerializeHand(const proto::Hand& hand, std::vector<float>* output);

// Geometric operations.
const Leap::Vector ProjectToScreenUndistorted(const Leap::Vector& p,
                                              const Leap::Image& image);
const Leap::Vector ProjectToScreenDistorted(const Leap::Vector& p,
                                            const Leap::Image& image);

// Image operations.
void ConvertImageToNetInput(Image* image);

}  // namespace genesis

#endif  // SRC_GENESIS_IO_CONVERSION_UTILS_H_
