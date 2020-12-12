#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "SepiaFilter.h"

namespace ImageEditor::Core
{
	SepiaFilter::SepiaFilter() {}

	void SepiaFilter::Transform(FilterBase::bgraMatrix& arr) const
	{
		for (uint64_t i = 0; i < arr.size(); i++)
		{
			for (uint64_t j = 0; j < arr[i].size(); j++) {

				/* uchar tone = (uchar)(0.299 * arr[i][j].r + 0.587 * arr[i][j].g + 0.114 * arr[i][j].b);
				arr[i][j] = bgra(
					((tone < 56) ? 0 : tone - 56),
					((tone < 14) ? 0 : tone - 14),
					((tone > 206) ? 255 : tone + 30),
					arr[i][j].a

						(arr[i][j].r * .272) + (arr[i][j].g * .534) + (arr[i][j].b * .131),
					(arr[i][j].r * .349) + (arr[i][j].g * .686) + (arr[i][j].b * .168),
					(arr[i][j].r * .393) + (arr[i][j].g * .769) + (arr[i][j].b * .189),
					);*/

				
				arr[i][j] = bgra(
					(arr[i][j].r * 0.2392f) + (arr[i][j].g * 0.4696f) + (arr[i][j].b * 0.0912f),
					(arr[i][j].r * 0.2990f) + (arr[i][j].g * 0.5870f) + (arr[i][j].b * 0.1140f),
					(arr[i][j].r * 0.3588f) + (arr[i][j].g * 0.7044f) + (arr[i][j].b * 0.1368f),
					arr[i][j].a
				); 
			}
		}
	}

	const std::string SepiaFilter::Description() const
	{
		return "sepia";
	}
}