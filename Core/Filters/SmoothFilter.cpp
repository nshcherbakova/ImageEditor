#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "SmoothFilter.h"

static const char* c_filter_name_str = "Smooth";

namespace ImageEditor::Core
{
	SmoothFilter::SmoothFilter()
	{}

	void SmoothFilter::Transform(FilterBase::bgraMatrix& image) const
	{
		UNI_ENSURE_RETURN(image.size() > 1 && image[0].size() > 1);
		
		double H[3][3];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				H[i][j] = (double)1.0 / 10.0;
		H[1][1] = 1.0 / 5.0;
		
		FilterBase::bgraMatrix image_src = image;
		for (uint64_t i = 1; i < image.size()-1; i++)
		{
			for (uint64_t j = 1; j < image[i].size()-1; j++) {

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

	const std::string SmoothFilter::Description() const
	{
		return c_filter_name_str;
	}
}