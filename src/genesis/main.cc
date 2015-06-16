#include "src/genesis/visualizer.h"

#include <string>

#include <glog/logging.h>

int main(int /* argc */, char** argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;

  genesis::Visualizer visualizer;
  if (!visualizer.Init()) {
    return 1;
  }
  visualizer.Run();
  return 0;
}
