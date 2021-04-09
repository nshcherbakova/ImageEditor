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

	struct IImageProvider;
	using IImageProviderPtr = std::shared_ptr<IImageProvider>;
	using ImageProviderInjector = boost::di::injector<IImageProviderPtr>;
}
#endif //IMAGEEDITOR_UI_TYPES_H