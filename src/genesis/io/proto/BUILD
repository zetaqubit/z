package(default_visibility = ["//visibility:public"])

load("@protobuf//:protobuf.bzl", "cc_proto_library", "py_proto_library")

cc_proto_library(
  name = "genesis_protos",
  srcs = glob([
    "*.proto",
  ]),
  default_runtime = "@protobuf//:protobuf",
  protoc = "@protobuf//:protoc",
)

py_proto_library(
  name = "genesis_protos_py",
  srcs = glob([
    "*.proto",
  ]),
  default_runtime = "@protobuf//:protobuf_python",
  protoc = "@protobuf//:protoc",
)
