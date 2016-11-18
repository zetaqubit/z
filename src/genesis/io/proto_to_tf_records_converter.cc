#include "src/genesis/io/proto_to_tf_records_converter.h"

#include <memory>

#include "src/genesis/io/conversion_utils.h"
#include "src/genesis/io/proto_iterator.h"
#include "src/third_party/glog/src/glog/logging.h"
#include "tensorflow/core/lib/io/record_writer.h"
#include "tensorflow/core/platform/env.h"

namespace genesis {

void ProtoToTfRecordsConverter::WriteRecords(
    const std::string& input_dir,
    const std::string& output_file) {

  ProtoIterator iterator(input_dir);

  tensorflow::WritableFile* output_fh;
  tensorflow::Env::Default()->NewWritableFile(output_file, &output_fh);
  tensorflow::io::RecordWriter writer(output_fh);

  while (true) {
    std::unique_ptr<proto::LeapFrame> proto = iterator.Next();
    if (!proto) {
      break;
    }

    tensorflow::Example example = ProtoToExample(*proto);
    std::string serialized_proto;
    example.SerializeToString(&serialized_proto);
    auto status = writer.WriteRecord(serialized_proto);
    if (!status.ok()) {
      LOG(ERROR) << "Failed to write record: " << status.error_message();
    }
  }
  delete output_fh;
}

}  // namespace genesis
