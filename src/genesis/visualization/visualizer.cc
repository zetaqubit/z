#include "src/genesis/visualization/visualizer.h"

#include <glog/logging.h>

#include "src/genesis/io/conversion_utils.h"
#include "src/genesis/visualization/gl_utils.h"

namespace genesis {

namespace {

static const int kWindowWidth = 800;
static const int kAspect = 1.1478;  // Leap device has fov of 2.304 x 2.007
static const int kWindowHeight = kWindowWidth / kAspect;
static const std::string kVertexShaderFile =
    "src/genesis/visualization/shaders/passthrough.vert";
static const std::string kFragmentShaderFile =
    "src/genesis/visualization/shaders/texture_undistort.frag";

static const std::string kProtoDataOutputDirectory =
    "/home/z/hand_tracking/blaze_root/data/genesis/current/proto";

static const std::string kHandnetModel =
    "src/genesis/caffe/handnet_deploy.prototxt";
static const std::string kHandnetWeights =
    "data/genesis/caffe/model_snapshots/handnet_iter_10000.caffemodel";

static const std::string kHandnetSolver =
    "src/genesis/caffe/handnet_solver_deploy.prototxt";
static const std::string kHandnetRestore =
    "data/genesis/caffe/model_snapshots/handnet_iter_10000.solverstate";

static const std::string kMnistModel =
    "src/genesis/caffe/mnist_deploy.prototxt";
static const std::string kMnistWeights =
    "data/genesis/caffe/model_snapshots/mnist_iter_10000.caffemodel";

}  // namespace


Visualizer::Visualizer(Leap::Controller* controller)
  : should_run_(true),
    should_record_(false),
    should_train_(false),
    controller_(controller),
    recorder_(FrameRecorder(kProtoDataOutputDirectory)),
    image_viewer_(GlWindow("Hand Visualizer", kWindowWidth, kWindowHeight)),
    debug_image_viewer_("Left distorted", 640, 480)
{
  LOG(INFO) << "Initializing neural network from model: [" << kHandnetModel
      << "]; weights: [" << kHandnetWeights << "]";
  handnet_.reset(new HandNeuralNet(
      kHandnetSolver, kHandnetRestore
      //kMnistModel, kMnistWeights
  ));
}

Visualizer::~Visualizer() {
  SDL_Quit();
}

bool Visualizer::Init() {
  controller_->setPolicyFlags(Leap::Controller::POLICY_IMAGES);
  image_viewer_.BeginFrame();
  bool ret = InitScene();
  image_viewer_.EndFrame();

  return ret;
}

bool Visualizer::InitScene() {
  if (!shader_.Init()) {
    return false;
  }

  // Setup projection and view matrices.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-0.8, 0.8, -0.8, 0.8, -0.8, 0.8);
  glMatrixMode(GL_MODELVIEW);
  return true;
}

void Visualizer::Run() {
  LOG(INFO) << "Let there be light!";
  LOG(INFO) << "Camera fov: " << controller_->devices()[0].horizontalViewAngle()
      << " x " << controller_->devices()[0].verticalViewAngle();

  SDL_Event event;
  while (should_run_) {
    while (SDL_PollEvent(&event) != 0) {
      HandleEvent(event);
    }

    frame_ = controller_->frame();
    if (!frame_.isValid() || frame_.images().count() < 2) {
      continue;
    }
    Leap::Image left = frame_.images()[0], right = frame_.images()[1];
    if (left.width() <= 0 || left.height() <= 0
       || right.width() <= 0 || right.height() <= 0) {
      continue;
    }

    image_viewer_.BeginFrame();
    Update();
    Render();
    image_viewer_.EndFrame();

    proto::LeapFrame proto = FrameToProto(frame_);

    // Visualize debug image.
    Image image(left.data(), left.width(), left.height());
    debug_image_viewer_.Update(image);
    if (proto.has_left_hand()) {
      debug_image_viewer_.DrawHand(proto.left_hand(), LEFT_IMAGE);
    }
    debug_image_viewer_.EndFrame();

    // Feed the frame to convnet for inference/training.
    int label = proto.has_left_hand() ? 1 : 0;
    ConvertImageToNetInput(&image);
    if (should_train_) {
      handnet_->Train(image, proto);
    } else {
      handnet_->Infer(image, proto);
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
        // r to toggle recording.
        case SDLK_r:
          should_record_ = !should_record_;
          LOG(INFO) << (should_record_ ? "Started" : "Stopped") << " recording";
          break;
        // t to toggle training.
        case SDLK_t:
          should_train_ = !should_train_;
          LOG(INFO) << (should_train_ ? "Started" : "Stopped") << " training";
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
  Leap::Image left = frame_.images()[0];
  Leap::Image right = frame_.images()[1];

  if (should_record_) {
    recorder_.Record(frame_);
  }

  // Update image and distortion textures.
  shader_.UpdateRawTexture(left.data(), left.width(), left.height());
  shader_.UpdateDistortionTexture(left.distortion(), left.distortionWidth() / 2,
                                  left.distortionHeight());

}

void Visualizer::Render() {
  shader_.Draw(kAspect);

  RenderTrackedHand();
  AssertNoGlError("After drawing tracked hand");
}

void Visualizer::DrawWorldPoint(const Leap::Vector& position) {
  Leap::Vector ndc = ProjectToScreenUndistorted(position, frame_.images()[0]);

  // Pixel coordinates from [0, 1] to [-1, 1]
  Leap::Vector pixel(ndc.x * 2 - 1, -(ndc.y * 2 - 1) / kAspect, 0);

  glUseProgram(0);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glPointSize(5.0f);
  glBegin(GL_POINTS);
  glVertex2f(pixel.x, pixel.y);
  glEnd();
}

void Visualizer::RenderTrackedHand() {
  Leap::FingerList fingers = frame_.fingers();

  DrawWorldPoint(frame_.hands()[0].palmPosition());

  for (auto fl = fingers.begin(); fl != fingers.end(); fl++) {
    for(int b = 1; b < 4; b++) {
      Leap::Bone::Type bone_type = static_cast<Leap::Bone::Type>(b);
      Leap::Vector p = (*fl).bone(bone_type).center();
      DrawWorldPoint(p);
    }
  }
}

}  // namespace genesis
