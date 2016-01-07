#include "src/genesis/io/lmdb_storage.h"

#include <stdint.h>
#include <sys/stat.h>

#include "src/third_party/glog/src/glog/logging.h"

namespace genesis {

LmdbStorage::LmdbStorage(const std::string& db_path, WriteMode mode) {
  // Create LMDB directory if it does not already exist.
  LOG(INFO) << "Opening lmdb " << db_path;
  int mkdir_failed = mkdir(db_path.c_str(), 0700);

  if (mode == OVERWRITE) {
    LOG(INFO) << "Overwriting database.";
    if (mkdir_failed) {
      LOG(FATAL) << "Could not overwrite: " << db_path << " already exists.";
      return;
    }
  } else if (mode == APPEND) {
    LOG(INFO) << "Appending to database.";
  }

  CHECK_EQ(mdb_env_create(&mdb_env_), MDB_SUCCESS) << "mdb_env_create failed";
  CHECK_EQ(mdb_env_set_mapsize(mdb_env_, 1099511627776), MDB_SUCCESS)  // 1TB
      << "mdb_env_set_mapsize failed";
  CHECK_EQ(mdb_env_open(mdb_env_, db_path.c_str(), 0, 0664), MDB_SUCCESS)
      << "mdb_env_open failed";
  CHECK_EQ(mdb_txn_begin(mdb_env_, NULL, 0, &mdb_txn_), MDB_SUCCESS)
      << "mdb_txn_begin failed";
  CHECK_EQ(mdb_open(mdb_txn_, NULL, 0, &mdb_dbi_), MDB_SUCCESS)
      << "mdb_open failed. Does the lmdb already exist? ";
}

LmdbStorage::~LmdbStorage() {
  CHECK_EQ(mdb_txn_commit(mdb_txn_), MDB_SUCCESS) << "mdb_txn_commit failed";
  mdb_close(mdb_env_, mdb_dbi_);
  mdb_env_close(mdb_env_);
}

bool LmdbStorage::Write(uint32_t key, std::string value) {
  const int kMaxKeyLength = 10;
  char key_cstr[kMaxKeyLength];
  snprintf(key_cstr, kMaxKeyLength, "%08d", key);
  std::string keystr(key_cstr);

  // Write in database
  MDB_val mdb_key, mdb_data;
  mdb_key.mv_size = keystr.size();
  mdb_key.mv_data = reinterpret_cast<void*>(&keystr[0]);
  mdb_data.mv_size = value.size();
  mdb_data.mv_data = reinterpret_cast<void*>(&value[0]);
  if (mdb_put(mdb_txn_, mdb_dbi_, &mdb_key, &mdb_data, 0) != MDB_SUCCESS) {
    LOG(ERROR) << "mdb_put failed";
    return false;
  }

  if (key % 100 == 0) {
    if (!Flush()) {
      return false;
    }
  }
  return true;
}

bool LmdbStorage::Flush() {
  if (mdb_txn_commit(mdb_txn_) != MDB_SUCCESS) {
    LOG(ERROR) << "mdb_txn_commit failed";
    return false;
  }
  if (mdb_txn_begin(mdb_env_, NULL, 0, &mdb_txn_) != MDB_SUCCESS) {
    LOG(ERROR) << "mdb_txn_begin failed";
    return false;
  }
  return true;
}

}  // namespace genesis
