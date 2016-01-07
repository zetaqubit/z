#include "src/genesis/io/frame_recorder.h"

#include <sys/stat.h>

#include "src/genesis/io/conversion_utils.h"
#include "src/third_party/glog/src/glog/logging.h"

namespace genesis {

FrameRecorder::FrameRecorder(const std::string& proto_output_dir)
  : proto_output_dir_(proto_output_dir),
    frame_number_(0) {
  // Create directory if it does not already exist.
  mkdir(proto_output_dir.c_str(), 0700);
}

void FrameRecorder::Record(const Leap::Frame& frame) {
  if (!frame.isValid()) {
    return;
  }

  //LOG(INFO) << "Recording frame: " << std::to_string(frame_number_);

  proto::LeapFrame leap_frame = FrameToProto(frame);

  std::string filename =
      proto_output_dir_ + "/" + std::to_string(frame_number_) + ".pb";
  frame_number_++;

  if (!proto_output_dir_.empty()) {
    WriteProto(filename, leap_frame);
  }
}

}  // namespace genesis
