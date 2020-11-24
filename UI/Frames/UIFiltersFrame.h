#pragma once
#ifndef IMAGEEDITOR_UI_FRAMES_UIFILTERSFRAME_H
#define IMAGEEDITOR_UI_FRAMES_UIFILTERSFRAME_H

#include <UI/Frames/IUIFrame.h>
#include <Modules/IFrame.h>
//#include "ui_UIFiltersFrame.h"

namespace ImageEditor::UI::Frames
{
    class UICommand final : public QObject
    {
        Q_OBJECT
    public:
        UICommand(QObject* parent, const Modules::IControlPtr& control);
    public slots:
        void OnButtonClicked();
    private:
        const Modules::IControlPtr control_;
    };

    class UIFiltersFrame final: public QGridLayout, public IUIFrame
    {
        Q_OBJECT
    public:
        explicit UIFiltersFrame(QWidget* parent, const Modules::IFramePtr& frame);
    public slots:
        virtual void onShow(const bool visible) override final;
    private:
        std::vector<QPushButton*> filter_buttons_;
        QPushButton* menu_button_;
    };
}
#endif // IMAGEEDITOR_UI_FRAMES_UIFILTERSFRAME_H