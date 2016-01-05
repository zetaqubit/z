## Library for creating, training, and deploying neural networks.

package(default_visibility = ["//visibility:public"])

load("/src/genesis/io/proto/gen_proto", "proto_library")
load("/src/third_party/caffe/cuda_library", "cuda_library")

proto_library(
  name = "caffe_protos",
  srcs = glob([
    "**/*.proto",
  ]),
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

COMMON_FLAGS = [
  "-DUSE_CUDNN",
]

CUDA_INCLUDES = [
  "-I$(GENDIR)/src/third_party/caffe/src",  # for caffe.pb.h
  "-Isrc/third_party/caffe/include",
  "-Isrc/third_party/cuda/include",
  "-Isrc/third_party/open_blas/include",
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
  "-DNDEBUG",
  "-O2",
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
    "//src/third_party/cuda:cublas",
    "//src/third_party/open_blas",
  ],
  copts = [
    "-pthread",
    "-fPIC",
    "-MMD",
    "-MP",

  ] + COMMON_FLAGS,

  linkopts = [
    # Library dir
    "-Lsrc/third_party/cuda/lib64",
    "-Lsrc/third_party/open_blas/lib",
    #"-L/opt/OpenBLAS/lib",
    #"-L/opt/cuda/lib64",
    "-L.",

    # LDFLAGS
    "-lcudart",
    "-lcublas",
    "-lcurand",
    #"-lcuda",
    "-lcudnn",

    "-lglog",
    "-lgflags",
    "-lprotobuf",
    "-lleveldb",
    "-lsnappy",
    "-llmdb",
    "-lboost_system",
    #"-lhdf5_h1",
    "-lhdf5",
    "-lm",

    "-lopencv_core",
    "-lopencv_highgui",
    "-lopencv_imgproc",

    "-lboost_thread",
    "-lstdc++",

    "-lopenblas",

  ] + COMMON_FLAGS,
)

