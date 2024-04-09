#version 330 core
in vec4 in_position;
in vec2 in_texture_coord;

out vec2 io_texture_coordinates;

void main() {
   gl_Position = in_position;
   io_texture_coordinates = in_texture_coord;
}
