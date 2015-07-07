## Library for creating, training, and deploying neural networks.

package(default_visibility = ["//visibility:public"])

load("/src/third_party/caffe/gen_proto", "proto_library")

proto_library(
  name = "caffe_protos",
  srcs = glob([
    "**/*.proto",
  ]),
  visibility = ["//visibility:public"],
)

cc_library(
  name = "caffe",
  srcs = glob(
    [
      "src/**/*.cpp",
    ],
    exclude = [
      "src/**/test_*.cpp",
    ]
  ),
  hdrs = glob([
    "includes/**/*.hpp",
  ]),
  includes = [
    "include",
    "src",
    "../cuda/include",
    "../open_blas/include",
  ],
  deps = [
    ":caffe_protos",
    "//src/third_party/open_blas",
    "//src/third_party/cuda:cublas",

    # TODO: add cuda sources
  ],
)

