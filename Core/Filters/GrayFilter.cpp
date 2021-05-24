#include <stdafx.h>
#include "GrayFilter.h"

static const char* c_filter_name_str = "Gray";

namespace ImageEditor::Core
{
	void GrayFilter::Transform(FilterBase::BGRAMatrix& arr) const
	{
		for (uint64_t i = 0; i < arr.Height(); i++)
		{
			for (uint64_t j = 0; j < arr.Width(); j++) {
				auto pixel = arr.GetPixel(i, j);
				const int summ = int(0.2989 * (pixel.r) + 0.5870 * (pixel.g) + 0.1140 * (pixel.b));
				pixel.update(summ, summ, summ);
			}
		}
	}

	const std::string GrayFilter::Description() const
	{
		return c_filter_name_str;
	}
}