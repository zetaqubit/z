#ifndef SRC_GENESIS_IO_LMDB_STORAGE_H_
#define SRC_GENESIS_IO_LMDB_STORAGE_H_

#include <string>
#include <lmdb.h>

#include "src/genesis/io/proto/leap_frame.pb.h"

namespace genesis {

// Wrapper around LMDB that takes protos and writes them into the storage.
class LmdbStorage {
 public:
  enum WriteMode { APPEND, OVERWRITE };

  LmdbStorage(const std::string& db_path, WriteMode mode);
  virtual ~LmdbStorage();
  bool Write(uint32_t key, const proto::LeapFrame& proto);
  bool Flush();

 private:
  std::string db_path_;

  MDB_env *mdb_env_;
  MDB_dbi mdb_dbi_;
  MDB_txn *mdb_txn_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_IO_LMDB_STORAGE_H_
