uniform sampler2D in_texture;
uniform highp vec2 in_resolution;
varying mediump vec2 io_texture_coordinates;

#define COLOR_MAX_VAL 16
#define COLOR_MAX_VAL_F 16.0
#define MAX_RAD 6
#define MIN_RAD 2

lowp int max_val(lowp int l, lowp int r)
{
        return l > r ? l : r;
}

lowp vec4 mediana(lowp int radius)
{
        mediump int r[COLOR_MAX_VAL + 1];
        mediump int g[COLOR_MAX_VAL + 1];
        mediump int b[COLOR_MAX_VAL + 1];

        for (int i = 0; i <= COLOR_MAX_VAL; i++)
        {
                r[i] = 0;
                g[i] = 0;
                b[i] = 0;
        }

        lowp int max_position = 0;
        for (lowp int i = - radius; i <= radius; i++)
        {
                for (lowp int j = -radius; j <= radius; j++)
                {
                        mediump vec4 pixel = texture2D(in_texture, io_texture_coordinates + vec2(float(i), float(j))/in_resolution);
                        lowp ivec4 ipixel = ivec4(pixel*COLOR_MAX_VAL_F);

                        r[ipixel.r]++;
                        g[ipixel.g]++;
                        b[ipixel.b]++;

                        max_position = max_val(ipixel.b, max_val(ipixel.g, max_val(max_position, ipixel.r)));
                }
        }
        mediump int r_count = 0;
        mediump int b_count = 0;
        mediump int g_count = 0;

        lowp ivec4 res = ivec4(-1, -1, -1, 1);
        lowp int side = 2*radius + 1;
        lowp int mediana_pos = int(ceil(float(side*side)/2.0 - 1.0));
        for (lowp int k = 0; k <= max_position; k++)
        {
                r_count += r[k];
                if (r_count >= mediana_pos && res.r == -1)
                        res.r = k;

                g_count += g[k];
                if (g_count >= mediana_pos && res.g == -1)
                        res.g = k;

                b_count += b[k];
                if (b_count >= mediana_pos && res.b == -1)
                        res.b  = k;

                if (r_count >= mediana_pos && g_count >= mediana_pos && b_count >= mediana_pos)
                {
                        break;
                }
        }
        return vec4( vec3(res)/COLOR_MAX_VAL_F, 1.0 );
}


void main()
{
        highp int res = int(in_resolution.x > in_resolution.y ? in_resolution.x : in_resolution.y);
        mediump int rad = int(res/300);
        rad = rad > MAX_RAD  ? MAX_RAD : rad;
        rad = rad < MIN_RAD  ? MIN_RAD : rad;
        gl_FragColor = mediana(rad);
}
