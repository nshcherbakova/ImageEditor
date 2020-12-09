#pragma once
#ifndef IMAGEEDITOR_MODULES_TYPES_H
#define IMAGEEDITOR_MODULES_TYPES_H
#include <memory>
#include <map>
#include <Core/Gears/Injector.h>

namespace ImageEditor::Modules
{
	struct IEditableImage;
	using IEditableImagePtr = std::shared_ptr<IEditableImage>;

	struct IControl;
	using IControlPtr = std::shared_ptr<IControl>;
	using IControlsMap = std::multimap<std::string, IControlPtr>;
	using IControlsMapPtr = std::shared_ptr<IControlsMap>;

	struct IFrame;
	using IFramePtr = std::shared_ptr<IFrame>;

	using IEditableImageInjector = boost::di::injector<IEditableImagePtr>;
	using IFrameInjector = boost::di::injector<IFramePtr>;
}
#endif //IMAGEEDITOR_MODULES_TYPES_H