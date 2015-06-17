package(default_visibility = ["//visibility:public"])

cc_binary(
  name = "main",
  srcs = ["main.cc"],
  deps = [
    ":visualizer",
    "//src/third_party/leap_motion:api",
  ],
  linkopts = [
    "-lglog",
  ],
)

cc_library(
  name = "visualizer",
  srcs = [
    "visualizer.cc",
  ],
  hdrs = [
    "visualizer.h",
  ],
  deps = [
    ":gl_utils",
    "//src/third_party/leap_motion:api",
  ],
  data = glob([
    "data/*",
  ]),
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
  srcs = [
    "gl_utils.cc",
  ],
  hdrs = [
    "gl_utils.h",
  ],
  linkopts = [
    "-lSDL2",
    "-lGLEW",
    "-lGLU",
    "-lGL",
    "-lglog",
    "-lm",
  ],
)

cc_test(
  name = "hello-success_test",
  srcs = [
    "hello-world.cc",
  ],
  deps = [
    ":hello-lib",
  ],
)

filegroup(
  name = "srcs",
  srcs = ["BUILD"] + glob([
    "**/*.cc",
    "**/*.h",
  ]),
)
