#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_MENUDIALOG_H
#define IMAGEEDITOR_UI_WIDGETS_MENUDIALOG_H

#include <QWidget>
#include <Modules/types.h>
#include <UI/types.h>
#include <UI/Widgets/IWidget.h>


class QPushButton;
namespace ImageEditor::UI
{
    class UICommand;

    class MenuDialog final: public QWidget
    {
        Q_OBJECT
    public:
        struct Parameters
        {
          QWidget* parent;
          QString image_file_name;
        };

        explicit MenuDialog(Parameters parameters);
        MenuDialog& operator= (const MenuDialog&) = delete;

    signals: 
        void SignalOpenImage(QString file_name);
        void SignalSaveImage(QString file_name);

    protected:
        void mouseReleaseEvent(QMouseEvent* event);

    private slots: 
        void OnButtonOpenClicked();
        void OnButtonSaveClicked();
        void OnButtonCancelClicked();

    private:
        void CreateMenuButtons();
        QPushButton* CreateButton(QString name, int button_width);

    private:
        QString image_file_name_;
        QPushButton* save_button_ = nullptr;
    };
}
#endif // IMAGEEDITOR_UI_WIDGETS_MENUDIALOG_H
