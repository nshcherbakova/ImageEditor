uniform sampler2D in_texture;
uniform highp vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

#define COLOR_MAX_VAL 32

#define COLOR_MAX_VAL_F 32.0

lowp int max(lowp int l, lowp int r) 
{
	return l > r ? l : r;
}

highp float mediana(lowp int radius, lowp int color_index) 
{
    lowp int color_range[COLOR_MAX_VAL + 1];
	for (lowp int i = 0; i < COLOR_MAX_VAL; i++)
	{
		color_range[i] = 0;
	}

	lowp int max_position = 0;
	for (lowp int i = - radius; i <= radius; i++)
	{
		for (lowp int j = -radius; j <= radius; j++)
		{
			mediump vec4 pixel = texture2D(in_texture, io_texture_coordinates + vec2(float(i), float(j))/in_resolution);
            lowp int ipixel_color_val = ivec4(pixel*COLOR_MAX_VAL_F)[color_index];
			
            color_range[ipixel_color_val]++;

            max_position =  max(max_position, ipixel_color_val);
		}
	}
	
	mediump int colors_count = 0;

	lowp int res = 0;
	for (lowp int k = 0; k <= max_position; k++)
	{
        colors_count += color_range[k];
		if (colors_count >= 12 && res == 0)
			res = k;
		
	}
    return float(res)/COLOR_MAX_VAL_F;
}


void main() 
{
    highp int res = int(in_resolution.x > in_resolution.y ? in_resolution.x : in_resolution.y);
    mediump int rad = int(res/300);
	rad = rad > 8  ? 8 : rad;
	rad = rad < 2  ? 2 : rad;

    gl_FragColor = vec4(mediana(rad, 0), mediana(rad, 1), mediana(rad, 2), 1.0);
}
