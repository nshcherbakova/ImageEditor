#pragma once
#ifndef IMAGEEDITOR_UI_TYPES_H
#define IMAGEEDITOR_UI_TYPES_H
#include <memory>

namespace ImageEditor::UI
{
	struct IWidget;
	using IWidgetPtr = std::shared_ptr<IWidget>;
}
#endif //IMAGEEDITOR_UI_TYPES_H