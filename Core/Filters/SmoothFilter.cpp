#include <stdafx.h>
#include "SmoothFilter.h"

static const char* c_filter_name_str = "Smooth";
static const float H[3][3] = { { 0.1, 0.1, 0.1}, 
								{ 0.1, 0.2, 0.1}, 
								{ 0.1, 0.1, 0.1} };

namespace ImageEditor::Core
{
	void SmoothFilter::Transform(FilterBase::BGRAMatrix& arr) const
	{
		for (uint64_t i = 1; i < arr.Height() - 1; i++)
		{
			for (uint64_t j = 1; j < arr.Width() - 1; j++) 
			{
				ucbgra color;

				for (int k = -1; k < 2; k++)
				{
					for (int m = -1; m < 2; m++)
					{
						const auto pixel = arr.GetPixel(i + k, j + m);

						const float h = H[1 + k][1 + m];
						color += ucbgra(pixel * h);
					}
				}
				arr.GetPixel(i, j).updateBGR(color);
			}
		}
	}
	const std::string SmoothFilter::Description() const
	{
		return c_filter_name_str;
	}
}