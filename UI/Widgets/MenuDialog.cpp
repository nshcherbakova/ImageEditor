#include <stdafx.h>
#include <UI/UIString.h>
#include "MenuDialog.h"


static const char* c_open_str = "Open";
static const char* c_save_str = "Save";
static const char* c_cancel_str = "Cancel";
static const char* c_open_image_str = "Open Image";
static const char* c_save_image_str = "Save Image";
static const char* c_file_types_str = "Image Files (*.png *.jpg *.jpeg *.bmp)";
static const char* c_last_opend_dir = "last_opened_dir";
static const char* c_button_style_str = "QPushButton{  background-color: rgba(253, 253, 255, 255); color: rgb(100, 100, 100); font-size: 24px; font-family: Typo Round Regular Demo;}";
static const QColor c_background_color = QColor(250, 250, 247, 200);
static const int c_buttons_margin = 5;
static const int c_layout_margin_left = 150;
static const int c_layout_margin_top = 0;
static const int c_layout_margin_right = 150;
static const int c_layout_margin_bottom = 5;
static const int c_buttons_vmargin = 20;

namespace ImageEditor::UI
{
    MenuDialog::MenuDialog(Parameters parameters)
       : QWidget(parameters.parent)
       , image_file_name_(parameters.image_file_name)
    {
        UNI_ENSURE_RETURN(parameters.parent);

        setContentsMargins(0, 0, 0, 0);
        setGeometry(parameters.parent->geometry());

        setAutoFillBackground(true);
        auto palette = QWidget::palette();
        palette.setColor(QPalette::Window, c_background_color);
        setPalette(palette);

        CreateMenuButtons();
    }

    void MenuDialog::CreateMenuButtons()
    {
        const QRect parent_rect = geometry();
        const int button_height = parent_rect.height() / 6;

        // buttons widget
        QWidget* buttons_widget = new QWidget(this);
        buttons_widget->setContentsMargins(0, 0, 0, c_buttons_margin);
        buttons_widget->setGeometry(QRect(0, (parent_rect.height() - button_height * 3) / 2 - c_buttons_vmargin, parent_rect.width(), button_height * 3 + c_buttons_vmargin));

        // buttons layput
        auto filter_buttons_layout = new QVBoxLayout(buttons_widget);
        filter_buttons_layout->setContentsMargins(c_layout_margin_left, c_layout_margin_top, c_layout_margin_right, c_layout_margin_bottom);

        buttons_widget->setLayout(filter_buttons_layout);

        // create buttons
        QPushButton* open_button =  CreateButton(UIString(c_open_str), button_height);
        connect(open_button, &QPushButton::clicked, this, &MenuDialog::OnButtonOpenClicked);
        open_button->setStyleSheet(c_button_style_str);
        open_button->setMaximumHeight(button_height);

        save_button_ = CreateButton(UIString(c_save_str), button_height);
        connect(save_button_, &QPushButton::clicked, this, &MenuDialog::OnButtonSaveClicked);
        save_button_->setEnabled(!image_file_name_.isEmpty());
        save_button_->setStyleSheet(c_button_style_str);
        save_button_->setMaximumHeight(button_height);

        QPushButton* canel_button = CreateButton(UIString(c_cancel_str), button_height);
        connect(canel_button, &QPushButton::clicked, this, &MenuDialog::OnButtonCancelClicked);
        canel_button->setStyleSheet(c_button_style_str);
        canel_button->setMaximumHeight(button_height);

        filter_buttons_layout->addWidget(open_button);
        filter_buttons_layout->addWidget(save_button_);
        filter_buttons_layout->addWidget(canel_button);
    }

    QPushButton* MenuDialog::CreateButton(QString name, int button_height)
    {
        QPushButton* button = new QPushButton(name, this);
        const QRect menu_button_rect = QRect(0, 0, 0, button_height);
        button->setGeometry(menu_button_rect);
        button->setMinimumHeight(button_height);
        button->setContentsMargins(0, 0, 0, 0);

        return button;
    }

    void MenuDialog::OnButtonOpenClicked()
    {
        QString path = image_file_name_;
        if (path.isEmpty())
        {
            QSettings settings;
            path = settings.value(c_last_opend_dir).toString();
        }
        const QString file_name = QFileDialog::getOpenFileName(this,
            UIString(c_open_image_str),
            path,
            UIString(c_file_types_str));
        
        if (!file_name.isEmpty())
        {
            image_file_name_ = file_name;
            save_button_->setEnabled(!image_file_name_.isEmpty());
            emit SignalOpenImage(file_name);
            setVisible(false);

            QSettings settings;
            settings.setValue(c_last_opend_dir, QFileInfo(file_name).dir().path());
        }
    }

    void MenuDialog::OnButtonSaveClicked()
    {
        const QString file_name = QFileDialog::getSaveFileName(this,
           UIString(c_save_image_str),
           image_file_name_,
           UIString(c_file_types_str),
           0,
           QFileDialog::DontUseNativeDialog);

       if (!file_name.isEmpty())
       {
           image_file_name_ = file_name;
           emit SignalSaveImage(file_name);
           setVisible(false);
       }
    }

    void MenuDialog::OnButtonCancelClicked()
    {
        setVisible(false);
    }
}
