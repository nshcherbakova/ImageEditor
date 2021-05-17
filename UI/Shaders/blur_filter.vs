attribute highp vec4 posAttr;
attribute mediump vec4 texAttr;
varying mediump vec4 texc;

void main() {
   gl_Position = posAttr;
   texc = texAttr;
} 
