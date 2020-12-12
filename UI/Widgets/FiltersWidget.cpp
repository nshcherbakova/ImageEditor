#include <stdafx.h>
#include <UI/UIString.h>
#include <Modules/EditableImage/IEditableImage.h>
#include <Modules/Frames/IFrame.h>
#include <Modules/Frames/IControl.h>
#include <Core/Image/IImage.h>
#include <UI/QtConverts.h>
#include "FiltersWidget.h"
#include "MenuDialog.h"


static const char* c_menu_str = "Menu";
static const char* c_clean_str = "Clean";
static const char* c_last_opend_file_str = "last_opend_file";

namespace ImageEditor::UI
{
    FiltersWidget::FiltersWidget(Parameters parameters)
        : QWidget(&(parameters.parent))
        , editable_image_(parameters.image)
    {
        UNI_ENSURE_RETURN(parameters.filters_frame);

        setContentsMargins(0, 0, 0, 0);
        setGeometry(parameters.parent.geometry());
        
        CreateMenuButton(parameters.filters_frame->Controls());
        CreateCleanButton(parameters.filters_frame->Controls());
        CreateFilterButtons(parameters.filters_frame->Controls());
        
        onShow(false);
    }

    void FiltersWidget::CreateMenuButton(Modules::IControlsMapPtr controls)
    {
        UNI_ENSURE_RETURN(controls);
        
        QRect parent_rect = geometry();
        int button_width = parent_rect.height() / 5;

        // create button
        QPushButton* menu_button = new QPushButton(UIString(c_menu_str), this);
        QRect menu_button_rect = QRect(parent_rect.width() - button_width, 0, button_width, button_width);
        menu_button->setGeometry(menu_button_rect);

        connect(menu_button, &QPushButton::clicked, this, &FiltersWidget::OnMenuButtonClicked);
    }

    void FiltersWidget::OnMenuButtonClicked()
    {
        if (!menu_)
        {
            QSettings settings;
            QString last_file = settings.value(c_last_opend_file_str).toString();
            menu_ = new MenuDialog(MenuDialog::Parameters{ this, last_file });
            connect(*menu_, &MenuDialog::SignalOpenImage, this, &FiltersWidget::OnSignalOpenImage);
            connect(*menu_, &MenuDialog::SignalSaveImage, this, &FiltersWidget::OnSignalSaveImage);
        }
        (*menu_)->setVisible(true);
    }

    void FiltersWidget::CreateCleanButton(Modules::IControlsMapPtr controls)
    {
        UNI_ENSURE_RETURN(controls);

        QRect parent_rect = geometry();
        int button_width = parent_rect.height() / 5;

        // create button
        QPushButton* button = new QPushButton(UIString(c_clean_str), this);
        QRect button_rect = QRect(parent_rect.width() - button_width, button_width, button_width, button_width);
        button->setGeometry(button_rect);

        connect(button, &QPushButton::clicked, this, &FiltersWidget::OnCleanButtonClicked);
    }

    void FiltersWidget::OnCleanButtonClicked()
    {
        UNI_ENSURE_RETURN(editable_image_ && editable_image_->Image());

        editable_image_->UpdateImage(editable_image_->OriginalImage());
        OnSignalCommandAppyed();
    }

    void FiltersWidget::CreateFilterButtons(Modules::IControlsMapPtr controls)
    {
        UNI_ENSURE_RETURN(controls);
        
        QRect parent_rect = geometry();
        int button_width = parent_rect.height() / 5;

        // buttons widget
        QWidget* filter_buttons_widget = new QWidget(this);
        filter_buttons_widget->setContentsMargins(0, 0, 0, 0);
        filter_buttons_widget->setGeometry(QRect(0, parent_rect.height() - button_width, parent_rect.width(), button_width));

        // buttons layput
        auto filter_buttons_layout = new QHBoxLayout(filter_buttons_widget);
        filter_buttons_layout->setContentsMargins(0, 0, 0, 0);

        filter_buttons_widget->setLayout(filter_buttons_layout);

        // bind button with controls, add to layout
        auto buttons_it = controls->find(Modules::FILTER_BUTTON_TAG);
        if (buttons_it != controls->end())
        {
            while (buttons_it != controls->end() && buttons_it->first == Modules::FILTER_BUTTON_TAG)
            {
                auto control = buttons_it->second;
                UNI_ENSURE_RETURN(control);

                // create buttons
                const auto button = new QPushButton(UIString(control->Parameters()), filter_buttons_widget);
                QRect button_rect = QRect(0, 0, button_width, button_width);
                button->setGeometry(button_rect);
                button->setMinimumHeight(button_width);
                button->setMaximumWidth(button_width);

                // bind button with control
                const auto ui_command = new UICommand(this, control);
                connect(button, &QPushButton::clicked, ui_command, &UICommand::OnButtonClicked);
                connect(ui_command, &UICommand::SignalCommandAppyed, this, &FiltersWidget::OnSignalCommandAppyed);

                //add button to layout
                filter_buttons_layout->addWidget(button);

                buttons_it++;
            }
        }

        const auto place_holder = new QWidget(filter_buttons_widget);
        QRect rect = QRect(0, 0, button_width, button_width);
        place_holder->setGeometry(rect);
        place_holder->setMinimumHeight(button_width);
        filter_buttons_layout->addWidget(place_holder);
    }

    void FiltersWidget::OnSignalOpenImage(QString path)
    {
        QSettings settings;
        settings.setValue(c_last_opend_file_str, path);

        image_ = std::make_shared<QImage>();
        if (!image_->load(path))
        {
            UNI_ENSURE_RETURN(false);
        }

        editable_image_->SetOriginalImage(QtImageToIImage(*image_));
        
        update();
    }

    void FiltersWidget::OnSignalSaveImage(QString path)
    {
        UNI_ENSURE_RETURN(image_);
        image_->save(path);
    }

    void FiltersWidget::OnSignalCommandAppyed()
    {
        UNI_ENSURE_RETURN(editable_image_ && editable_image_->Image());

        image_ = std::make_shared<QImage>(IImageToQtImage(editable_image_->Image()));

        update();
    }

    void FiltersWidget::paintEvent(QPaintEvent* event)
    {
        if (image_)
        {
            auto new_image_height = geometry().size().height();
            QImage image = image_->scaledToHeight(new_image_height);

            QPainter painter(this);
            QRect dirty_rect = event->rect();
            dirty_rect.setLeft((dirty_rect.width() - image.rect().width()) / 2);
            dirty_rect.setWidth(image.rect().width());
            painter.drawImage(dirty_rect, image, image.rect());
        }
    }

    void FiltersWidget::onShow(const bool visible)
    {
        QSettings settings;
        QString last_file = settings.value(c_last_opend_file_str).toString();
        if (!last_file.isEmpty())
        {
            OnSignalOpenImage(last_file);
        }
        setEnabled(visible);
    }
}

namespace ImageEditor::UI
{
    UICommand::UICommand(QObject* parent, Modules::IControlPtr control) : QObject(parent), control_(control)
    {
        UNI_ENSURE_RETURN(control_);
    }

    void UICommand::OnButtonClicked()
    {
        UNI_ENSURE_RETURN(control_);
        control_->Activate(control_->Parameters());
        emit SignalCommandAppyed();
    }
}     