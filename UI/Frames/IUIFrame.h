#pragma once
#ifndef IMAGEEDITOR_UI_FRAMES_IFRAME_H 
#define IMAGEEDITOR_UI_FRAMES_IFRAME_H
#include <QtCore/QObject>

namespace ImageEditor::UI::Frames
{
    struct IUIFrame 
    {
        //Q_OBJECT
    public:
        virtual ~IUIFrame() {}
    //public slots:
        virtual void onShow(const bool visible) = 0;
    private:
    };
}
#endif // IMAGEEDITOR_UI_FRAMES_IFRAME_H