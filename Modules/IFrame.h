#pragma once
#ifndef IMAGEEDITOR_FRAMES_IFRAME_H
#define IMAGEEDITOR_FRAMES_IFRAME_H

#include <memory>
#include <Modules/IControl.h>

namespace ImageEditor::Modules
{
	struct IFrame;
	using IFramePtr = std::shared_ptr<IFrame>;

	struct IFrame
	{
	public:
		virtual ~IFrame() {}
	public:
		virtual const IControlsMapPtr Controls() const = 0;
	private:
	};
}

#endif // IMAGEEDITOR_FRAMES_IFRAME_H
