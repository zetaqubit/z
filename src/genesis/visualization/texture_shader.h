#ifndef SRC_GENESIS_VISUALIZATION_TEXTURE_SHADER_H_
#define SRC_GENESIS_VISUALIZATION_TEXTURE_SHADER_H_

#include <GL/glew.h>

namespace genesis {

class TextureShader {
 public:
  bool Init();
  void UpdateTexture(const uint8_t* bytes, int width, int height);
  void Draw();

 private:
  GLint program_;
  GLuint texture_;
};

}  // namespace genesis

#endif  // SRC_GENESIS_VISUALIZATION_TEXTURE_SHADER_H_
