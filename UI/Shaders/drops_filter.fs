uniform sampler2D in_texture;
uniform highp vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

#define S(a, b, t) smoothstep(a, b, t)

mediump vec3 N13(mediump float p) {
    //  from DAVE HOSKINS
   mediump vec3 p3 = fract(vec3(p) * vec3(.1031,.11369,.13787));
   p3 += dot(p3, p3.yzx + 19.19);
   return fract(vec3((p3.x + p3.y)*p3.z, (p3.x+p3.z)*p3.y, (p3.y+p3.z)*p3.x));
}

mediump vec4 N14(mediump float t) {
	return fract(sin(t*vec4(123., 1024., 1456., 264.))*vec4(6547., 345., 8799., 1564.));
}

mediump float N(mediump float t) {
    return fract(sin(t*12345.564)*7658.76);
}

mediump float Saw(mediump float b, mediump  float t) {
	return S(0., b, t)*S(1., b, t);
}

mediump vec2 DropLayer2(mediump vec2 uv, mediump float t) {
    mediump vec2 UV = uv;
    
    uv.y += t*0.75;
    mediump vec2 a = vec2(6., 1.);
    mediump vec2 grid = a*2.;
    mediump vec2 id = floor(uv*grid);
    
    mediump float colShift = N(id.x); 
    uv.y += colShift;
    
    id = floor(uv*grid);
    mediump vec3 n = N13(id.x*35.2+id.y*2376.1);
    mediump vec2 st = fract(uv*grid)-vec2(.5, 0);
    
    mediump float x = n.x-.5;
    
    mediump float y = UV.y*20.;
    mediump float wiggle = sin(y+sin(y));
    x += wiggle*(.5-abs(x))*(n.z-.5);
    x *= .7;
    mediump float ti = fract(t+n.z);
    y = (Saw(.85, ti)-.5)*.9+.5;
    mediump vec2 p = vec2(x, y);
    
    mediump float d = length((st-p)*a.yx);
    
    mediump float mainDrop = S(.4, .0, d);
    
    mediump float r = sqrt(S(1., y, st.y));
    mediump float cd = abs(st.x-x);
    mediump float trail = S(.23*r, .15*r*r, cd);
    mediump float trailFront = S(-.02, .02, st.y-y);
    trail *= trailFront*r*r;
    
    y = UV.y;
    mediump float trail2 = S(.2*r, .0, cd);
    mediump float droplets = max(0., (sin(y*(1.-y)*120.)-st.y))*trail2*trailFront*n.z;
    y = fract(y*10.)+(st.y-.5);
    mediump float dd = length(st-vec2(x, y));
    droplets = S(.3, 0., dd);
    mediump float m = mainDrop+droplets*r*trailFront;
    
    //m += st.x>a.y*.45 || st.y>a.x*.165 ? 1.2 : 0.;
    return vec2(m, trail);
}

mediump float StaticDrops(mediump vec2 uv, mediump float t) {
	uv *= 40.;
    
    mediump vec2 id = floor(uv);
    uv = fract(uv)-.5;
    mediump vec3 n = N13(id.x*107.45+id.y*3543.654);
    mediump vec2 p = (n.xy-.5)*.7;
    mediump float d = length(uv-p);
    
    mediump  float fade = Saw(.025, fract(t+n.z));
    mediump float c = S(.3, 0., d)*fract(n.z*10.)*fade;
    return c;
}

mediump vec2 Drops(mediump vec2 uv, mediump float t, mediump float l0, mediump float l1, mediump float l2) {
    mediump float s = StaticDrops(uv, t)*l0; 
    mediump vec2 m1 = DropLayer2(uv, t)*l1;
    mediump vec2 m2 = DropLayer2(uv*1.85, t)*l2;
    
    mediump float c = s+m1.x+m2.x;
    c = S(.3, 1., c);
    
    return vec2(c, max(m1.y*l0, m2.y*l1));
}

void main(  )
{   
    mediump vec2 fragCoord = io_texture_coordinates;
    mediump vec3 iMouse = vec3(0.0, 0.0, 0.0);
    mediump float iTime = 500.0;
    mediump vec2 uv = fragCoord;
    mediump vec2 UV = fragCoord;
    mediump vec3 M = iMouse.xyz;
    mediump float T = iTime+M.x*2.;
    
    mediump float t = T*.2;
    
    mediump float rainAmount = iMouse.z>0. ? M.y : sin(T*.05)*.3+.7;
    
    mediump float maxBlur = 1.0;
    mediump float minBlur = 2.0;
    
    mediump float story = 0.;
    mediump float heart = 0.;
    
   
    //float zoom = -cos(T*.2);
    mediump float zoom = 1.0;
    uv *= .7+zoom*.3;
   
    UV = (UV-.5)*(.9+zoom*.1)+.5;
    
    mediump float staticDrops = S(-.5, 1., rainAmount)*2.;
    mediump float layer1 = S(.25, .75, rainAmount);
    mediump float layer2 = S(.0, .5, rainAmount);
    
    
    mediump vec2 c = Drops(uv, t, staticDrops, layer1, layer2);
   
    mediump vec2 e = vec2(.001, 0.);
    mediump float cx = Drops(uv+e, t, staticDrops, layer1, layer2).x;
    mediump float cy = Drops(uv+e.yx, t, staticDrops, layer1, layer2).x;
    mediump vec2 n = vec2(cx-c.x, cy-c.x);		// expensive normals
    
    mediump float focus = mix(maxBlur-c.y, minBlur, S(.1, .2, c.x));
    mediump vec3 col = texture2D(in_texture, UV+n, focus).rgb;
    
    //col = vec3(heart);
    gl_FragColor = vec4(col, 1.);
}
 
