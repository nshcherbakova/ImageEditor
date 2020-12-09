#pragma once
#ifndef IMAGEEDITOR_UI_TYPES_H
#define IMAGEEDITOR_UI_TYPES_H
#include <memory>
#include <Core/Gears/Injector.h>

namespace ImageEditor::UI
{
	struct IWidget;
	using IWidgetPtr = std::shared_ptr<IWidget>;

	using IWidgetInjector = boost::di::injector<IWidget*>;
}
#endif //IMAGEEDITOR_UI_TYPES_H