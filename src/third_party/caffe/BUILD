## Library for creating, training, and deploying neural networks.

package(default_visibility = ["//visibility:public"])

load("@protobuf//:protobuf.bzl", "cc_proto_library")
load("/src/third_party/caffe/cuda_library", "cuda_library")

cc_proto_library(
  name = "caffe_protos",
  srcs = glob([
    "**/*.proto",
  ]),
  default_runtime = "@protobuf//:protobuf",
  protoc = "@protobuf//:protoc",
  visibility = ["//visibility:public"],
)

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
  ],
)

WARNINGS = [
  "-Wall",
  "-Wno-sign-compare",
]

COMMON_FLAGS = [
  "-DUSE_CUDNN",
  "-DNDEBUG",
  "-O2",
]

CUDA_INCLUDES = [
  "-I$(GENDIR)/src/third_party/caffe/src",  # for caffe.pb.h
  "-Isrc/third_party/caffe/include",
  "-Isrc/third_party/cuda/include",
  "-Isrc/third_party/gflags/include",
  "-Isrc/third_party/glog/src",
  "-Isrc/third_party/open_blas/include",
  "-Igoogle/protobuf/src",
]

CUDA_ARCH = [
  #"-gencode arch=compute_20,code=sm_20",
  #"-gencode arch=compute_20,code=sm_21",
  "-gencode arch=compute_30,code=sm_30",
  "-gencode arch=compute_35,code=sm_35",
  #"-gencode arch=compute_50,code=sm_50",
  #"-gencode arch=compute_50,code=compute_50",
]

CUDA_OPTS = COMMON_FLAGS + [
  "-Xcompiler",
  "-fPIC",
] + CUDA_INCLUDES + CUDA_ARCH

cuda_library(
  name = "caffe_lib_cuda",
  srcs = glob([
    "src/caffe/**/*.cu",
  ], exclude = [
    "src/**/test_*.cu",
  ]),
  other_srcs = [
    "//src/third_party/caffe:caffe_protos",  # caffe.pb.h
  ],
  nvcc_opts = CUDA_OPTS,
)

cc_library(
  name = "caffe",
  srcs = glob([
    "src/caffe/**/*.cpp",
  ], exclude = [
    "src/**/test_*.cpp",
  ]),
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
    ":caffe_lib_cuda",
    "@protobuf//:protobuf",
    "//src/third_party/cuda:cuda",
    "//src/third_party/gflags:gflags",
    "//src/third_party/glog:glog",
    "//src/third_party/open_blas:open_blas",
  ],
  copts = [
    "-pthread",
    "-fPIC",
    "-MMD",
    "-MP",
  ] + COMMON_FLAGS + WARNINGS,

  linkopts = [
    "-lleveldb",
    "-lsnappy",
    "-llmdb",
    "-lboost_system",
    "-lhdf5_hl",
    "-lhdf5",
    "-lm",

    "-lopencv_core",
    "-lopencv_highgui",
    "-lopencv_imgproc",

    "-lboost_thread",
    "-lstdc++",

    "-pthread",
    "-fPIC",

  ] + COMMON_FLAGS + WARNINGS,

  # When static-linking Caffe, force link all the object files, even ones
  # whose symbols are not referenced from source. This is necessary because the
  # Caffe layers self-register on init and are invoked through prototxt spec.
  alwayslink = 1,
)

