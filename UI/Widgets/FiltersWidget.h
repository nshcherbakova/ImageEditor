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
    class Button;

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
        QImage background_image_;
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

    class Button final : public QPushButton
    {
        Q_OBJECT
    public:
        Button(const QString& text, QWidget* parent = nullptr);

    protected:
        virtual void keyPressEvent(QKeyEvent*) override final;
        virtual void focusInEvent(QFocusEvent*) override final;
        virtual void focusOutEvent(QFocusEvent*) override final;
        virtual void mouseMoveEvent(QMouseEvent* e) override final;
        virtual void mousePressEvent(QMouseEvent* e) override final;
        virtual void mouseReleaseEvent(QMouseEvent* e) override final;
        virtual void enterEvent(QEvent* e) override final;
        virtual void leaveEvent(QEvent* e) override final;
    };
}
#endif // IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H