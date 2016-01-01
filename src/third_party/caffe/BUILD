## Library for creating, training, and deploying neural networks.

package(default_visibility = ["//visibility:public"])

load("/src/genesis/io/proto/gen_proto", "proto_library")

proto_library(
  name = "caffe_protos",
  srcs = glob([
    "**/*.proto",
  ]),
  visibility = ["//visibility:public"],
)

COMMON_FLAGS = [
  "-DUSE_CUDNN",
]

cc_library(
  name = "caffe_lib",
  srcs = [
    "build/lib/libcaffe.so",
  ],
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
    "//src/third_party/cuda:cublas",
    "//src/third_party/open_blas",

    # TODO: add cuda sources
  ],
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
    "//src/third_party/cuda:cublas",
    "//src/third_party/open_blas",

    # TODO: add cuda sources
  ],
  copts = [
    "-pthread",
    "-fPIC",
    "-MMD",
    "-MP",

  ] + COMMON_FLAGS,

  linkopts = [
    # Library dir
    "-L../cuda/lib64",
    "-L../cuda/lib",
    "-L../open_blas/lib",
    "-L.",

    # LDFLAGS
    #"-lcudart",
    "-lcublas",
    #"-lcurand",
    "-lcuda",
    #"-lcudnn",

    "-lglog",
    "-lgflags",
    "-lprotobuf",
    "-lleveldb",
    "-lsnappy",
    "-llmdb",
    #"-lhdf5_h1",
    "-lhdf5",

    "-lboost_thread",
    #"-lstdc++",

    "-lopenblas",

    "-lm",
  ] + COMMON_FLAGS,
)

