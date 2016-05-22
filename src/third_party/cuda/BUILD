package(default_visibility = ["//visibility:public"])

filegroup(
    name = "nvcc",
    srcs = [
      "bin/nvcc",
    ],
)

cc_library(
    name = "cuda_headers",
    hdrs = glob([
        "**/*.h",
    ]),
    includes = [".", "include"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cudart_static",
    srcs = [
        "lib64/libcudart_static.a",
    ],
    includes = ["include/"],
    linkopts = [
        "-ldl",
        "-lrt",
        "-lpthread",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cudart",
    srcs = [
        "lib64/libcudart.so.7.0",
    ],
    data = [
        "lib64/libcudart.so.7.0",
    ],
    includes = ["include/"],
    visibility = ["//visibility:public"],
    linkstatic = 1,
)

cc_library(
    name = "cublas",
    srcs = [
        "lib64/libcublas.so.7.0",
    ],
    data = [
        "lib64/libcublas.so.7.0",
    ],
    includes = ["include/"],
    visibility = ["//visibility:public"],
    linkstatic = 1,
)

cc_library(
    name = "cudnn",
    srcs = [
        "lib64/libcudnn.so.4",
    ],
    data = [
        "lib64/libcudnn.so.4",
    ],
    includes = ["include/"],
    visibility = ["//visibility:public"],
    linkstatic = 1,
)

cc_library(
    name = "cufft",
    srcs = [
        "lib64/libcufft.so.7.0",
    ],
    data = [
        "lib64/libcufft.so.7.0",
    ],
    includes = ["include/"],
    visibility = ["//visibility:public"],
    linkstatic = 1,
)

cc_library(
    name = "curand",
    srcs = [
        "lib64/libcurand.so.7.0",
    ],
    data = [
        "lib64/libcurand.so.7.0",
    ],
    includes = ["include/"],
    visibility = ["//visibility:public"],
    linkstatic = 1,
)

cc_library(
    name = "cuda",
    deps = [
        ":cuda_headers",
        ":cudart",
        ":cublas",
        ":cudnn",
        ":cufft",
        ":curand",
    ],
    visibility = ["//visibility:public"],
)
