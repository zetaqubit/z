#ifndef SRC_GENESIS_IO_CONVERSION_UTILS_H_
#define SRC_GENESIS_IO_CONVERSION_UTILS_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "src/genesis/io/datatypes.h"
#include "src/genesis/io/proto/leap_frame.pb.h"
#include "src/genesis/io/proto/metadata.pb.h"
#include "src/third_party/caffe/src/caffe/proto/caffe.pb.h"
#include "src/third_party/glog/src/glog/logging.h"
#include "src/third_party/leap_motion/include/Leap.h"

// Utility functions for converting from one format to another, and for reading
// and writing disk.

using std::ios;
using std::fstream;
using std::string;

namespace genesis {

// String logging.
template<typename ... Args>
std::string Format(const string& format, Args... args) {
  // Extra space for '\0'
  size_t size = snprintf( nullptr, 0, format.c_str(), args...) + 1;
  std::unique_ptr<char[]> buf(new char[size]);
  snprintf(buf.get(), size, format.c_str(), args...);
  return string( buf.get(), buf.get() + size - 1); // strip '\0'
}


// Proto conversions.
template<typename T>
std::unique_ptr<T> ReadProto(const string& filename) {
  fstream input(filename, ios::in | ios::binary);
  if (!input) {
    LOG(INFO) << filename << ": File not found";
    return nullptr;
  }
  std::unique_ptr<T> proto(new T());
  if (!proto->ParseFromIstream(&input)) {
    LOG(ERROR) << "Failed to parse Leap frame proto.";
    return nullptr;
  }
  return proto;
}

bool WriteProto(const string& filename,
                const ::google::protobuf::Message& proto);
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
