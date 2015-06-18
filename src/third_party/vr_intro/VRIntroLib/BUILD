cc_library(
  name = "vr_intro_lib",
  srcs = glob([
    "**/*.cpp",
  ]),
  hdrs = glob([
    "**/*.h",
  ]),
  deps = [
    "//src/third_party/leap_motion:api",
  ],
  linkopts = [
    "-lSDL2",
    "-lGLEW",
    "-lGLU",
    "-lGL",
    "-lglog",
  ],
)
