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
static const string kVertexShaderFile = "src/genesis/data/vertex.glsl";
static const string kFragmentShaderFile = "src/genesis/data/fragment.glsl";

static const string kDataOutputDirectory = "/tmp/hand_tracking_output";

}  // namespace


Visualizer::Visualizer(Leap::Controller* controller)
  : should_run_(true),
    should_record_(false),
    controller_(controller),
    recorder_(new FrameRecorder(kDataOutputDirectory))
{}

Visualizer::~Visualizer() {
  SDL_Quit();
}

bool Visualizer::Init() {
  controller_->setPolicyFlags(Leap::Controller::POLICY_IMAGES);
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
    return false;
  }

  // GLEW setup.
  GLint status = glewInit();
  if (status != GLEW_OK) {
    LOG(ERROR) << "Unable to glewInit(): " << glewGetErrorString(status);
    return false;
  }

  // Debugging info.
  LOG(ERROR) << "GL_VENDOR: " << glGetString(GL_VENDOR);
  LOG(ERROR) << "GL_RENDERER: " << glGetString(GL_RENDERER);
  LOG(ERROR) << "GL_VERSION: " << glGetString(GL_VERSION);
  LOG(ERROR) << "GLSL_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION);

  return true;
}

bool Visualizer::InitScene() {

  // Create the program.
  program_ = CreateProgram(kVertexShaderFile, kFragmentShaderFile);
  if (program_ < 0) {
    return false;
  }
  glUseProgram(program_);
  GLuint raw_sampler = glGetUniformLocation(program_, "rawTexture");
  GLuint distortion_sampler = glGetUniformLocation(program_, "distortionTexture");
  glUniform1i(raw_sampler, 0);
  glUniform1i(distortion_sampler, 1);

  // Create the textures.
  raw_left_texture_ = CreateTextureReference();
  raw_right_texture_ = CreateTextureReference();
  distortion_left_texture_ = CreateTextureReference();
  distortion_right_texture_ = CreateTextureReference();

  // Setup projection and view matrices.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  SetPerspectiveFrustum(110 /* fov */, 2 * kWindowWidth / kWindowHeight,
      1 /* near_plane */, 20 /* far_plane */);
  glMatrixMode(GL_MODELVIEW);

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
  switch (event.type) {
    case SDL_QUIT:
      should_run_ = false;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_r:
          should_record_ = !should_record_;
          LOG(INFO) << (should_record_ ? "Started" : "Stopped") << " recording";
          break;
      }
      break;
    case SDL_KEYUP:
      break;
  }
}

void Visualizer::Update() {
  Leap::Frame frame = controller_->frame();
  Leap::Image left = frame.images()[0];
  Leap::Image right = frame.images()[1];
  if (!frame.isValid() || left.width() <= 0 || left.height() <= 0
      || right.width() <= 0 || right.height() <= 0) {
    LOG(INFO) << "Skipping invalid frame.";
    return;
  }

  if (should_record_) {
    recorder_->Record(frame);
  }

  // Update image and distortion textures.
  glBindTexture(GL_TEXTURE_2D, raw_left_texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, left.width(), left.height(), 0,
      GL_RED, GL_UNSIGNED_BYTE, left.data());
  glBindTexture(GL_TEXTURE_2D, distortion_left_texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, left.distortionWidth() / 2,
      left.distortionHeight(), 0, GL_RG, GL_FLOAT, left.distortion());

  glBindTexture(GL_TEXTURE_2D, raw_right_texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, right.width(), right.height(), 0,
      GL_RED, GL_UNSIGNED_BYTE, right.data());
  glBindTexture(GL_TEXTURE_2D, distortion_right_texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, right.distortionWidth() / 2,
      right.distortionHeight(), 0, GL_RG, GL_FLOAT, right.distortion());
}

void Visualizer::Render() {
  SDL_RenderClear(renderer_.get());
  glClearColor(1.f, 1.f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0., 0., -10.);

  // Move sensor images away from camera and scale to maintain distance-to-size
  // ratio of 4:1.
  glPushMatrix();
  glScalef(80., 80., 1.);
  glTranslatef(0., 0., -10.);

  glEnable(GL_TEXTURE_2D);
  glUseProgram(program_);

  // Draw the left image.
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, raw_left_texture_);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, distortion_left_texture_);
  glBegin(GL_QUADS);
  glTexCoord2f(0.f, 1.f); glVertex3f(-1.f,  1.f, 0.f); // Top Left
  glTexCoord2f(1.f, 1.f); glVertex3f( 1.f,  1.f, 0.f); // Top Right
  glTexCoord2f(1.f, 0.f); glVertex3f( 1.f, -1.f, 0.f); // Bottom Right
  glTexCoord2f(0.f, 0.f); glVertex3f(-1.f, -1.f, 0.f); // Bottom Left
  glEnd();

  glPopMatrix();

  SDL_GL_SwapWindow(window_.get());
}


}  // namespace genesis
