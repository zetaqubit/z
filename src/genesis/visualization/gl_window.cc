#include "src/genesis/visualization/gl_window.h"

#include <GL/glew.h>
#include <glog/logging.h>

namespace genesis {

GlWindow::GlWindow(const std::string& window_title)
    : window_(nullptr, SDL_DestroyWindow) {
  EnsureSdlInitialized();
  CreateWindow(window_title, 0, 0);
}

GlWindow::GlWindow(const std::string& window_title, int width, int height)
    : window_(nullptr, SDL_DestroyWindow) {
  EnsureSdlInitialized();
  CreateWindow(window_title, width, height);
}

void GlWindow::BeginFrame() {
  if (SDL_GL_MakeCurrent(window_.get(), gl_context_) < 0) {
    LOG(ERROR) << "Unable to SDL_GL_MakeCurrent: " << SDL_GetError();
    return;
  }

  glClearColor(1.f, 1.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GlWindow::EndFrame() {
  SDL_GL_SwapWindow(window_.get());
}

void GlWindow::Resize(int width, int height) {
  SDL_SetWindowSize(window_.get(), width, height);
}

bool GlWindow::EnsureSdlInitialized() {
  if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
    return true;
  }

  SDL_version compiled, linked;
  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);
  LOG(INFO) << "Initializing SDL. Version: compiled - "
      << std::to_string(compiled.major) << "." << std::to_string(compiled.minor)
      << "." << std::to_string(compiled.patch)
      << ", linked - " << std::to_string(linked.major) << "."
      << std::to_string(linked.minor) << "."
      << std::to_string(linked.patch);

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG(ERROR) << "Unable to SDL_Init: " << SDL_GetError();
    return false;
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    LOG(ERROR) << "Unable to SDL_SetHint: " << SDL_GetError();
    return false;
  }

  return true;
}

bool GlWindow::CreateWindow(const std::string& window_title,
                            int width, int height) {
  window_.reset(SDL_CreateWindow(
      window_title.c_str(),
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL));
  if (!window_) {
    LOG(ERROR) << "Unable to SDL_CreateWindow: " << SDL_GetError();
    return false;
  }

  gl_context_ = SDL_GL_CreateContext(window_.get());
  if (!gl_context_) {
    LOG(ERROR) << "Unable to SDL_GL_CreateContext: " << SDL_GetError();
    return false;
  }

  if (SDL_GL_MakeCurrent(window_.get(), gl_context_) < 0) {
    LOG(ERROR) << "Unable to SDL_GL_MakeCurrent: " << SDL_GetError();
    return false;
  }

  // GLEW setup.
  GLint status = glewInit();
  if (status != GLEW_OK) {
    LOG(ERROR) << "Unable to glewInit(): " << glewGetErrorString(status);
    return false;
  }

  // Debugging info.
  LOG(INFO) << "GL_VENDOR: " << glGetString(GL_VENDOR);
  LOG(INFO) << "GL_RENDERER: " << glGetString(GL_RENDERER);
  LOG(INFO) << "GL_VERSION: " << glGetString(GL_VERSION);
  LOG(INFO) << "GLSL_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION);

  return true;
}


}  // namespace genesis
