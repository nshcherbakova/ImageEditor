#pragma once
#ifndef IMAGEEDITOR_FRAMES_FILTERFRAME_FILTERFRAME_H
#define IMAGEEDITOR_FRAMES_FILTERFRAME_FILTERFRAME_H

#include <Core/Image/IImage.h>
#include <Modules/IFrame.h>

namespace ImageEditor::Modules::FiltersFrame
{
	class FiltersFrame final: public IFrame
	{
	public:
		explicit FiltersFrame(const Core::Image::IImagePtr& image);
	public:
		virtual const IControlsMapPtr Controls() const override final;
	
	};
}

#endif // IMAGEEDITOR_FRAMES_FILTERFRAME_FILTERFRAME_H
