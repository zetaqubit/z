#ifndef SRC_GENESIS_FRAME_RECORDER_H_
#define SRC_GENESIS_FRAME_RECORDER_H_

#include <string>

#include "src/genesis/proto/leap_frame.pb.h"
#include "src/third_party/leap_motion/include/Leap.h"

namespace genesis {

class FrameRecorder {
 public:
  FrameRecorder(const std::string& proto_output_dir);
  void Record(const Leap::Frame& frame);

 private:
  void ReadProto(std::string filename);
  void WriteProto(std::string filename, proto::LeapFrame leap_frame);

  std::string proto_output_dir_;
  int frame_number_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_FRAME_RECORDER_H_
