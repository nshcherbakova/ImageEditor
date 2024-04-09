uniform sampler2D in_texture;
uniform sampler2D random_texture;
uniform mediump vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

void main() {
    mediump vec2 uv = io_texture_coordinates.xy ;
    mediump vec2 n = texture2D(random_texture, uv * .5).rg;
    gl_FragColor = texture2D(in_texture, uv, 2.5   );
    for (mediump float r = 4.; r > 0.; r--) {
        mediump vec2 x = in_resolution.xy * r * .015;
        mediump vec2 p = 6.28 * uv * x + (n - .5) * 2.;
        mediump vec2 s = sin(p);
        mediump vec4 d = texture2D(random_texture, floor(uv * x - 0.25 + 0.5) / x);
        mediump float t = (s.x + s.y) * max(0.,1.-fract(100.0 * (d.b+.1)+d.g) * 2.);

        if (d.r < (5.-r) * .08 && t > .5) {
            mediump vec3 v = normalize(-vec3(cos(p), mix(.2, 2., t-.5)));
            gl_FragColor = texture2D(in_texture, uv + v.xy * .3);
        }
    }
}
