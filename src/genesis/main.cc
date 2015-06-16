#include "src/genesis/visualizer.h"

#include <string>

int main(int argc, char** argv) {
  genesis::Visualizer visualizer;
  visualizer.Init();
  visualizer.Run();
  return 0;
}
