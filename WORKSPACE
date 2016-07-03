android_sdk_repository(
    name = "androidsdk",
    api_level = 23,
    build_tools_version = "23.0.2",
    # Replace with path to Android SDK on your system
    path = "/home/z/Android/Sdk",
)

android_ndk_repository(
    name="androidndk",
    path="/home/z/Android/ndk",
    api_level=21)

local_repository(
  name = "tf",
  path = __workspace_dir__ + "/tensorflow",
)

load('//tensorflow/tensorflow:workspace.bzl', 'tf_workspace')
tf_workspace('tensorflow/', '@tf')
