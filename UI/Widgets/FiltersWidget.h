#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H
#define IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H

#include <Modules/types.h>
#include <UI/types.h>
#include <UI/Widgets/IWidget.h>

namespace ImageEditor::UI
{
    class UICommand;
    class MenuDialog;
    class FiltersWidget final: public QWidget, public IWidget
    {
        Q_OBJECT
    public:
        struct Parameters
        {
            QWidget& parent;
            Modules::IFramePtr filters_frame;
            Modules::IEditableImagePtr image;
        };

        explicit FiltersWidget(Parameters parameters);
        FiltersWidget& operator= (const FiltersWidget&) = delete;

    public: // IWidget
        virtual void onShow(const bool visible) override final;

    public slots: 
        void OnSignalOpenImage(QString path);
        void OnSignalSaveImage(QString path);
        void OnMenuButtonClicked();
        void OnCleanButtonClicked();
        void OnSignalCommandAppyed();

    private: // QWidget
        virtual void paintEvent(QPaintEvent* event) override final;

    private:
        void CreateMenuButton(Modules::IControlsMapPtr controls);
        void CreateCleanButton(Modules::IControlsMapPtr controls);
        void CreateFilterButtons(Modules::IControlsMapPtr controls);

    private:
        std::optional<MenuDialog*> menu_;

        Modules::IEditableImagePtr editable_image_;
        std::shared_ptr<QImage> image_;
    };

    class UICommand final : public QObject
    {
        Q_OBJECT
    public:
        explicit UICommand(QObject* parent, Modules::IControlPtr control);
        UICommand& operator= (const UICommand&) = delete;

    public slots:
        void OnButtonClicked();

    signals:
        void SignalCommandAppyed();

    private:
        const Modules::IControlPtr control_;
    };
}
#endif // IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H