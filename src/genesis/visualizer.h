#ifndef SRC_GENESIS_VISUALIZER_H_
#define SRC_GENESIS_VISUALIZER_H_

#include <memory>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "src/third_party/leap_motion/include/Leap.h"
#include "src/genesis/frame_recorder.h"

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
  bool InitSdl();
  bool InitScene();
  void HandleEvent(const SDL_Event& event);
  void Update();
  void Render();

  // SDL resources.
  std::shared_ptr<SDL_Window> window_;
  SDL_GLContext gl_context_;
  std::shared_ptr<SDL_Renderer> renderer_;

  // GL resources
  GLint program_;
  GLuint raw_left_texture_;
  GLuint raw_right_texture_;
  GLuint distortion_left_texture_;
  GLuint distortion_right_texture_;

  bool should_run_;
  bool should_record_;

  // Non-owning pointer to the Leap Motion controller.
  Leap::Controller* controller_;

  FrameRecorder* recorder_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_VISUALIZER_H_
