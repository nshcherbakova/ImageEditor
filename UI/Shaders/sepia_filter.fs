#version %1

out mediump vec4 FragColor;
in mediump vec2 io_texture_coordinates;

uniform sampler2D in_texture;
uniform highp vec2 in_resolution;

void main() {
  FragColor = texture(in_texture, io_texture_coordinates);

  mediump vec3 sep = vec3(  (FragColor.r * 0.3588) + (FragColor.g * 0.7044) + (FragColor.b * 0.1368),
                            (FragColor.r * 0.2990) + (FragColor.g * 0.5870) + (FragColor.b * 0.1140),
                            (FragColor.r * 0.2392) + (FragColor.g * 0.4696) + (FragColor.b * 0.0912));
  FragColor = vec4(sep, 1.0);
}
