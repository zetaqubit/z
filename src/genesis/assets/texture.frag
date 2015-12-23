#version 120

precision mediump float;

uniform sampler2D texture;

void main() {
  gl_FragColor = vec4(texture2D(texture, gl_TexCoord[0].st).rrr, 1.0);
}
