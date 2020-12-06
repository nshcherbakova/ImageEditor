#include <stdafx.h>
#include <UI/UIString.h>
#include "FiltersWidget.h"


static const char* c_menu_str = "Menu";

namespace ImageEditor::UI
{
    FiltersWidget::FiltersWidget(Parameters parameters)
        : QWidget(&(parameters.parent))
        , editable_image_(parameters.image)
    {
        core::return_if_check(!parameters.filters_frame);

        setContentsMargins(0, 0, 0, 0);
        setGeometry(parameters.parent.geometry());
        
        CreateMenuButton(parameters.filters_frame->Controls());
        CreateFilterButtons(parameters.filters_frame->Controls());
        
        onShow(false);
    }

    void FiltersWidget::CreateMenuButton(Modules::IControlsMapPtr controls)
    {
        core::return_if_check(!controls);
        
        QRect parent_rect = geometry();
        int button_width = parent_rect.height() / 5;

        // create button
        QPushButton* menu_button = new QPushButton(UIString(c_menu_str), this);
        QRect menu_button_rect = QRect(parent_rect.width() - button_width, 0, button_width, button_width);
        menu_button->setGeometry(menu_button_rect);

        // bind button with control
        auto buttons_it = controls->find(Modules::MENU_BUTTON_TAG);
        if (buttons_it != controls->end())
        {
            const auto ui_command = new UICommand(this, buttons_it->second);
            connect(menu_button, &QPushButton::clicked, ui_command, &UICommand::OnButtonClicked);
        }
    }

    void FiltersWidget::CreateFilterButtons(Modules::IControlsMapPtr controls)
    {
        core::return_if_check(!controls);
        
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
                core::return_if_check(!control);

                // create buttons
                const auto button = new QPushButton(UIString(control->Parameters()), filter_buttons_widget);
                QRect button_rect = QRect(0, 0, button_width, button_width);
                button->setGeometry(button_rect);
                button->setMinimumHeight(button_width);

                // bind button with control
                const auto ui_command = new UICommand(this, control);
                connect(button, &QPushButton::clicked, ui_command, &UICommand::OnButtonClicked);

                //add button to layout
                filter_buttons_layout->addWidget(button);

                buttons_it++;
            }
        }
    }

    void FiltersWidget::OnSignalOpenImage(QString path)
    {
        QImage loaded_image;
        if (!loaded_image.load(path))
            core::return_if_check(false);

        auto new_image_height = geometry().size().height();
       
        image_ = std::make_shared<QImage>();
        *image_ = loaded_image.scaledToHeight(new_image_height);

        Core::IImagePtr core_image = Core::InitImageModule(
            std::vector<uchar>(image_->bits(), image_->bits() + image_->sizeInBytes()),
            image_->width(),
            image_->height(),
            image_->bytesPerLine(),
            image_->format()).create<Core::IImagePtr>();
           

        editable_image_->UpdateImage(core_image);

        update();
    }

    void FiltersWidget::OnSignalSaveImage(QString path)
    {
        core::return_if_check(!image_);

        image_->save(path);
    }

    void FiltersWidget::paintEvent(QPaintEvent* event)
    {
        core::return_if_check(!image_);
        
        QPainter painter(this);
        QRect dirty_rect = event->rect();
        dirty_rect.setLeft((dirty_rect.width() - image_->rect().width()) / 2);
        dirty_rect.setWidth(image_->rect().width());
        painter.drawImage(dirty_rect, *image_, image_->rect());
    }

    void FiltersWidget::onShow(const bool visible)
    {
        OnSignalOpenImage("C:\\Users\\npopl\\OneDrive\\Desktop\\pexels-photo-2103864.jpeg");
        setEnabled(visible);
        //setVisible(visible);
    }
}

namespace ImageEditor::UI
{
    UICommand::UICommand(QObject* parent, Modules::IControlPtr control) : QObject(parent), control_(control)
    {
        core::return_if_check(!control_);
        if (!control_)
        {
            // todo log here
        }
    }

    void UICommand::OnButtonClicked()
    {
        core::return_if_check(!control_);
        assert(control_);
        if (control_)
        {
            control_->Activate(control_->Parameters());
        }
    }
}     