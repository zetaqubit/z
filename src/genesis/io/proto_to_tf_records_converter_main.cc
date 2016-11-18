#include "src/genesis/io/proto_to_tf_records_converter.h"

#include <stdint.h>
#include <string>

#include "src/third_party/glog/src/glog/logging.h"

namespace {

static const std::string kProtoDir = 
    "/home/z/code/blaze_root/data/genesis/current/proto";
static const std::string kTfRecordsFile =
    "/home/z/code/blaze_root/data/genesis/current/tf/frames.tfrecords";

}  // namespace

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;

  genesis::ProtoToTfRecordsConverter converter;
  converter.WriteRecords(kProtoDir, kTfRecordsFile);
  return 0;
}
