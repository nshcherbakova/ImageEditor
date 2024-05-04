#version %1

out mediump vec4 FragColor;
in mediump vec2 io_texture_coordinates;

uniform sampler2D in_texture;
uniform highp vec2 in_resolution;


void main() {
    highp float colors = 4.0;
    highp float dither = 0.01;

    highp vec4 color = texture(in_texture, io_texture_coordinates);

    highp float a = floor(mod(io_texture_coordinates.x, 2.0));
    highp float b = floor(mod(io_texture_coordinates.y, 2.0));
    highp float c = mod(a + b, 2.0);

    FragColor.r = (round(color.r * colors + dither) / colors) * c;
    FragColor.g = (round(color.g * colors + dither) / colors) * c;
    FragColor.b = (round(color.b * colors + dither) / colors) * c;
    c = 1.0 - c;
    FragColor.r += (round(color.r * colors - dither) / colors) * c;
    FragColor.g += (round(color.g * colors - dither) / colors) * c;
    FragColor.b += (round(color.b * colors - dither) / colors) * c;

    FragColor.a = 1.0;
}
