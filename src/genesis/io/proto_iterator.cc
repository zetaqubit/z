#include "src/genesis/io/proto_iterator.h"

#include <fstream>

namespace genesis {

ProtoIterator::ProtoIterator(const std::string& input_dir)
  : input_dir_(input_dir), index_(0), reached_end_(false) {
}

std::unique_ptr<proto::LeapFrame> ProtoIterator::Next() {
  std::unique_ptr<proto::LeapFrame> proto = std::unique_ptr<proto::LeapFrame>(
      new proto::LeapFrame());
  std::string filename = input_dir_ + "/" + std::to_string(index_) + ".pb";
  index_++;
  std::fstream input(filename, std::fstream::in | std::ios::binary);
  if (!input || !proto->ParseFromIstream(&input)) {
    return nullptr;
  }
  return proto;
}

}  // namespace genesis
