#include <stdafx.h>
#include <UI/UIString.h>
#include <QGraphicsAnchorLayout.h>
#include "FiltersWidget.h"


static const char* c_menu_str = "Menu";

namespace ImageEditor::UI
{
    FiltersWidget::FiltersWidget(QWidget& parent, Modules::IFramePtr filters_frame)
        :QWidget(&parent)
    {
        core::return_if_check(!filters_frame);

        setContentsMargins(0, 0, 0, 0);
        setGeometry(parent.geometry());
        
        QRect parent_rect = geometry();

        QPushButton* menu_button = new QPushButton(UIString(c_menu_str), this);
        int button_width = parent_rect.height() / 5;
        QRect menu_button_rect = QRect(parent_rect.width() - button_width, 0, button_width, button_width);
        menu_button->setGeometry(menu_button_rect);
        
        auto controls = filters_frame->Controls();
        core::return_if_check(!controls);

        auto buttons_it = controls->find(Modules::MENU_BUTTON_TAG);
        if (buttons_it != controls->end())
        {
            const auto ui_command = new UICommand(this, buttons_it->second);
            connect(menu_button, &QPushButton::clicked, ui_command, &UICommand::OnButtonClicked);
        }

        QWidget* filter_buttons_widget = new QWidget(this);
        filter_buttons_widget->setContentsMargins(0, 0, 0, 0);
        filter_buttons_widget->setGeometry(QRect(0, parent_rect.height() - button_width, parent_rect.width(), button_width));

        auto filter_buttons_layout = new QHBoxLayout(filter_buttons_widget);
        filter_buttons_layout->setContentsMargins(0, 0, 0, 0);

        filter_buttons_widget->setLayout(filter_buttons_layout);


        buttons_it = controls->find(Modules::FILTER_BUTTON_TAG);
        if (buttons_it != controls->end())
        {
            while (buttons_it != controls->end() && buttons_it->first == Modules::FILTER_BUTTON_TAG)
            {
                auto control = buttons_it->second;
                core::return_if_check(!control);

                const auto ui_command = new UICommand(this, control);

                const auto button = new QPushButton(UIString(control->Parameters()), filter_buttons_widget);
                QRect button_rect = QRect(0, 0, button_width, button_width);
                button->setGeometry(button_rect);
                button->setMinimumHeight(button_width);
                connect(button, &QPushButton::clicked, ui_command, &UICommand::OnButtonClicked);
                filter_buttons_layout->addWidget(button);

                buttons_it++;
            }
        }
        onShow(false);
    }

    void FiltersWidget::onShow(const bool visible)
    {
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