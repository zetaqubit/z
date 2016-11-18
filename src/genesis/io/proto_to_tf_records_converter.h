#ifndef SRC_GENESIS_IO_PROTO_TO_TF_RECORDS_CONVERTER_H_
#define SRC_GENESIS_IO_PROTO_TO_TF_RECORDS_CONVERTER_H_

#include <string>

namespace genesis {

class ProtoToTfRecordsConverter {
 public:
  void WriteRecords(const std::string& input_dir,
                    const std::string& output_file);

};

}  // namespace genesis

#endif  // SRC_GENESIS_IO_PROTO_TO_TF_RECORDS_CONVERTER_H_
