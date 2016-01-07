cc_binary(
  name = "caffe",
  srcs = ["caffe.cpp"],
  deps = [
    # "//src/third_party/caffe:caffe_lib",
    "//src/third_party/caffe:caffe",
    "//src/third_party/gflags",
    "//src/third_party/glog",
  ],
  linkopts = [
    "-lpthread",
  ],
  visibility = ["//visibility:public"],
)
