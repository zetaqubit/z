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
    ":conversion_utils",
    ":lmdb_storage",
    "//src/third_party/leap_motion:api",
    "//src/genesis/io/proto:genesis_protos",
  ],
)

cc_library(
  name = "datatypes",
  hdrs = [
    "datatypes.h",
  ],
  deps = [
    "//src/third_party/cimg:cimg",
  ],
)

cc_library(
  name = "conversion_utils",
  srcs = [
    "conversion_utils.cc",
  ],
  hdrs = [
    "conversion_utils.h",
  ],
  deps = [
    ":datatypes",
    "//src/genesis/io/proto:genesis_protos",
    "//src/genesis/visualization:image_viewer",  # for debugging
    "//src/third_party/leap_motion:api",
    "//src/third_party/caffe:caffe_protos",
    "@tf//tensorflow/core:tensorflow",
  ],
)

cc_library(
  name = "proto_iterator",
  srcs = [
    "proto_iterator.cc",
  ],
  hdrs = [
    "proto_iterator.h",
  ],
  deps = [
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
    "//src/third_party/glog",
  ],
  linkopts = [
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
    ":conversion_utils",
    ":lmdb_storage",
    "//src/genesis/io/proto:genesis_protos",
    "//src/third_party/caffe:caffe_protos",
    "//src/third_party/glog",
  ],
)

cc_library(
  name = "proto_to_tf_records_converter",
  srcs = [
    "proto_to_tf_records_converter.cc",
  ],
  hdrs = [
    "proto_to_tf_records_converter.h",
  ],
  deps = [
    ":conversion_utils",
    ":proto_iterator",
    "//src/genesis/io/proto:genesis_protos",
    "//src/third_party/glog",
    "@tf//tensorflow/core:lib",
  ],
)

cc_binary(
  name = "lmdb_converter_main",
  srcs = [
    "proto_to_lmdb_converter_main.cc",
  ],
  deps = [
    ":proto_to_lmdb_converter",
  ],
)

cc_binary(
  name = "tf_records_converter_main",
  srcs = [
    "proto_to_tf_records_converter_main.cc",
  ],
  deps = [
    ":proto_to_tf_records_converter",
  ],
)
