#include <stdafx.h>
#include "FiltersFrame.h"


namespace ImageEditor::Modules::FiltersFrame
{
	FiltersFrame::FiltersFrame(const Core::Image::IImagePtr& /*image*/)
	{}

	const IControlsMapPtr FiltersFrame::Controls() const
	{
		return nullptr;
	}

}