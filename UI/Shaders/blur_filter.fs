uniform sampler2D texture;
varying mediump vec4 texc;

void main() {
    highp float Pi = 6.28318530718;
    
    highp float Directions = 16.0;
    highp float Quality = 4.0;
    highp float Size = 10.0;

    highp vec2 Radius = vec2(Size)/600.0;
    highp vec2 uv = texc.st;
    highp vec4 Color = texture2D(texture, uv);

    for( highp float d=0.0; d<Pi; d+=Pi/Directions)
    {
        for(highp float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
            Color += texture2D( texture, uv+vec2(cos(d),sin(d))*Radius*i);
        }
    }

    Color /= Quality * Directions;
    gl_FragColor =  Color;
}
