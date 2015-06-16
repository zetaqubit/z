package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [":visualizer"],
    linkopts = [
        "-lglog",
    ],
)

cc_library(
    name = "visualizer",
    srcs = ["visualizer.cc"],
    hdrs = ["visualizer.h"],
    deps = [":gl_utils"],
    data = glob(["data/*"]),
    linkopts = [
        "-lSDL2",
        "-lGLEW",
        "-lGLU",
        "-lGL",
        "-lglog",
    ],
)

cc_library(
    name = "gl_utils",
    srcs = ["gl_utils.cc"],
    hdrs = ["gl_utils.h"],
    data = glob(["data/*"]),
    linkopts = [
        "-lSDL2",
        "-lGLEW",
        "-lGLU",
        "-lGL",
        "-lglog",
    ],
)

cc_test(
    name = "hello-success_test",
    srcs = ["hello-world.cc"],
    deps = [":hello-lib"],
)

filegroup(
    name = "srcs",
    srcs = ["BUILD"] + glob([
        "**/*.cc",
        "**/*.h",
    ]),
)
