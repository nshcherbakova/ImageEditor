uniform sampler2D texture;
varying mediump vec4 texc;

void main() {
  gl_FragColor = texture2D(texture, texc.st);
  highp float average = 0.2126 * gl_FragColor.r + 0.7152 * gl_FragColor.g + 0.0722 * gl_FragColor.b;
  gl_FragColor = vec4(average, average, average, 1.0);
}
