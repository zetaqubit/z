#include "src/genesis/visualization/texture_shader.h"

#include <glog/logging.h>
#include <string>

#include "src/genesis/visualization/gl_utils.h"

namespace {

static const std::string kVertexShaderFile =
    "src/genesis/visualization/shaders/fullscreen_quad.vert";
static const std::string kFragmentShaderFile =
    "src/genesis/visualization/shaders/texture.frag";

}  // namespace

namespace genesis {

bool TextureShader::Init() {
  // Create the program.
  program_ = CreateProgram(kVertexShaderFile, kFragmentShaderFile);
  if (program_ < 0) {
    return false;
  }
  glUseProgram(program_);
  GLuint texture_handle = glGetUniformLocation(program_, "texture");
  glUniform1i(texture_handle, 0);

  // Create the textures.
  texture_ = CreateTextureReference();

  return true;
}

void TextureShader::UpdateTexture(const uint8_t* bytes, int width, int height) {
  glBindTexture(GL_TEXTURE_2D, texture_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED,
               GL_UNSIGNED_BYTE, bytes);
}

void TextureShader::Draw() {
  glEnable(GL_TEXTURE_2D);
  glUseProgram(program_);
  AssertNoGlError("glUseProgram");

  // Draw the left image.
  glActiveTexture(GL_TEXTURE0);
  AssertNoGlError("glActiveTexture");
  glBindTexture(GL_TEXTURE_2D, texture_);
  AssertNoGlError("glBindTexture");
  glBegin(GL_QUADS);
  float a = 1;
  glTexCoord2f(0.f, 1.f); glVertex3f(-1.f,  a, 0.f); // Top Left
  glTexCoord2f(1.f, 1.f); glVertex3f( 1.f,  a, 0.f); // Top Right
  glTexCoord2f(1.f, 0.f); glVertex3f( 1.f, -a, 0.f); // Bottom Right
  glTexCoord2f(0.f, 0.f); glVertex3f(-1.f, -a, 0.f); // Bottom Left
  glEnd();
  AssertNoGlError("After drawing quad");
}

}  // namespace genesis
