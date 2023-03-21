uniform sampler2D in_texture;
uniform highp vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

void main() {
  gl_FragColor = texture2D(in_texture, io_texture_coordinates);

  mediump vec3 sep = vec3(  (gl_FragColor.r * 0.3588) + (gl_FragColor.g * 0.7044) + (gl_FragColor.b * 0.1368),
                            (gl_FragColor.r * 0.2990) + (gl_FragColor.g * 0.5870) + (gl_FragColor.b * 0.1140),
                            (gl_FragColor.r * 0.2392) + (gl_FragColor.g * 0.4696) + (gl_FragColor.b * 0.0912));
  gl_FragColor = vec4(sep, 1.0);
}
