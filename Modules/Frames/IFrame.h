#pragma once
#ifndef IMAGEEDITOR_MODULES_FRAMES_IFRAME_H
#define IMAGEEDITOR_MODULES_FRAMES_IFRAME_H

#include <Modules/types.h>

namespace ImageEditor::Modules
{
	struct IFrame
	{
		virtual const IControlsMapPtr Controls() const = 0;

		virtual ~IFrame() = default;
	};
}

#endif // IMAGEEDITOR_MODULES_FRAMES_IFRAME_H
