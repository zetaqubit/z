package(default_visibility = ["//visibility:public"])

cc_library(
    name = "visualizer",
    srcs = ["visualizer.cc"],
    hdrs = ["visualizer.h"],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [":visualizer"],
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
