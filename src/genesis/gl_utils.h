#ifndef SRC_GENESIS_GL_UTILS_H_
#define SRC_GENESIS_GL_UTILS_H_

#include <string>

#include <GL/glew.h>

namespace genesis {

using std::string;

void AssertNoGlError(std::string msg = "");

GLint CreateProgram(const string& vertex_file, const string& fragment_file);
GLint CompileShader(GLenum shader_type, const string& source_filename);
bool ReadFileContents(const string& filename, string* contents);

GLuint CreateTextureReference();
void SetPerspectiveFrustum(
    GLdouble fov_y, GLdouble aspect, GLdouble near_plane, GLdouble far_plane);

}  // namespace genesis

#endif  // SRC_GENESIS_GL_UTILS_H_
