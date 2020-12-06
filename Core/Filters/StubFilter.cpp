#include <stdafx.h>
#include "StubFilter.h"

namespace ImageEditor::Core
{
	StubFilter::StubFilter()
	{}

	IImagePtr StubFilter::Apply(const IImagePtr image, const std::string& /*parameters*/) const
	{
		return image;
	}

	const std::string StubFilter::Description() const
	{
		return "stub";
	}
}