#version %1
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texture_coord;

out mediump vec2 io_texture_coordinates;

void main()
{
  gl_Position = vec4(in_position, 1.0);
  io_texture_coordinates = in_texture_coord;
}
