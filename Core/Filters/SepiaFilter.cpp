#include <stdafx.h>
#include "SepiaFilter.h"

static const char* c_filter_name_str = "Sepia";

namespace ImageEditor::Core
{
	void SepiaFilter::Transform(FilterBase::BGRAMatrix& arr) const
	{
		for (uint64_t i = 0; i < arr.Height(); i++)
		{
			for (uint64_t j = 0; j < arr.Width(); j++) {
				auto pixel = arr.GetPixel(i, j);
				pixel.update((pixel.r * 0.2392f) + (pixel.g * 0.4696f) + (pixel.b * 0.0912f),
							(pixel.r * 0.2990f) + (pixel.g * 0.5870f) + (pixel.b * 0.1140f),
							(pixel.r * 0.3588f) + (pixel.g * 0.7044f) + (pixel.b * 0.1368f));
			}
		}
	}
	const std::string SepiaFilter::Description() const
	{
		return c_filter_name_str;
	}
}