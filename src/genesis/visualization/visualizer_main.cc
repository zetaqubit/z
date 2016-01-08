#include "src/genesis/visualization/visualizer.h"

#include <string>

#include "src/third_party/gflags/include/gflags/gflags.h"
#include "src/third_party/glog/src/glog/logging.h"
#include "src/third_party/leap_motion/include/Leap.h"

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  Leap::Controller controller;
  while (!controller.isConnected()) {
    // wait for connection.
  }

  genesis::Visualizer visualizer(&controller);
  if (!visualizer.Init()) {
    return 1;
  }
  visualizer.Run();
  return 0;
}
