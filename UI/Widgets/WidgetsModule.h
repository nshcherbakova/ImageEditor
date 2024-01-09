#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_MODULE_H
#define IMAGEEDITOR_UI_WIDGETS_MODULE_H
#include <Modules/types.h>
#include <UI/types.h>

class QWidget;
namespace ImageEditor::UI {
IWidgetInjector InitWidgetsModule(QWidget &parent, Modules::IFramePtr frame,
                                  Modules::IEditableImagePtr image,
                                  Modules::INetworkPtr network);
}
#endif // IMAGEEDITOR_UI_WIDGETS_MODULE_H
