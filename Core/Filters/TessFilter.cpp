#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "TessFilter.h"

static const char* c_filter_name_str = "Imp";

namespace ImageEditor::Core
{
	TessFilter::TessFilter()
	{
	}

	void TessFilter::Transform(FilterBase::bgraMatrix& image) const 
	{
		UNI_ENSURE_RETURN(image.size() > 1 && image[0].size() > 1);

		int H[3][3] = { {0,1,0},
				{-1,0,1},
				{0,-1,0} };

		FilterBase::bgraMatrix image_src = image;
		for (uint64_t i = 1; i < image.size()-1; i++)
		{
			for (uint64_t j = 1; j < image[i].size()-1; j++) {

				int r = 0, g = 0, b = 0;

				for (int k = -1; k < 2; k++)
				{
					for (int m = -1; m < 2; m++)
					{
						if (H[1 + k][1 + m] != 0)
						{
							r += (int)image_src[i + k][j + m].r * H[1 + k][1 + m];
							g += (int)image_src[i + k][j + m].g * H[1 + k][1 + m];
							b += (int)image_src[i + k][j + m].b * H[1 + k][1 + m];
						}
					}
				}

				b = int(b + 128) % 255;
				g = int(g + 128) % 255;
				r = int(r + 128) % 255;

				image[i][j] = bgra(
					b,
					g,
					r,
					image[i][j].a
					);
			}
		}
	}

	const std::string TessFilter::Description() const
	{
		return c_filter_name_str;
	}
}