uniform sampler2D in_texture;
uniform vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

void main() {
    gl_FragColor =  texture2D( texture, texture_coordinates);
}
