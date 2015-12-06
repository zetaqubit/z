
# Not working. Need to write only main.cc that depends on caffe:caffe
cc_binary(
  name = "handnet",
  data = glob(["*.prototxt"]),
  deps = [
      "//src/third_party/caffe/tools:caffe",
  ],
)
