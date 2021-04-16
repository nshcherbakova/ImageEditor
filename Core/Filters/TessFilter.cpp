#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "TessFilter.h"

static const char* c_filter_name_str = "Imp";
static const int H[3][3] = {{0,1,0},
							{-1,0,1},
							{0,-1,0}};

namespace ImageEditor::Core
{
	TessFilter::TessFilter()
	{
	}

	void TessFilter::Transform(FilterBase::BGRAMatrix& arr) const
	{
		FilterBase::BGRAMatrix arr_src = arr;

		for (uint64_t i = 1; i < arr_src.Height() - 1; i++)
		{
			for (uint64_t j = 1; j < arr_src.Width() - 1; j++) {
				int r = 0, g = 0, b = 0;

				for (int k = -1; k < 2; k++)
				{
					for (int m = -1; m < 2; m++)
					{
						if (H[1 + k][1 + m] != 0)
						{
							auto pixel = arr_src.GetPixel(i + k, j + m);

							r += (int)pixel.r * H[1 + k][1 + m];
							g += (int)pixel.g * H[1 + k][1 + m];
							b += (int)pixel.b * H[1 + k][1 + m];
						}
					}
				}

				b = int(b + 128) % std::numeric_limits<unsigned char>::max();
				g = int(g + 128) % std::numeric_limits<unsigned char>::max();
				r = int(r + 128) % std::numeric_limits<unsigned char>::max();

				arr.GetPixel(i, j).update(b, g, r);
			}
		}
	}
	const std::string TessFilter::Description() const
	{
		return c_filter_name_str;
	}
}