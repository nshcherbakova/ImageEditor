#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "TessFilter.h"

static const char* c_filter_name_str = "Imp";
static const int H[3][3] = {{0,-1,0},
							{1,0,-1},
							{0,1,0}};

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
			for (uint64_t j = 1; j < arr_src.Width() - 1; j++) 
			{
				float r = 0, g = 0, b = 0;

				for (int k = -1; k < 2; k++)
				{
					for (int m = -1; m < 2; m++)
					{
						const int h = H[1 + k][1 + m];
					//	if (h != 0)
						{
							const auto pixel = arr_src.GetPixel(i + k, j + m);

							r += pixel.r / 255.0 * h;
							g += pixel.g / 255.0 * h;
							b += pixel.b / 255.0 * h;
						}
					}
				}
				
				float max_char = 1.0;

				b = float(b + 0.5) - floor(b + 0.5);
				g = float(g + 0.5) - floor(g + 0.5);
				r = float(r + 0.5) - floor(r + 0.5);

				arr.GetPixel(i, j).update(b*255, g*255, r*255);
			}
		}
	}
	const std::string TessFilter::Description() const
	{
		return c_filter_name_str;
	}
}