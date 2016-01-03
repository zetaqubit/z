#include "src/genesis/visualization/image_viewer.h"

#include <glog/logging.h>

namespace genesis {

ImageViewer::ImageViewer(const std::string& window_title, int win_w, int win_h)
    : window_(GlWindow(window_title, win_w, win_h)),
      shader_(TextureShader()),
      started_frame_(false) {
  window_.BeginFrame();
  shader_.Init();
  window_.EndFrame();
}

void ImageViewer::StartFrameIfNecessary() {
  if (!started_frame_) {
    window_.BeginFrame();
    started_frame_ = true;
  }
}

ImageViewer& ImageViewer::Update(const Image& image) {
  StartFrameIfNecessary();

  Image scaled_image = image / 256.0f;
  shader_.UpdateTexture(scaled_image.data(), image.width(), image.height());
  shader_.Draw();

  return *this;
}

ImageViewer& ImageViewer::DrawPoint(float x, float y, float r) {
  StartFrameIfNecessary();

  glUseProgram(0);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glPointSize(r);
  glBegin(GL_POINTS);
  glVertex2f(2 * x - 1, 2 * y - 1);
  glEnd();
}

ImageViewer& ImageViewer::DrawCoords(const proto::ScreenCoords& coords) {
  return DrawPoint(coords.u(), 1 - coords.v(), 7.0f);
}

ImageViewer& ImageViewer::DrawHand(const proto::Hand& hand, ImageId id) {
  proto::KeyPoint fingers[] = {
    hand.thumb(), hand.index(), hand.middle(), hand.ring(), hand.pinky()
  };
  for (const proto::KeyPoint& finger : fingers) {
    if (id == LEFT_IMAGE) {
      DrawCoords(finger.left_screen_coords());
    } else if (id == RIGHT_IMAGE) {
      DrawCoords(finger.right_screen_coords());
    }
  }
}

ImageViewer& ImageViewer::UpdateNormalized(const Image& image) {
  return Update((image + 1.0f) * 128.0f);
}

void ImageViewer::EndFrame() {
  window_.EndFrame();
  started_frame_ = false;
}


}  // namespace genesis
