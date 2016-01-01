#include "src/genesis/visualization/image_viewer.h"

namespace genesis {

ImageViewer::ImageViewer(const std::string& window_title, int win_w, int win_h)
    : window_(GlWindow(window_title, win_w, win_h)),
      shader_(TextureShader()) {
  window_.BeginFrame();
  shader_.Init();
  window_.EndFrame();
}

void ImageViewer::Update(const Image& image) {
  window_.BeginFrame();
  Image scaled_image = image / 256.0f;
  shader_.UpdateTexture(scaled_image.data(), image.width(), image.height());
  shader_.Draw();
  window_.EndFrame();
}

void ImageViewer::UpdateNormalized(const Image& image) {
  Update((image + 1.0f) * 128.0f);
}

}  // namespace genesis
