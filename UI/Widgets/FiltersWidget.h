#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H
#define IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H

#include <QWidget>
#include <QPushButton>
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

    signals:
        void SignalEnableFilterButtons(const bool enable);
        void SignalEnableCleanButton(const bool enable);

    public slots:
        void OnSignalOpenImage(const QString path);
        void OnSignalSaveImage(const QString path);
        void OnMenuButtonClicked();
        void OnCleanButtonClicked();
        void OnSignalCommandAppyed();

    private: // QWidget
        virtual void paintEvent(QPaintEvent* event) override final;

    private:
        void CreateMenuButton();
        void CreateCleanButton();
        void CreateFilterButtons(Modules::IControlsMapPtr controls);

        void UpdateImage();

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

    class ImageButton : public QPushButton
    {
        Q_OBJECT
    public:
        ImageButton(const QString& text, QWidget* parent = nullptr);

    public slots:
        void OnSignalEnable(const bool enable);

    protected:
        virtual void keyPressEvent(QKeyEvent*) override final;
        virtual void focusInEvent(QFocusEvent*) override final;
        virtual void focusOutEvent(QFocusEvent*) override final;
        virtual void mouseMoveEvent(QMouseEvent* e) override final;
        virtual void mousePressEvent(QMouseEvent* e) override final;
        virtual void mouseReleaseEvent(QMouseEvent* e) override final;
        virtual void leaveEvent(QEvent* e) override final;

    };

    class RadioButton final : public ImageButton
    {
        Q_OBJECT
    public:
        RadioButton(const QString& text, const QString& button_group_name, QWidget* parent = nullptr);

    public:
        static void UncheckAll(QWidget* parent, const QString& button_group_name);

    protected slots:
        void OnButtonClicked(const bool checked);
    };
}
#endif // IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H
