package(default_visibility = ["//visibility:public"])

cc_library(
  name = "handnet_inference",
  srcs = [
    "hand_neural_net.cc",
  ],
  hdrs = [
    "hand_neural_net.h",
  ],
  data = [
    ":model",
    "//data/genesis/caffe:trained_weights",
  ],
  deps = [
    "//src/genesis/io:conversion_utils",
    "//src/genesis/io:datatypes",
    "//src/genesis/visualization:image_viewer",
    "//src/third_party/caffe:caffe_lib",
  ],
  linkopts = [
    "-lglog",
  ],
)

filegroup(
  name = "model",
  srcs = glob([
    "*.prototxt",
  ]),
)
