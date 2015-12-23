#include "src/genesis/frame_recorder.h"

#include <glog/logging.h>
#include <sys/stat.h>
#include <fstream>
#include <iostream>

using std::endl;
using std::fstream;
using std::ios;
using std::string;

namespace genesis {

namespace {
}  // namespace


FrameRecorder::FrameRecorder(const string& proto_output_dir)
  : proto_output_dir_(proto_output_dir),
    frame_number_(0) {
  // Create directory if it does not already exist.
  mkdir(proto_output_dir.c_str(), 0700);
}

void FrameRecorder::ReadProto(string filename) {
  fstream input(filename, ios::in | ios::binary);
  proto::LeapFrame leap_frame;
  if (!input) {
    LOG(INFO) << filename << ": File not found" << endl;
  } else if (!leap_frame.ParseFromIstream(&input)) {
    LOG(ERROR) << "Failed to parse Leap frame proto." << endl;
    return;
  }
}

void FrameRecorder::WriteProto(string filename, proto::LeapFrame leap_frame) {
  fstream output(filename, ios::out | ios::trunc | ios::binary);
  if (!output) {
    LOG(ERROR) << "Could not open " << filename << " for writing." << endl;
    return;
  }
  if (!leap_frame.SerializeToOstream(&output)) {
    LOG(ERROR) << "Failed to write Leap frame proto." << endl;
    return;
  }
}

proto::Image ConvertImageToProto(const Leap::Image& image) {
  proto::Image proto;
  proto.set_width(image.width());
  proto.set_height(image.height());
  for (int r = 0; r < image.height(); r++) {
    for (int c = 0; c < image.width(); c++) {
      proto.add_data(image.data()[c + r * image.width()]);
    }
  }
  return proto;
}

void FrameRecorder::Record(const Leap::Frame& frame) {
  if (!frame.isValid()) {
    return;
  }

  //LOG(INFO) << "Recording frame: " << std::to_string(frame_number_) << endl;

  proto::LeapFrame leap_frame;
  leap_frame.set_timestamp_ms(frame.timestamp());

  // Update image and distortion textures.
  Leap::Image left = frame.images()[0];
  if (left.width() > 0) {
    *leap_frame.mutable_left() = ConvertImageToProto(left);
  }
  Leap::Image right = frame.images()[1];
  if (right.width() > 0) {
    *leap_frame.mutable_right() = ConvertImageToProto(right);
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

  string filename = 
      proto_output_dir_ + "/" + std::to_string(frame_number_) + ".pb";
  frame_number_++;

  if (!proto_output_dir_.empty()) {
    WriteProto(filename, leap_frame);
  }
}

}  // namespace genesis
