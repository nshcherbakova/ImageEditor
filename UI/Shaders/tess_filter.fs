uniform sampler2D in_texture;
uniform highp vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

void main() {
	highp vec4 res;
	res += texture2D(in_texture, io_texture_coordinates + vec2(-1.0, 0.0)/in_resolution);
	res += texture2D(in_texture, io_texture_coordinates + vec2(0.0, -1.0)/in_resolution);
	res -= texture2D(in_texture, io_texture_coordinates + vec2(1.0, 0.0)/in_resolution);
	res -= texture2D(in_texture, io_texture_coordinates + vec2(0.0, 1.0)/in_resolution);
	
        highp vec4 displ = res + 0.5;
        highp vec4 mod_res = displ - floor(displ);
	gl_FragColor = vec4( mod_res.xyz, 1.0);
}
