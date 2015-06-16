#ifndef SRC_GENESIS_VISUALIZER_H_
#define SRC_GENESIS_VISUALIZER_H_

#include <memory>

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace genesis {

class Visualizer {
 public:
  Visualizer();
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

  bool should_run_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_VISUALIZER_H_
