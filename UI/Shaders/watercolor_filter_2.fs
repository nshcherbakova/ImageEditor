#version %1

out mediump vec4 FragColor;
in mediump vec2 io_texture_coordinates;

uniform sampler2D in_texture;
uniform highp vec2 in_resolution;

void main() {
        mediump mat3 h = mat3(	vec3(0.0, -0.5, 0.0),
                                vec3(-0.5 , 3.0 ,-0.5),
                                vec3(0.0, -0.5, 0.0));

        highp vec4 res;
        for (mediump int i = 0; i < 3; ++i)
        {
                for (mediump int j = 0; j < 3; ++j)
                {
                        res += texture(in_texture, io_texture_coordinates + vec2(float(i) - 1.0, float(j) - 1.0)/in_resolution) * (h[i][j]);
                }
        }

    FragColor =  vec4(res.xyz, 1.0);
}
