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
