#ifndef SRC_GENESIS_VISUALIZATION_IMAGE_VIEWER_H_
#define SRC_GENESIS_VISUALIZATION_IMAGE_VIEWER_H_

#include <string>

#include "src/genesis/io/datatypes.h"
#include "src/genesis/io/proto/leap_frame.pb.h"
#include "src/genesis/visualization/gl_window.h"
#include "src/genesis/visualization/texture_shader.h"

namespace genesis {

class ImageViewer {
 public:
  ImageViewer(const std::string& window_title, int win_width, int win_height);

  // Displays an image in range [0, 256).
  ImageViewer& Update(const Image& image);

  // Displays an image in range (-1, 1).
  ImageViewer& UpdateNormalized(const Image& image);

  // (0, 0) is bottom-left, (1, 1) is top right. r is in pixels.
  ImageViewer& DrawPoint(float x, float y, float r);
  ImageViewer& DrawHand(const proto::Hand& hand, ImageId id);

  void EndFrame();

 private:
  void StartFrameIfNecessary();
  ImageViewer& DrawCoords(const proto::ScreenCoords& coords);

  GlWindow window_;
  TextureShader shader_;
  bool started_frame_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_VISUALIZATION_IMAGE_VIEWER_H_
