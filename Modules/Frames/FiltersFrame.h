#pragma once
#ifndef IMAGEEDITOR_MODULES_FRAMES_FILTERFRAME_H
#define IMAGEEDITOR_MODULES_FRAMES_FILTERFRAME_H

#include <Core/types.h>
#include <Modules/types.h>
#include <Modules/Frames/IFrame.h>

namespace ImageEditor::Modules
{
	class FiltersFrame final: public IFrame
	{
	public:
		struct Parameters
		{
			IEditableImagePtr image;
			Core::IFilterPtrArr filters;
		};

		explicit FiltersFrame(Parameters parameters);
		FiltersFrame& operator= (const FiltersFrame&) = delete;

	public: // IFrame
		virtual const IControlsMapPtr Controls() const override final;
	
	private:
		IControlsMapPtr controls_;
	};
}

#endif // IMAGEEDITOR_MODULES_FRAMES_FILTERFRAME_H
