#version %1

out mediump vec4 FragColor;
in mediump vec2 io_texture_coordinates;

uniform sampler2D in_texture;
uniform highp vec2 in_resolution;

void main() {
  FragColor = texture(in_texture, io_texture_coordinates);
  highp float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
  FragColor = vec4(average, average, average, 1.0);
}
