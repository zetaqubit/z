cc_binary(
  name = "caffe",
  srcs = ["caffe.cpp"],
  deps = [
    # "//src/third_party/caffe:caffe_lib",
    "//src/third_party/caffe:caffe",
  ],
  linkopts = [
    "-lglog",
    "-lgflags",
    "-lpthread",
  ],
  visibility = ["//visibility:public"],
)
