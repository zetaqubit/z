#include "src/genesis/proto_to_lmdb_converter.h"

#include <fstream>
#include <glog/logging.h>

#include "src/genesis/proto/leap_frame.pb.h"

namespace genesis {

ProtoToLmdbConverter::ProtoToLmdbConverter(const std::string& input_dir,
                                           const std::string& output_dir,
                                           LmdbStorage::WriteMode mode)
    : input_dir_(input_dir),
      output_dir_(output_dir),
      storage_(LmdbStorage(output_dir, mode)) {

  // Open all proto files in input_dir.
  // Read them and write to storage_.
}

int ProtoToLmdbConverter::Convert(uint32_t starting_file_number,
                                  uint32_t ending_file_number) {
  DCHECK(starting_file_number <= ending_file_number)
      << "Ending file number is less than starting file number.";
  LOG(INFO) << "Converting protos FROM ";
  LOG(INFO) << "[" << input_dir_ << "]["
      << starting_file_number << "," << ending_file_number << "].pb  TO ";
  LOG(INFO) << "[" << output_dir_ << "]";

  int files_converted = 0;
  for (uint32_t i = starting_file_number; i <= ending_file_number; i++) {
    std::string filename = input_dir_ + "/" + std::to_string(i) + ".pb";

    proto::LeapFrame proto;

    std::fstream input(filename, std::fstream::in | std::ios::binary);
    if (!input) {
      LOG(ERROR) << "Skipping " << filename << ": unable to open.";
      continue;
    } else if (!proto.ParseFromIstream(&input)) {
      LOG(ERROR) << "Skipping " << filename << ": unable to parse proto.";
      continue;
    }
    if (!storage_.Write(i, proto)) {
      LOG(ERROR) << "Stopping at " << filename << ": could not write to LMDB.";
      break;
    }
    files_converted++;
  }

  if (!storage_.Flush()) {
    LOG(ERROR) << "Final flush failed.";
  }

  LOG(INFO) << "Finished converting " << files_converted << " protos in ["
      << starting_file_number << ", " << ending_file_number << "].";

  return files_converted;
}

}  // namespace genesis
