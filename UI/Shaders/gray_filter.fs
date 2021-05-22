uniform sampler2D in_texture;
uniform highp vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

void main() {
  gl_FragColor = texture2D(in_texture, io_texture_coordinates);
  highp float average = 0.2126 * gl_FragColor.r + 0.7152 * gl_FragColor.g + 0.0722 * gl_FragColor.b;
  gl_FragColor = vec4(average, average, average, 1.0);
}
