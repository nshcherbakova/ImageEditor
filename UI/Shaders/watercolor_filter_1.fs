uniform sampler2D in_texture;
uniform highp vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

void Sort(inout highp float a, inout highp float b)
{
    if(a > b)
    {
        highp float t = a;
        a = b;
        b = t;
    }
}

highp float sort1(highp float a[9]) 
{
    Sort(a[1], a[2]); Sort(a[4], a[5]); Sort(a[7], a[8]); 
    Sort(a[0], a[1]); Sort(a[3], a[4]); Sort(a[6], a[7]);
    Sort(a[1], a[2]); Sort(a[4], a[5]); Sort(a[7], a[8]); 
    Sort(a[0], a[3]); Sort(a[5], a[8]); Sort(a[4], a[7]);
    Sort(a[3], a[6]); Sort(a[1], a[4]); Sort(a[2], a[5]); 
    Sort(a[4], a[7]); Sort(a[4], a[2]); Sort(a[6], a[4]);
    Sort(a[4], a[2]);

    return a[4];
}

lowp vec4 mediana1(lowp vec2 coordinates)
{
         float r[9];
             float g[9];
             float b[9];

        lowp int k = 0;
        for (lowp int i = - 1; i <= 1; i++)
        {
                for (lowp int j = -1; j <= 1; j++)
                {
                        mediump vec4 pixel = texture2D(in_texture, coordinates + vec2(float(i), float(j))/in_resolution);
                       
                        r[k] =  pixel.r;
			            g[k] =  pixel.g;
			            b[k] =  pixel.b;
			            k++;
                }
        }
        
        highp float rm = sort1(r);
	    highp float gm = sort1(g);
	    highp float bm = sort1(b);
        return vec4( vec3(rm, gm, bm), 1.0 );
}


lowp vec4 mediana2(lowp vec4 multidim[9])
{
        highp float r[9];
	    highp float g[9];
	    highp float b[9];

        for (lowp int k = 0; k < 9; k++)
        {
               
                        mediump vec4 pixel = multidim[k];
                       
                        r[k] =  pixel.r;
			            g[k] =  pixel.g;
			            b[k] =  pixel.b;
                
        }
        
        highp float rm = sort1(r);
	    highp float gm = sort1(g);
	    highp float bm = sort1(b);
        return vec4( vec3(rm, gm, bm), 1.0 );
}

lowp vec4 mediana()
{
      lowp vec4 multidim[9];
      int k = 0;
      for (lowp int i = - 1; i <= 1; i++)
      {
            for (lowp int j = -1; j <= 1; j++)
            {
                multidim[k++] = mediana1(io_texture_coordinates + vec2(float(i*2), float(j*2))/in_resolution );
            }
      }

      return mediana2(multidim);
}

void main()
{
        gl_FragColor = mediana();
}
