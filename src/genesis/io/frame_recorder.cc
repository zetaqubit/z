#include "src/genesis/io/frame_recorder.h"

#include <sys/stat.h>

#include "src/genesis/io/conversion_utils.h"
#include "src/genesis/io/proto/metadata.pb.h"
#include "src/third_party/glog/src/glog/logging.h"

namespace {

static const std::string METADATA_FILENAME = "metadata.pb";

}  // namespace

namespace genesis {

FrameRecorder::FrameRecorder(const std::string& proto_output_dir)
  : proto_output_dir_(proto_output_dir),
    frame_number_(0) {
  if (proto_output_dir_.empty()) {
    return;
  }

  // Create directory if it does not already exist.
  mkdir(proto_output_dir.c_str(), 0700);

  auto metadata = ReadProto<proto::Metadata>(
      proto_output_dir_ + "/" + METADATA_FILENAME);
  if (metadata != nullptr) {
    frame_number_ = metadata->next_frame_number();
  }
  LOG(INFO) << "Saving started from: " << frame_number_ << ".pb";
}

FrameRecorder::~FrameRecorder() {
  if (proto_output_dir_.empty()) {
    return;
  }

  proto::Metadata metadata;
  metadata.set_next_frame_number(frame_number_);
  WriteProto(proto_output_dir_ + "/" + METADATA_FILENAME, metadata);
  LOG(INFO) << "Saving ended before: " << frame_number_ << ".pb";
}

void FrameRecorder::Record(const Leap::Frame& frame) {
  if (proto_output_dir_.empty() || !frame.isValid()) {
    return;
  }

  //LOG(INFO) << "Recording frame: " << std::to_string(frame_number_);

  proto::LeapFrame leap_frame = FrameToProto(frame);

  std::string filename =
      proto_output_dir_ + "/" + std::to_string(frame_number_) + ".pb";
  frame_number_++;

  WriteProto(filename, leap_frame);
}

}  // namespace genesis
