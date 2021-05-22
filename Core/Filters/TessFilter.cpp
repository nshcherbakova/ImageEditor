#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "TessFilter.h"

static const char* c_filter_name_str = "Imp";
static const int H[3][3] = {{0,-1,0},
							{1,0,-1},
							{0,1,0}};

namespace ImageEditor::Core
{
	float diff(float val)
	{
		return float(val + 0.5) - floor(val + 0.5);
	}

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
				fbgra color;

				for (int k = -1; k < 2; k++)
				{
					for (int m = -1; m < 2; m++)
					{
						const int h = H[1 + k][1 + m];
						if (h != 0)
						{
							const auto pixel = arr_src.GetPixel(i + k, j + m);

							color += pixel / float(std::numeric_limits<unsigned char>::max()) * h;
						}
					}
				}
				
				color.b = diff(color.b);
				color.g = diff(color.g);
				color.r = diff(color.r);

				arr.GetPixel(i, j).updateBGR(color * std::numeric_limits<unsigned char>::max());
			}
		}
	}
	const std::string TessFilter::Description() const
	{
		return c_filter_name_str;
	}
}