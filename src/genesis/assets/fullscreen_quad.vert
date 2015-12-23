#version 120

// Flip y (texture data assumes top-left is (0,0)).
// Normalize from [0, 1]x[0, 1] to [-1, 1]x[-1, 1]
const vec2 a = vec2(2.0, -2.0);
const vec2 b = vec2(-1.0, 1.0);

void main() {
  gl_Position = vec4(a * gl_MultiTexCoord0.xy + b, 0.0, 1.0);
  gl_TexCoord[0] = gl_MultiTexCoord0;
}
