#include "src/genesis/image_viewer.h"

#include <GL/glew.h>
#include <glog/logging.h>

namespace genesis {

ImageViewer::ImageViewer(const std::string& window_title, int win_w, int win_h)
    : window_(GlWindow(window_title, win_w, win_h)),
      shader_(TextureShader()) {
}

void ImageViewer::Init() {
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


}  // namespace genesis
