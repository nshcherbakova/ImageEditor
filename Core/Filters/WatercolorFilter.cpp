#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "WatercolorFilter.h"

static const char* c_filter_name_str = "Aqua";

namespace ImageEditor::Core
{
	WatercolorFilter::WatercolorFilter()
	{
	}

	void WatercolorFilter::Transform(FilterBase::bgraMatrix& image) const
	{
		UNI_ENSURE_RETURN(image.size() > 4 && image[0].size() > 4);
		FilterBase::bgraMatrix image_src = image;

		auto mediana = [](FilterBase::bgraMatrix& image, uint64_t index_i, uint64_t index_j) {
			FilterBase::bgra pix;
			std::vector<uchar> r(256, 0);
			std::vector<uchar> g(256, 0);
			std::vector<uchar> b(256, 0);
			for (uint64_t i = index_i - 2; i <= index_i + 2; i++)
			{
				for (uint64_t j = index_j - 2; j <= index_j + 2; j++)
				{
					r[image[i][j].r]++;
					g[image[i][j].g]++;
					b[image[i][j].b]++;
				}
			}
			int r_count = 0;
			int b_count = 0;
			int g_count = 0;
			
			int r_i = -1;
			int g_i = -1;
			int b_i = -1;
			for (int k = 0; k <= 255; k++)
			{
				r_count += r[k];
				if (r_count >= 12 && r_i == -1)
					r_i = k;
				g_count += g[k];
				if (g_count >= 12 && g_i == -1)
					g_i = k;
				b_count += b[k];
				if (b_count >= 12 && b_i == -1)
					b_i = k;
				if (r_count >= 12 && g_count >= 12 && b_count >= 12)
				{
					break;
				}
			}
			return FilterBase::bgra{ b_i, g_i, r_i, image[index_i][index_j].a };
		};

		auto mediana2 = [](FilterBase::bgraMatrix& image, uint64_t index_i, uint64_t index_j) {
			FilterBase::bgra pix;
			std::vector<uchar> r(25);
			std::vector<uchar> g(25);
			std::vector<uchar> b(25);
			int k = 0;
			for (uint64_t i = index_i - 2; i <= index_i + 2; i++)
			{
				for (uint64_t j = index_j - 2; j <= index_j + 2; j++)
				{
					r[k] = (image[i][j].r);
					g[k] = (image[i][j].g);
					b[k] = (image[i][j].b);
					k++;
				}
			}
			std::sort(r.begin(), r.end());
			std::sort(g.begin(), g.end());
			std::sort(b.begin(), b.end());

			return FilterBase::bgra{ b[12], g[12], r[12], image[index_i][index_j].a };
		};

		for (uint64_t i = 2; i < image.size() - 2; i++)
			for (uint64_t j = 2; j < image[i].size() - 2; j++) {
				image[i][j] = mediana(image_src, i, j);
			}

		int H[3][3]={{0,-1,0},
				{-1,5,-1},
				{0,-1,0}};
		
		image_src = image;
		for (uint64_t i = 1; i < image.size()-1; i++)
		{
			for (uint64_t j = 1; j < image[i].size()-1; j++) 
			{
				double r = 0, g = 0, b = 0;

				for (int k = -1; k < 2; k++)
				{
					for (int m = -1; m < 2; m++)
					{
						r += (int)image_src[i + k][j + m].r * H[1 + k][1 + m];
						g += (int)image_src[i + k][j + m].g * H[1 + k][1 + m];
						b += (int)image_src[i + k][j + m].b * H[1 + k][1 + m];
					}
				}

				image[i][j] = bgra(
					b,
					g,
					r,
					image[i][j].a
				);

			}
		}
	}

	const std::string WatercolorFilter::Description() const
	{
		return c_filter_name_str;
	}
}