package(default_visibility = ["//visibility:public"])

cc_binary(
  name = "visualizer",
  srcs = ["main.cc"],
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
    ":frame_recorder",
    ":gl_utils",
    ":gl_window",
    ":image_viewer",
    ":shaders",
    "//src/third_party/leap_motion:api",
  ],
  data = glob([
    "assets/**",
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
    "assets/**",
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

cc_library(
  name = "frame_recorder",
  srcs = [
    "frame_recorder.cc",
  ],
  hdrs = [
    "frame_recorder.h",
  ],
  deps = [
    ":lmdb_storage",
    "//src/third_party/leap_motion:api",
    "//src/genesis/proto:genesis_protos",
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
  name = "lmdb_storage",
  srcs = [
    "lmdb_storage.cc"
  ],
  hdrs = [
    "lmdb_storage.h"
  ],
  deps = [
    ":image_viewer",  # for debugging
    "//src/genesis/proto:genesis_protos",
    "//src/third_party/caffe:caffe_protos"
  ],
  linkopts = [
    "-lglog",
    "-llmdb",
  ],
)

cc_library(
  name = "proto_to_lmdb_converter",
  srcs = [
    "proto_to_lmdb_converter.cc",
  ],
  hdrs = [
    "proto_to_lmdb_converter.h",
  ],
  deps = [
    ":lmdb_storage",
    "//src/genesis/proto:genesis_protos",
  ],
  linkopts = [
    "-lglog",
  ],
)

cc_binary(
  name = "converter",
  srcs = [
    "proto_to_lmdb_converter_main.cc",
  ],
  deps = [
    ":proto_to_lmdb_converter",
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
