#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "GrayFilter.h"

namespace ImageEditor::Core
{
	GrayFilter::GrayFilter() {}

	void GrayFilter::Transform(FilterBase::bgraMatrix& arr) const
	{
		for (uint64_t i = 0; i < arr.size(); i++)
		{
			for (uint64_t j = 0; j < arr[i].size(); j++) {
				int summ = int(0.2989 * (arr[i][j].r) + 0.5870 * (arr[i][j].g) + 0.1140 * (arr[i][j].b));
				arr[i][j] = bgra(
					summ,
					summ,
					summ,
					arr[i][j].a
					);
			}
		}
	}

	const std::string GrayFilter::Description() const
	{
		return "gray";
	}
}