#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H
#define IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H

#include <Modules/types.h>
#include <UI/types.h>
#include <UI/Widgets/IWidget.h>

namespace ImageEditor::UI
{
    class UICommand;

    class FiltersWidget final: public QWidget, public IWidget
    {
        Q_OBJECT
    public:
        FiltersWidget(QWidget& parent, Modules::IFramePtr frame);

    public slots: // IWidget
        virtual void onShow(const bool visible) override final;
    };

    class UICommand final : public QObject
    {
        Q_OBJECT
    public:
        explicit UICommand(QObject* parent, Modules::IControlPtr control);
    public slots:
        void OnButtonClicked();
    private:
        const Modules::IControlPtr control_;
    };
}
#endif // IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H