#include <stdafx.h>
#include <UI/UIString.h>
#include "MenuDialog.h"


static const char* c_open_str = "Open";
static const char* c_save_str = "Save";
static const char* c_cancel_str = "Cancel";
static const char* c_open_image_str = "Open Image";
static const char* c_save_image_str = "Save Image";
static const char* c_file_types_str = "Image Files (*.png *.jpg *.jpeg *.bmp)";
static const char* c_last_opend_dir = "last_opend_dir";

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

        CreateMenuButtons();
    }

    void MenuDialog::CreateMenuButtons()
    {
        QRect parent_rect = geometry();
        int button_width = parent_rect.height() / 5;

        // buttons widget
        QWidget* buttons_widget = new QWidget(this);
        buttons_widget->setContentsMargins(0, 0, 0, 5);
        buttons_widget->setGeometry(QRect(0, (parent_rect.height() - button_width * 3) / 2, parent_rect.width(), button_width * 3));

        // buttons layput
        auto filter_buttons_layout = new QVBoxLayout(buttons_widget);
        filter_buttons_layout->setContentsMargins(0, 0, 0, 5);

        buttons_widget->setLayout(filter_buttons_layout);

        // create buttons
        QPushButton* open_button =  CreateButton(UIString(c_open_str), button_width);
        connect(open_button, &QPushButton::clicked, this, &MenuDialog::OnButtonOpenClicked);

        save_button_ = CreateButton(UIString(c_save_str), button_width);
        connect(save_button_, &QPushButton::clicked, this, &MenuDialog::OnButtonSaveClicked);
        save_button_->setEnabled(!image_file_name_.isEmpty());

        QPushButton* canel_button = CreateButton(UIString(c_cancel_str), button_width);
        connect(canel_button, &QPushButton::clicked, this, &MenuDialog::OnButtonCancelClicked);

        filter_buttons_layout->addWidget(open_button);
        filter_buttons_layout->addWidget(save_button_);
        filter_buttons_layout->addWidget(canel_button);
    }

    QPushButton* MenuDialog::CreateButton(QString name, int button_width)
    {
        QRect parent_rect = geometry();
        QPushButton* button = new QPushButton(name, this);
        QRect menu_button_rect = QRect(parent_rect.width() - button_width, 0, parent_rect.width(), button_width);
        button->setGeometry(menu_button_rect);
        button->setMinimumHeight(button_width);
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
        QString file_name = QFileDialog::getOpenFileName(this,
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
       QString file_name = QFileDialog::getSaveFileName(this,
           UIString(c_save_image_str),
           image_file_name_,
           UIString(c_file_types_str));

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
