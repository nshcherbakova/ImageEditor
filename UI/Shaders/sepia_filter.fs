uniform sampler2D in_texture;
uniform highp vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

void main() {
  gl_FragColor = texture2D(in_texture, io_texture_coordinates);
  mediump vec3 sep = vec3(  (gl_FragColor.r * 0.3588f) + (gl_FragColor.g * 0.7044f) + (gl_FragColor.b * 0.1368f),
                            (gl_FragColor.r * 0.2990f) + (gl_FragColor.g * 0.5870f) + (gl_FragColor.b * 0.1140f),
                            (gl_FragColor.r * 0.2392f) + (gl_FragColor.g * 0.4696f) + (gl_FragColor.b * 0.0912f));
  gl_FragColor = vec4(sep, 1.0);
}
