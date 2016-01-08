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
    "//data/genesis/caffe:current_model",
    "//data/genesis/caffe:trained_models",
  ],
  deps = [
    "//src/genesis/io:conversion_utils",
    "//src/genesis/io:datatypes",
    "//src/genesis/visualization:image_viewer",
    "//src/third_party/caffe:caffe",
    "//src/third_party/glog",
  ],
)

filegroup(
  name = "model",
  srcs = glob([
    "*.prototxt",
  ]),
)
