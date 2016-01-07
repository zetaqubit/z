#include "src/genesis/io/proto_to_lmdb_converter.h"

#include <stdint.h>
#include <string>

#include "src/third_party/glog/src/glog/logging.h"

namespace {

static const std::string kProtoDir = 
    "/home/z/hand_tracking/blaze_root/data/genesis/current/proto";
static const std::string kLmdbDir =
    "/home/z/hand_tracking/blaze_root/data/genesis/current/lmdb";

}  // namespace

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;

  if (argc < 4) {
    LOG(FATAL) << "Usage: " << argv[0]
        << " [APPEND|OVERWRITE] starting_number ending_number";
    return 1;
  }

  genesis::LmdbStorage::WriteMode mode;
  if (!std::string("APPEND").compare(argv[1])) {
    mode = genesis::LmdbStorage::APPEND;
  } else if (!std::string("OVERWRITE").compare(argv[1])) {
    mode = genesis::LmdbStorage::OVERWRITE;
  } else {
    LOG(FATAL) << "Invalid write mode: " << argv[1]
        << ". Valid options: APPEND, OVERWRITE.";
  }

  int start = std::stoi(argv[2]);
  int end = std::stoi(argv[3]);
  if (start < 0 || end < 0 || start > end) {
    LOG(FATAL) << "Require start >= 0, end >=0, and start <= end.";
    return 1;
  }

  genesis::ProtoToLmdbConverter converter(kProtoDir, kLmdbDir, mode);
  converter.Convert(static_cast<uint32_t>(start),
                    static_cast<uint32_t>(end));
  return 0;
}
