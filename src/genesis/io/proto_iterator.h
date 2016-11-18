#ifndef SRC_GENESIS_IO_PROTO_ITERATOR_H_
#define SRC_GENESIS_IO_PROTO_ITERATOR_H_

#include <memory>
#include <string>

#include "src/genesis/io/proto/leap_frame.pb.h"

namespace genesis {

class ProtoIterator {
 public:
  ProtoIterator(const std::string& input_dir);
  std::unique_ptr<proto::LeapFrame> Next();

 private:
  std::string input_dir_;
  int index_;
  bool reached_end_;

};

}  // namespace genesis

#endif  // SRC_GENESIS_IO_PROTO_ITERATOR_H_
