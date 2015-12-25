#include "src/genesis/visualization/image_viewer.h"

#include <GL/glew.h>
#include <glog/logging.h>
#include <vector>

namespace genesis {

ImageViewer::ImageViewer(const std::string& window_title, int win_w, int win_h)
    : window_(GlWindow(window_title, win_w, win_h)),
      shader_(TextureShader()) {
  window_.BeginFrame();
  shader_.Init();
  window_.EndFrame();
}

void ImageViewer::Update(const uint8_t* data, int width, int height) {
  window_.BeginFrame();
  shader_.UpdateTexture(data, width, height);
  shader_.Draw();
  window_.EndFrame();
}

void ImageViewer::UpdateNormalized(const float* data, int width, int height) {
  std::vector<uint8_t> converted(width * height);
  for (int i = 0; i < width * height; i++) {
    converted[i] = static_cast<uint8_t>(128 * (1.0f + data[i]));
  }
  Update(converted.data(), width, height);
}

}  // namespace genesis
