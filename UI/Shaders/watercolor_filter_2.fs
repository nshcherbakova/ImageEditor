uniform sampler2D in_texture;
uniform vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

void main() {
   mediump mat3 h = mat3(vec3(0.0, -1.0, 0.0),
					vec3(-1.0 ,5.0,-1.0),
					vec3(0.0, -1.0, 0.0));

	highp vec4 res;
	for (mediump int i = 0; i < 3; ++i)
	{
		for (mediump int j = 0; j < 3; ++j)
		{
			res += texture2D(in_texture, io_texture_coordinates + vec2(float(i) - 1.0, float(j) - 1.0)/in_resolution) * h[i][j];
		}
	}
   
    gl_FragColor =  vec4(res.xyz, 1.0);
}
