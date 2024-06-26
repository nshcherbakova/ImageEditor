// Used part of Heartfelt - by Martijn Steinrucken aka BigWings - 2017
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.

uniform sampler2D in_texture;
uniform highp vec2 in_resolution;
varying highp vec2 io_texture_coordinates;



#define S(a, b, t) smoothstep(a, b, t)


highp vec3 N13(float p) {
    //  from DAVE HOSKINS
   highp vec3 p3 = fract(vec3(p) * vec3(.1031,.11369,.13787));
   p3 += dot(p3, p3.yzx + 19.19);
   return fract(vec3((p3.x + p3.y)*p3.z, (p3.x+p3.z)*p3.y, (p3.y+p3.z)*p3.x));
}

highp vec4 N14(float t) {
        return fract(sin(t*vec4(123., 1024., 1456., 264.))*vec4(6547., 345., 8799., 1564.));
}
highp float N(float t) {
    return fract(sin(t*12345.564)*7658.76);
}

highp float Saw(float b, float t) {
        return S(0., b, t)*S(1., b, t);
}


highp vec2 DropLayer2(vec2 uv, float t) {
    highp vec2 UV = uv;

    uv.y += t*0.75;
    highp vec2 a = vec2(6., 1.);
    highp vec2 grid = a*2.;
    highp vec2 id = floor(uv*grid);

    highp float colShift = N(id.x);
    uv.y += colShift;

    id = floor(uv*grid);
    highp vec3 n = N13(id.x*35.2+id.y*2376.1);
    highp vec2 st = fract(uv*grid)-vec2(.5, 0);

    highp float x = n.x-.5;

    highp float y = UV.y*20.;
    highp float wiggle = sin(y+sin(y));
    x += wiggle*(.5-abs(x))*(n.z-.5);
    x *= .7;
    highp float ti = fract(t+n.z);
    y = (Saw(.85, ti)-.5)*.9+.5;
    vec2 p = vec2(x, y);

    highp float d = length((st-p)*a.yx);

    highp float mainDrop = S(.4, .0, d);

    highp float r = sqrt(S(1., y, st.y));
    highp float cd = abs(st.x-x);
    highp float trail = S(.23*r, .15*r*r, cd);
    highp float trailFront = S(-.02, .02, st.y-y);
    trail *= trailFront*r*r;

    y = UV.y;
    highp float trail2 = S(.2*r, .0, cd);
    highp float droplets = max(0., (sin(y*(1.-y)*120.)-st.y))*trail2*trailFront*n.z;
    y = fract(y*10.)+(st.y-.5);
    highp float dd = length(st-vec2(x, y));
    droplets = S(.3, 0., dd);
    highp float m = mainDrop+droplets*r*trailFront;

    //m += st.x>a.y*.45 || st.y>a.x*.165 ? 1.2 : 0.;
    return highp vec2(m, trail);
}

highp float StaticDrops(vec2 uv, float t) {
        uv *= 40.;

    highp vec2 id = floor(uv);
    uv = fract(uv)-.5;
    highp vec3 n = N13(id.x*107.45+id.y*3543.654);
    highp vec2 p = (n.xy-.5)*.7;
    highp float d = length(uv-p);

    highp float fade = Saw(.025, fract(t+n.z));
    highp float c = S(.3, 0., d)*fract(n.z*10.)*fade;
    return c;
}

highp vec2 Drops(vec2 uv, float t, float l0, float l1, float l2) {
    highp float s = StaticDrops(uv, t)*l0;
    highp vec2 m1 = DropLayer2(uv, t)*l1;
    highp vec2 m2 = DropLayer2(uv*1.85, t)*l2;

    highp float c = s+m1.x+m2.x;
    c = S(.3, 1., c);

    return highp vec2(c, max(m1.y*l0, m2.y*l1));
}

