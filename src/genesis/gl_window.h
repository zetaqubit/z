#ifndef SRC_GENESIS_GL_WINDOW_H_
#define SRC_GENESIS_GL_WINDOW_H_

#include <SDL2/SDL.h>
#include <memory>
#include <string>

namespace genesis {

class GlWindow {
 public:
  GlWindow(std::string window_title, int width, int height);
  void BeginFrame();
  void EndFrame();

 private:
  bool EnsureSdlInitialized();
  bool CreateWindow(std::string window_title, int width, int height);

  // SDL resources.
  SDL_GLContext gl_context_;
  std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> window_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_GL_WINDOW_H_
