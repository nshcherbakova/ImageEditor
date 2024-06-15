#version %1

out mediump vec4 FragColor;
in mediump vec2 io_texture_coordinates;

uniform sampler2D in_texture;
uniform sampler2D noise_texture;
uniform highp vec2 in_resolution;

void main() {

    highp float avg = dot( dot( textureLod(in_texture, io_texture_coordinates, 2.4).rgb, vec3(0.333)*2.0 )
                   , dot( texture(noise_texture, io_texture_coordinates).rgb, vec3(0.333) )
                   );

    highp float vig = 1.0 - distance(io_texture_coordinates, vec2(0.5));

    highp vec3 col = vec3(1.0) * vig * avg * 1.4;
    FragColor = vec4(col, 1.0);


    mediump vec3 sep = vec3(  (FragColor.r * 0.3588) + (FragColor.g * 0.7044) + (FragColor.b * 0.1368),
                              (FragColor.r * 0.2990) + (FragColor.g * 0.5870) + (FragColor.b * 0.1140),
                              (FragColor.r * 0.2392) + (FragColor.g * 0.4696) + (FragColor.b * 0.0912));
    FragColor = vec4(sep, 1.0);

}