void main()
{
    highp vec2 fragCoord = io_texture_coordinates.xy*in_resolution.xy;
    highp vec2 uv = (fragCoord.xy-.5*in_resolution.xy) / in_resolution.y;

    highp vec2 UV = fragCoord.xy/in_resolution.xy;
    highp vec3 M = vec3(1.0,2.0,0.0)/vec3(in_resolution, 1.0);
   highp  float T = 2500.0+M.x*2.;


    highp float t = T*.2;

    highp float rainAmount =  sin(T*.05)*.3+.7;

    highp float maxBlur = mix(3., 6., rainAmount);
   highp  float minBlur = 2.;

    highp float zoom = 1.0;
    uv *= .7+zoom*.3;

    UV = (UV-.5)*(.9+zoom*.1)+.5;

    highp float staticDrops = S(-.5, 1., rainAmount)*2.;
    highp float layer1 = S(.25, .75, rainAmount);
    highp float layer2 = S(.0, .5, rainAmount);


    highp vec2 c = Drops(uv, t, staticDrops, layer1, layer2);

        highp vec2 e = vec2(.001, 0.);
        highp float cx = Drops(uv+e, t, staticDrops, layer1, layer2).x;
        highp float cy = Drops(uv+e.yx, t, staticDrops, layer1, layer2).x;
        highp vec2 n = vec2(cx-c.x, cy-c.x);		// expensive normals



    highp float focus = mix(maxBlur-c.y, minBlur, S(.1, .2, c.x));
    highp vec3 col = texture2D(in_texture, UV+n, focus).rgb;

    gl_FragColor = vec4(col, 1.);
}
/*
#define S(a, b, t) smoothstep(a, b, t)

highp vec3 N13(highp float p) {
    //  from DAVE HOSKINS
   highp vec3 p3 = fract(vec3(p) * vec3(.1031,.11369,.13787));
   p3 += dot(p3, p3.yzx + 19.19);
   return fract(vec3((p3.x + p3.y)*p3.z, (p3.x+p3.z)*p3.y, (p3.y+p3.z)*p3.x));
}

highp vec4 N14(highp float t) {
        return fract(sin(t*vec4(123., 1024., 1456., 264.))*vec4(6547., 345., 8799., 1564.));
}

highp float N(highp float t) {
    return fract(sin(t*12345.564)*7658.76);
}

highp float Saw(highp float b, highp  float t) {
        return S(0., b, t)*S(1., b, t);
}

highp vec2 DropLayer2(highp vec2 uv, highp float t) {
    highp vec2 UV = uv;

    uv.y += t*0.75;
    highp vec2 a = vec2(6., 1.);
    highp vec2 grid = a*2.;
    highp vec2 id = floor(uv*grid);

    highp float colShift = N(id.x);
    uv.y += colShift;

    id = floor(uv*grid);
    highp vec3 n = N13(id.x*35.2+id.y*2376.1);
    highp vec2 st = fract(uv*grid)-vec2(.5, 0);

    highp float x = n.x-.5;

    highp float y = UV.y*20.;
    highp float wiggle = sin(y+sin(y));
    x += wiggle*(.5-abs(x))*(n.z-.5);
    x *= .7;
    highp float ti = fract(t+n.z);
    y = (Saw(.85, ti)-.5)*.9+.5;
    highp vec2 p = vec2(x, y);

    highp float d = length((st-p)*a.yx);

    highp float mainDrop = S(.4, .0, d);

    highp float r = sqrt(S(1., y, st.y));
    highp float cd = abs(st.x-x);
    highp float trail = S(.23*r, .15*r*r, cd);
    highp float trailFront = S(-.02, .02, st.y-y);
    trail *= trailFront*r*r;

    y = UV.y;
    highp float trail2 = S(.2*r, .0, cd);
    highp float droplets = max(0., (sin(y*(1.-y)*120.)-st.y))*trail2*trailFront*n.z;
    y = fract(y*10.)+(st.y-.5);
    highp float dd = length(st-vec2(x, y));
    droplets = S(.3, 0., dd);
    highp float m = mainDrop+droplets*r*trailFront;

    //m += st.x>a.y*.45 || st.y>a.x*.165 ? 1.2 : 0.;
    return vec2(m, trail);
}

highp float StaticDrops(highp vec2 uv, highp float t) {
        uv *= 40.;

    highp vec2 id = floor(uv);
    uv = fract(uv)-.5;
    highp vec3 n = N13(id.x*107.45+id.y*3543.654);
    highp vec2 p = (n.xy-.5)*.7;
    highp float d = length(uv-p);

    highp  float fade = Saw(.025, fract(t+n.z));
    highp float c = S(.3, 0., d)*fract(n.z*10.)*fade;
    return c;
}

highp vec2 Drops(highp vec2 uv, highp float t, highp float l0, highp float l1, highp float l2) {
    highp float s = StaticDrops(uv, t)*l0;
    highp vec2 m1 = DropLayer2(uv, t)*l1;
    highp vec2 m2 = DropLayer2(uv*1.85, t)*l2;

    highp float c = s+m1.x+m2.x;
    c = S(.3, 1., c);

    return vec2(c, max(m1.y*l0, m2.y*l1));
}

void main(  )
{
    highp vec2 fragCoord = io_texture_coordinates;
    highp vec3 iMouse = vec3(0.0, 0.0, 0.0);
    highp float iTime = 2500.0;
    highp vec2 uv = fragCoord;
    uv.x = (uv.x -0.5)*in_resolution.x/in_resolution.y;
    uv.y = uv.y - 0.5;
    highp vec2 UV = fragCoord;
    highp vec3 M = iMouse.xyz;
    highp float T = iTime+M.x*2.;

    highp float t = T*.2;

    highp float rainAmount = iMouse.z>0. ? M.y : sin(T*.05)*.3+.7;

    highp float maxBlur = 6.0;
    highp float minBlur = 4.0;

    highp float zoom = 1.0;
    uv *= .7+zoom*.3;

    UV = (UV-.5)*(.9+zoom*.1)+.5;

    highp float staticDrops = S(-.5, 1., rainAmount)*2.;
    highp float layer1 = S(.25, .75, rainAmount);
    highp float layer2 = S(.0, .5, rainAmount);


    highp vec2 c = Drops(uv, t, staticDrops, layer1, layer2);

    highp vec2 e = vec2(.001, 0.);
    highp float cx = Drops(uv+e, t, staticDrops, layer1, layer2).x;
    highp float cy = Drops(uv+e.yx, t, staticDrops, layer1, layer2).x;
    highp vec2 n = vec2(cx-c.x, cy-c.x);		// expensive normals

    highp float focus = mix(maxBlur-c.y, minBlur, S(.1, .2, c.x));
    highp vec3 col = texture2D(in_texture, UV+n, focus).rgb;

    gl_FragColor = vec4(col, 1.);
}
*/
/* variant 2
uniform sampler2D in_texture;
uniform sampler2D random_texture;
uniform highp vec2 in_resolution;
varying highp vec2 io_texture_coordinates;

void main() {
    highp vec2 uv = io_texture_coordinates.xy;
    highp vec2 n = texture2D(random_texture, uv * .5).rg;
    gl_FragColor = texture2D(in_texture, uv, 2.5   );
    for (highp float r = 4.; r > 0.; r--) {
        highp vec2 x = in_resolution.xy * r * .015;
        highp vec2 p = 6.28 * uv * x + (n - .5) * 2.;
        highp  vec2 s = sin(p);
        highp vec4 d = texture2D(random_texture, floor(uv * x - 0.25 + 0.5) / x);
        highp float t = (s.x + s.y) * max(0.,1.-fract(100.0 * (d.b+.1)+d.g) * 2.);

        if (d.r < (5.-r) * .08 && t > .5) {
            highp vec3 v = normalize(-vec3(cos(p), mix(.2, 2., t-.5)));
            gl_FragColor = texture2D(in_texture, uv + v.xy * .3);
        }
    }
}
*/
