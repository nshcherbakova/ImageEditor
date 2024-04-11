#version %1

out mediump vec4 FragColor;
in mediump vec2 io_texture_coordinates;

uniform sampler2D in_texture;
uniform highp vec2 in_resolution;


void main() {
/*    highp float Pi = 6.28318530718;
    
    highp float Directions = 16.0;
    highp float Quality = 4.0;
    highp float Size = 8.0;

    highp vec2 Radius = Size/in_resolution.xy;
    highp vec2 uv = io_texture_coordinates;
    highp vec4 Color = texture(in_texture, uv);

    for( highp float d=0.0; d<Pi; d+=Pi/Directions)
    {
        for(highp float i=1.0/Quality; i<=1.0; i+=1.0/Quality)
        {
            Color += texture( in_texture, uv+vec2(cos(d),sin(d))*Radius*i);
        }
    }

    Color /= Quality * Directions;*/
    FragColor =  textureLod( in_texture, io_texture_coordinates, 3.0);
}
