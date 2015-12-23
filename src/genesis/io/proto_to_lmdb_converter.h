#ifndef SRC_GENESIS_IO_PROTO_TO_LMDB_CONVERTER_H_
#define SRC_GENESIS_IO_PROTO_TO_LMDB_CONVERTER_H_

#include <stdint.h>
#include <string>

#include "src/genesis/io/lmdb_storage.h"

namespace genesis {

class ProtoToLmdbConverter {
 public:
  ProtoToLmdbConverter(const std::string& input_dir,
                       const std::string& output_dir,
                       LmdbStorage::WriteMode mode);

  // Stores protos into LMDB storage.
  //
  // @param starting_file_number starting file number
  // @param ending_file_number the file number to end at. All protos with
  //     integer filenames between starting_file_number.pb and
  //     ending_file_number.pb (inclusive) are converted.
  // @return the number of files converted and stored into the LMDB.
  int Convert(uint32_t starting_file_number, uint32_t ending_file_number);

 private:
  std::string input_dir_;
  std::string output_dir_;
  LmdbStorage storage_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_IO_PROTO_TO_LMDB_CONVERTER_H_
