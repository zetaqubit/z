#ifndef SRC_GENESIS_VISUALIZER_H_
#define SRC_GENESIS_VISUALIZER_H_

#include <memory>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "src/third_party/leap_motion/include/Leap.h"
#include "src/genesis/frame_recorder.h"
#include "src/genesis/gl_window.h"

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

  // GL resources
  GLint program_;
  GLuint raw_left_texture_;
  GLuint raw_right_texture_;
  GLuint distortion_left_texture_;
  GLuint distortion_right_texture_;
  GLUquadric* fingertips_[10];

  bool should_run_;
  bool should_record_;

  // Non-owning pointer to the Leap Motion controller.
  Leap::Controller* controller_;
  Leap::Frame frame_;

  FrameRecorder recorder_;

  GlWindow image_viewer_;
  GlWindow left_image_distorted_viewer_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_VISUALIZER_H_
