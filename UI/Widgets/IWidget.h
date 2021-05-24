#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_IWIDGET_H 
#define IMAGEEDITOR_UI_WIDGETS_IWIDGET_H

namespace ImageEditor::UI
{
    struct IWidget
    {
        virtual void onShow(const bool visible) = 0;

        virtual ~IWidget() = default;
    };
}
#endif // IMAGEEDITOR_UI_WIDGETS_IWIDGET_H