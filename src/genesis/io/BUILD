package(default_visibility = ["//visibility:public"])

cc_library(
  name = "frame_recorder",
  srcs = [
    "frame_recorder.cc",
  ],
  hdrs = [
    "frame_recorder.h",
  ],
  deps = [
    ":lmdb_storage",
    "//src/third_party/leap_motion:api",
    "//src/genesis/io/proto:genesis_protos",
  ],
)

cc_library(
  name = "lmdb_storage",
  srcs = [
    "lmdb_storage.cc"
  ],
  hdrs = [
    "lmdb_storage.h"
  ],
  deps = [
    "//src/genesis/io/proto:genesis_protos",
    "//src/genesis/visualization:image_viewer",  # for debugging
    "//src/third_party/caffe:caffe_protos"
  ],
  linkopts = [
    "-lglog",
    "-llmdb",
  ],
)

cc_library(
  name = "proto_to_lmdb_converter",
  srcs = [
    "proto_to_lmdb_converter.cc",
  ],
  hdrs = [
    "proto_to_lmdb_converter.h",
  ],
  deps = [
    ":lmdb_storage",
    "//src/genesis/io/proto:genesis_protos",
  ],
  linkopts = [
    "-lglog",
  ],
)

cc_binary(
  name = "converter",
  srcs = [
    "proto_to_lmdb_converter_main.cc",
  ],
  deps = [
    ":proto_to_lmdb_converter",
  ],
)
