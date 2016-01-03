#ifndef SRC_GENESIS_VISUALIZATION_VISUALIZER_H_
#define SRC_GENESIS_VISUALIZATION_VISUALIZER_H_

#include <memory>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "src/genesis/caffe/hand_neural_net.h"
#include "src/genesis/io/frame_recorder.h"
#include "src/genesis/visualization/gl_window.h"
#include "src/genesis/visualization/image_viewer.h"
#include "src/genesis/visualization/undistorted_texture_shader.h"
#include "src/third_party/leap_motion/include/Leap.h"

namespace genesis {

class Visualizer {
 public:

  // @param controller The Leap Motion controller whose images and hand output
  //        we are visualizing. Does not take ownership.
  Visualizer(Leap::Controller* controller);
  ~Visualizer();
  bool Init();
  void Run();

 private:
  bool InitScene();
  void HandleEvent(const SDL_Event& event);
  void Update();
  void Render();
  void RenderTrackedHand();
  void DrawWorldPoint(const Leap::Vector& position);

  bool should_run_;
  bool should_record_;
  bool should_train_;

  // Non-owning pointer to the Leap Motion controller.
  Leap::Controller* controller_;
  Leap::Frame frame_;

  FrameRecorder recorder_;

  UndistortedTextureShader shader_;
  GlWindow image_viewer_;
  ImageViewer debug_image_viewer_;

  std::unique_ptr<HandNeuralNet> handnet_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_VISUALIZATION_VISUALIZER_H_
