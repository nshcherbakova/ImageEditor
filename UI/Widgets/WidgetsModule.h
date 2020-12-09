#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_MODULE_H
#define IMAGEEDITOR_UI_WIDGETS_MODULE_H
#include <Modules/types.h>
#include <UI/types.h>

namespace ImageEditor::UI
{
    IWidgetInjector InitWidgetsModule(QWidget& parent, Modules::IFramePtr frame, Modules::IEditableImagePtr image);
}
#endif //IMAGEEDITOR_UI_WIDGETS_MODULE_H