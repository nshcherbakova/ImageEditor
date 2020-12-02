#ifndef IMAGEEDITOR_MODULES_FRAMES_ICONTROL_H
#define IMAGEEDITOR_MODULES_FRAMES_ICONTROL_H

#include <string>
#include <Modules/types.h>

namespace ImageEditor::Modules
{
	struct IControl
	{
		//virtual const std::string Tag() const = 0;
		virtual const std::string Parameters() const = 0;
		virtual void Activate(std::string paramerts) = 0;

		virtual ~IControl() {}
	};
}

#endif // IMAGEEDITOR_MODULES_FRAMES_ICONTROL_H
#pragma once
