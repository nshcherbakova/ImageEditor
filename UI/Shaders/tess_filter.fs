#version %1

out mediump vec4 FragColor;
in mediump vec2 io_texture_coordinates;

uniform sampler2D in_texture;
uniform highp vec2 in_resolution;

void main() {
        highp vec4 res = vec4(0.0, 0.0, 0.0, 0.0);
        highp float coord = 1.0;
        highp vec2 r = coord/in_resolution.xy;
        highp vec2 uv = io_texture_coordinates;

        res += texture(in_texture, uv + vec2(-1.0, 0.0)*r);
        res += texture(in_texture, uv + vec2(0.0, -1.0)*r);
        res -= texture(in_texture, uv + vec2(1.0, 0.0)*r);
        res -= texture(in_texture, uv + vec2(0.0, 1.0)*r);

        highp vec4 displ = res + 0.5;
        highp vec4 mod_res = displ - floor(displ);
        FragColor = vec4( mod_res.xyz, 1.0);
}
