#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "SmoothFilter.h"

static const char* c_filter_name_str = "Smooth";
static const double H[3][3] = { { 0.1, 0.1, 0.1}, 
								{ 0.1, 0.2, 0.1}, 
								{ 0.1, 0.1, 0.1} };

namespace ImageEditor::Core
{
	SmoothFilter::SmoothFilter()
	{
	}

	void SmoothFilter::Transform(FilterBase::BGRAMatrix& arr) const
	{
		for (uint64_t i = 1; i < arr.Height() - 1; i++)
		{
			for (uint64_t j = 1; j < arr.Width() - 1; j++) 
			{
				double r = 0, g = 0, b = 0;

				for (int k = -1; k < 2; k++)
				{
					for (int m = -1; m < 2; m++)
					{
						auto pixel = arr.GetPixel(i + k, j + m);

						r += (int)pixel.r * H[1 + k][1 + m];
						g += (int)pixel.g * H[1 + k][1 + m];
						b += (int)pixel.b * H[1 + k][1 + m];
					}
				}
				arr.GetPixel(i, j).update(b, g, r);
			}
		}
	}
	const std::string SmoothFilter::Description() const
	{
		return c_filter_name_str;
	}
}