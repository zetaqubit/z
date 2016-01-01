#include "src/genesis/io/frame_recorder.h"

#include <glog/logging.h>
#include <sys/stat.h>

#include "src/genesis/io/conversion_utils.h"

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

  proto::LeapFrame leap_frame;
  leap_frame.set_timestamp_ms(frame.timestamp());

  // Update image and distortion textures.
  Leap::Image left = frame.images()[0];
  if (left.width() > 0) {
    *leap_frame.mutable_left() = ImageToProto(left);
  }
  Leap::Image right = frame.images()[1];
  if (right.width() > 0) {
    *leap_frame.mutable_right() = ImageToProto(right);
  }

  // Update hand pose.
  Leap::HandList hands = frame.hands();
  for (auto hl = hands.begin(); hl != hands.end(); hl++) {
    Leap::Hand hand = *hl;
    if (hand.isLeft()) {
      proto::Pose pose;
      Leap::Vector position = hand.palmPosition();
      pose.set_x(position.x);
      pose.set_y(position.y);
      pose.set_z(position.z);
      *leap_frame.mutable_hand_pose() = pose;
      //LOG(INFO) << "Left hand pose: " << position.x << ", " << position.y << ", "
      //    << position.z;
      break;
    }
  }

  std::string filename =
      proto_output_dir_ + "/" + std::to_string(frame_number_) + ".pb";
  frame_number_++;

  if (!proto_output_dir_.empty()) {
    WriteProto(filename, leap_frame);
  }
}

}  // namespace genesis
