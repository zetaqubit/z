package(default_visibility = ["//visibility:public"])

cc_binary(
  name = "visualizer",
  srcs = ["visualizer_main.cc"],
  deps = [
    ":visualizer_lib",
    "//src/third_party/glog",
    "//src/third_party/leap_motion:api",
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
    "//src/genesis/io:conversion_utils",
    "//src/genesis/io:frame_recorder",
    "//src/third_party/glog",
    "//src/third_party/gflags",
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
  deps = [
    "//src/third_party/glog",
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
    "//src/third_party/glog",
  ],
  linkopts = [
    "-lSDL2",
    "-lGL",
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
    "//src/genesis/io:datatypes",
    "//src/genesis/io/proto:genesis_protos",
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
  deps = [
    ":gl_utils",
    "//src/third_party/glog",
  ],
  linkopts = [
    "-lGLEW",
  ],
)

