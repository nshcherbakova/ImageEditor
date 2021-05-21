uniform sampler2D in_texture;
uniform vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

float sort(float arr[25])
{
    return arr[12];
}

highp vec4 mediana(highp float index_i, highp float index_j) 
{
	highp float r[25];
	highp float g[25];
	highp float b[25];
	mediump int k = 0;
	for (highp float i = index_i - 2.0; i <= index_i + 2.0; i++)
	{
		for (highp float j = index_j - 2.0; j <= index_j + 2.0; j++)
		{
			vec4 pix = texture2D(in_texture, vec2(i, j)/in_resolution);
			r[k] =  pix.r;
			g[k] =  pix.g;
			b[k] =  pix.b;
			k++;
		}
	}
	highp float rm = sort(r);
	highp float gm = sort(g);
	highp float bm = sort(b);

	return vec4( rm, gm, bm, 1.0 );
}

void main() {
  gl_FragColor = texture2D(in_texture, io_texture_coordinates);
}
