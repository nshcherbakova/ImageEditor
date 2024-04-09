attribute highp vec4 in_position;
attribute mediump vec2 in_texture_coord;
varying mediump vec2 io_texture_coordinates;

void main() {
   gl_Position = in_position;
   io_texture_coordinates = in_texture_coord;
} 