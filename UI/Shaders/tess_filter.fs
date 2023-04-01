uniform sampler2D in_texture;
uniform highp vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

void main() {
        highp vec4 res;
        highp float coord = 1.0;
        highp vec2 r = coord/in_resolution.xy;
        highp vec2 uv = io_texture_coordinates;
        highp vec4 Color = texture2D(in_texture, uv);

        res += texture2D(in_texture, uv + vec2(-1.0, 0.0)*r);
        res += texture2D(in_texture, uv + vec2(0.0, -1.0)*r);
        res -= texture2D(in_texture, uv + vec2(1.0, 0.0)*r);
        res -= texture2D(in_texture, uv + vec2(0.0, 1.0)*r);

        highp vec4 displ = res + 0.5;
        highp vec4 mod_res = displ - floor(displ);
        gl_FragColor = vec4( mod_res.xyz, 1.0);
}
