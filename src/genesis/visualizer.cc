#include "src/genesis/visualizer.h"

#include <iostream>

#include <glog/logging.h>

#include "src/genesis/gl_utils.h"

using std::cout;
using std::endl;
using std::string;

namespace genesis {

namespace {

static const int kWindowWidth = 1024;
static const int kWindowHeight = 768;
static const string kVertexShaderFile = "data/vertex.glsl";
static const string kFragmentShaderFile = "data/fragment.glsl";

}  // namespace


Visualizer::Visualizer()
  : should_run_(true) {}

Visualizer::~Visualizer() {
  SDL_Quit();
}

bool Visualizer::Init() {
  return InitSdl() && InitScene();
}

bool Visualizer::InitSdl() {
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

  window_.reset(
      SDL_CreateWindow(
          "Hand Visualizer",
          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
          kWindowWidth, kWindowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL),
      SDL_DestroyWindow);
  if (!window_) {
    LOG(ERROR) << "Unable to SDL_CreateWindow: " << SDL_GetError();
    return false;
  }

  gl_context_ = SDL_GL_CreateContext(window_.get());
  if (!gl_context_) {
    LOG(ERROR) << "Unable to SDL_GL_CreateContext: " << SDL_GetError();
    return false;
  }

  renderer_.reset(SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED),
      SDL_DestroyRenderer);
  if (!renderer_) {
    LOG(ERROR) << "Unable to SDL_CreateRenderer: " << SDL_GetError();
    return false;
  }

  if (SDL_GL_MakeCurrent(window_.get(), gl_context_) < 0) {
    LOG(ERROR) << "Unable to SDL_GL_MakeCurrent: " << SDL_GetError();
  }

  return true;
}

bool Visualizer::InitScene() {

  program_ = CreateProgram(kVertexShaderFile, kFragmentShaderFile);
  if (program_ < 0) {
    return false;
  }

  return true;
}

void Visualizer::Run() {
  cout << "Let there be light!" << endl;

  SDL_Event event;

  while (should_run_) {
    while (SDL_PollEvent(&event) != 0) {
      HandleEvent(event);
    }

    Update();
    Render();
    SDL_Delay(1);
  }
}

void Visualizer::HandleEvent(const SDL_Event& event) {
  if (event.type == SDL_QUIT) {
    should_run_ = false;
  }
}

void Visualizer::Update() {
}

void Visualizer::Render() {
  SDL_RenderClear(renderer_.get());

  glClearColor(0.5f, 0.5f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  SDL_GL_SwapWindow(window_.get());
}


}  // namespace genesis
