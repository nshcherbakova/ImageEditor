#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "WatercolorFilter.h"

static const char* c_filter_name_str = "Aqua";
static const int H[3][3] = { {0, -1, 0},
							 {-1 ,5,-1},
							 {0, -1, 0} };

namespace ImageEditor::Core
{
	WatercolorFilter::WatercolorFilter()
	{
	}

	void WatercolorFilter::Transform(FilterBase::BGRAMatrix& arr) const
	{
		UNI_ENSURE_RETURN(arr.Height() > 4 && arr.Width() > 4);
		FilterBase::BGRAMatrix arr_copy = arr;

		struct bgr_holder
		{
			int b = 0;
			int g = 0;
			int r = 0;
		};

		const unsigned int c_arr_size = std::numeric_limits<unsigned char>::max() + 1;
		std::vector<uchar> r(c_arr_size, 0);
		std::vector<uchar> g(c_arr_size, 0);
		std::vector<uchar> b(c_arr_size, 0);

		auto mediana = [&](FilterBase::BGRAMatrix& arr, uint64_t index_i, uint64_t index_j) {
			for (uint64_t i = 0; i < c_arr_size; i++)
			{
				r[i] = 0;
				g[i] = 0;
				b[i] = 0;
			}

			for (uint64_t i = index_i - 2; i <= index_i + 2; i++)
			{
				for (uint64_t j = index_j - 2; j <= index_j + 2; j++)
				{
					auto pixel = arr.GetPixel(i, j);
					r[pixel.r]++;
					g[pixel.g]++;
					b[pixel.b]++;
				}
			}
			int r_count = 0;
			int b_count = 0;
			int g_count = 0;

			int r_i = -1;
			int g_i = -1;
			int b_i = -1;
			for (int k = 0; k <= std::numeric_limits<unsigned char>::max(); k++)
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
			return bgr_holder{ b_i, g_i, r_i};
		};

		for (uint64_t i = 2; i < arr_copy.Height() - 2; i++)
		{
			for (uint64_t j = 2; j < arr_copy.Width() - 2; j++) {
				auto pix = mediana(arr_copy, i, j);
				arr.GetPixel(i, j).update(pix.b, pix.g, pix.r);
			}
		}
		
		arr_copy = arr;
		for (uint64_t i = 1; i < arr.Height() - 1; i++)
		{
			for (uint64_t j = 1; j < arr.Width() - 1; j++)
			{
				double r = 0, g = 0, b = 0;

				for (int k = -1; k < 2; k++)
				{
					for (int m = -1; m < 2; m++)
					{
						auto pixel = arr_copy.GetPixel(i + k, j + m);

						r += pixel.r * H[1 + k][1 + m];
						g += pixel.g * H[1 + k][1 + m];
						b += pixel.b * H[1 + k][1 + m];
					}
				}
				arr.GetPixel(i, j).update(b, g, r);

			}
		}
	}
	const std::string WatercolorFilter::Description() const
	{
		return c_filter_name_str;
	}
}