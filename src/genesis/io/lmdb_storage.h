#ifndef SRC_GENESIS_IO_LMDB_STORAGE_H_
#define SRC_GENESIS_IO_LMDB_STORAGE_H_

#include <lmdb.h>
#include <string>

namespace genesis {

// Wrapper around LMDB that takes protos and writes them into the storage.
class LmdbStorage {
 public:
  enum WriteMode { APPEND, OVERWRITE };

  LmdbStorage(const std::string& db_path, WriteMode mode);
  virtual ~LmdbStorage();
  bool Write(uint32_t key, std::string value);
  bool Flush();

 private:
  std::string db_path_;

  MDB_env *mdb_env_;
  MDB_dbi mdb_dbi_;
  MDB_txn *mdb_txn_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_IO_LMDB_STORAGE_H_
