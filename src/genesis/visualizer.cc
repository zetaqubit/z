#include "src/genesis/visualizer.h"

#include <glog/logging.h>
#include <iostream>

#include "src/genesis/gl_utils.h"

using std::cout;
using std::endl;
using std::string;

namespace genesis {

namespace {

static const int kWindowWidth = 800;
static const int kAspect = 1.1478;  // Leap device has fov of 2.304 x 2.007
static const int kWindowHeight = kWindowWidth / kAspect;
static const string kVertexShaderFile = "src/genesis/assets/passthrough.vert";
static const string kFragmentShaderFile =
    "src/genesis/assets/texture_undistort.frag";

static const string kProtoDataOutputDirectory =
    "/home/z/hand_tracking/blaze_root/data/genesis/current/proto";
}  // namespace


Visualizer::Visualizer(Leap::Controller* controller)
  : should_run_(true),
    should_record_(false),
    controller_(controller),
    recorder_(FrameRecorder(kProtoDataOutputDirectory)),
    image_viewer_(GlWindow("Hand Visualizer", kWindowWidth, kWindowHeight)),
    debug_image_viewer_("Left distorted", 640, 480)
{}

Visualizer::~Visualizer() {
  SDL_Quit();
}

bool Visualizer::Init() {
  controller_->setPolicyFlags(Leap::Controller::POLICY_IMAGES);
  image_viewer_.BeginFrame();
  bool ret = InitScene();
  image_viewer_.EndFrame();

  debug_image_viewer_.Init();

  return ret;
}

bool Visualizer::InitScene() {
  if (!shader_.Init()) {
    return false;
  }

  // Create circles representing fingertips.
  for (int i = 0; i < 10; i++) {
    fingertips_[i] = gluNewQuadric();
  }

  // Setup projection and view matrices.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //SetPerspectiveFrustum(132 /* fov */, kWindowWidth / kWindowHeight,
  //    1 /* near_plane */, 20 /* far_plane */);
  glOrtho(-1, 1, -1, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  return true;
}

void Visualizer::Run() {
  cout << "Let there be light!" << endl;

  SDL_Event event;

  LOG(INFO) << "Camera fov: " << controller_->devices()[0].horizontalViewAngle()
      << " x " << controller_->devices()[0].verticalViewAngle();

  while (should_run_) {
    while (SDL_PollEvent(&event) != 0) {
      HandleEvent(event);
    }

    image_viewer_.BeginFrame();
    Update();
    Render();
    image_viewer_.EndFrame();

    if (frame_.images().count() > 0 && frame_.images()[0].width() > 0) {
      auto left = frame_.images()[0];
      debug_image_viewer_.Update(left.data(), left.width(), left.height());
    }

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
        // Q or Esc exits.
        case SDLK_q:
        case SDLK_ESCAPE:
          should_run_ = false;
          break;
      }
      break;
    case SDL_KEYUP:
      break;
  }
}

void Visualizer::Update() {
  frame_ = controller_->frame();
  Leap::Image left = frame_.images()[0];
  Leap::Image right = frame_.images()[1];
  if (!frame_.isValid() || left.width() <= 0 || left.height() <= 0
      || right.width() <= 0 || right.height() <= 0) {
    LOG(INFO) << "Skipping invalid frame.";
    return;
  }

  if (should_record_) {
    recorder_.Record(frame_);
  }

  // Update image and distortion textures.
  shader_.UpdateRawTexture(left.data(), left.width(), left.height());
  shader_.UpdateDistortionTexture(left.distortion(), left.distortionWidth() / 2,
                                  left.distortionHeight());

}

void Visualizer::Render() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //glTranslatef(0., 0., -10.);

  // Move sensor images away from camera and scale to maintain distance-to-size
  // ratio of 4:1.
  glPushMatrix();
  //glScalef(50., 50., 1.);
  //glTranslatef(0., 0., -10.);

  shader_.Draw(kAspect);

  RenderTrackedHand();
  AssertNoGlError("After drawing tracked hand");

  glPopMatrix();
}

void Visualizer::RenderTrackedHand() {
  // TODO: debug why color is not working.
  glColor3f(0.5f, 0.2f, 0.3f);
  Leap::FingerList fingers = frame_.fingers();
  int id = 0;
  for (auto fl = fingers.begin(); fl != fingers.end(); fl++) {
    //Convert finger tip position to a ray from the camera POV
    Leap::Vector tip = (*fl).tipPosition();
    int i = 0;  // 0 = left, 1 = right.
    float horizontal_slope = -(tip.x + 20 * (2 * i - 1))/tip.y;
    float vertical_slope = tip.z/tip.y;

    // Normalize ray from [-4..4] to [0..1] (the inverse of how the undistorted
    // image was drawn earlier)
    Leap::Image image = frame_.images()[0];
    Leap::Vector ray(horizontal_slope * image.rayScaleX() + image.rayOffsetX(),
        vertical_slope   * image.rayScaleY() + image.rayOffsetY(), 0);

    //Pixel coordinates from [0..1] to [0..width/height]
    Leap::Vector pixel(ray.x * 2 - 1, -(ray.y * 2 - 1) / kAspect, 0);
    //LOG(INFO) << "Finger " << id << " position: "  << pixel.x << ", " << pixel.y;
    glPushMatrix();
    glTranslatef(pixel.x, pixel.y, 0);
    gluDisk(fingertips_[id], 0, 0.01, 10 /* slices */, 1 /* loops */);
    glPopMatrix();
    id++;
    //Leap::Vector pixel(ray.x * targetWidth, ray.y * targetHeight, 0);
    //gl::color(.5, 0, 1, .5);
    //gl::drawSolidCircle(Vec2f(pixel.x + origin.x, pixel.y + origin.y), 5);
  }
}

}  // namespace genesis
