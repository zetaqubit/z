package(default_visibility = ["//visibility:public"])

cc_binary(
  name = "visualizer",
  srcs = ["visualizer_main.cc"],
  deps = [
    ":visualizer_lib",
    "//src/third_party/leap_motion:api",
  ],
  linkopts = [
    "-lglog",
  ],
)

cc_library(
  name = "visualizer_lib",
  srcs = [
    "visualizer.cc",
  ],
  hdrs = [
    "visualizer.h",
  ],
  deps = [
    ":gl_utils",
    ":gl_window",
    ":image_viewer",
    ":shaders",
    "//src/genesis/caffe:handnet_inference",
    "//src/genesis/io:frame_recorder",
    "//src/third_party/leap_motion:api",
  ],
  data = glob([
    "shaders/**",
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
    "-lGLEW",
    "-lm",
  ],
)

cc_library(
  name = "gl_window",
  srcs = [
    "gl_window.cc",
  ],
  hdrs = [
    "gl_window.h",
  ],
  deps = [
    ":gl_utils",
  ],
  linkopts = [
    "-lSDL2",
    "-lGL",
    "-lglog",
  ],
)

cc_library(
  name = "image_viewer",
  srcs = [
    "image_viewer.cc",
  ],
  hdrs = [
    "image_viewer.h",
  ],
  deps = [
    ":shaders",
    ":gl_window",
  ],
  data = glob([
    "shaders/**",
  ]),
)

cc_library(
  name = "shaders",
  srcs = [
    "texture_shader.cc",
    "undistorted_texture_shader.cc",
  ],
  hdrs = [
    "texture_shader.h",
    "undistorted_texture_shader.h",
  ],
  linkopts = [
    "-lGLEW",
    "-lglog",
  ],
)

