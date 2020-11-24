#include <stdafx.h>
#include "UIFiltersFrame.h"

namespace ImageEditor::UI::Frames
{
    UICommand::UICommand(QObject* parent, const Modules::IControlPtr& control): QObject(parent), control_(control)
        {
            assert(control_);
            if (!control_)
            {
                // todo log here
            }
        }
        void UICommand::OnButtonClicked()
        {
            assert(control_);
            if (control_)
            {
                control_->Activate(control_->Parameters());
            }
        }

    UIFiltersFrame::UIFiltersFrame(QWidget* parent, const Modules::IFramePtr& frame)
        :QGridLayout(parent), menu_button_(new QPushButton(QLatin1String("Menu"), parent))
    {
        assert(parent);
        if (!parent)
        {
            // todo log here
            return;
        }

        assert(frame);
        if (!frame)
        {
            // todo log here
            return;
        }
        

        setContentsMargins(0, 0, 0, 0);
        addWidget(menu_button_);
        setAlignment(menu_button_, Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignRight);
        setGeometry(parentWidget()->geometry());

        const auto controls = frame->Controls();
        assert(controls);
        if (!controls)
        {
            // todo log here
        }
        if (controls)
        {
            auto buttons_it = controls->find(Modules::MENU_BUTTON_TAG);
            if (buttons_it != controls->end())
            {
                const auto ui_command = new UICommand(this, buttons_it->second);
                connect(menu_button_, &QPushButton::clicked, ui_command, &UICommand::OnButtonClicked);
            }
        }


        auto filter_buttons_layout = new QHBoxLayout(parent);
        filter_buttons_layout->setContentsMargins(0, 0, 0, 0);

        addLayout(filter_buttons_layout, 0, 0);
        setAlignment(filter_buttons_layout, Qt::AlignmentFlag::AlignBottom | Qt::AlignmentFlag::AlignHCenter);


        auto filter_buttons_list_view = new QListView(parent);
        filter_buttons_list_view->setContentsMargins(0, 0, 0, 0);
        filter_buttons_layout->addWidget(filter_buttons_list_view);

        auto buttons_it = controls->find(Modules::FILTER_BUTTON_TAG);
        if (buttons_it != controls->end())
        {
            while (buttons_it->first == Modules::FILTER_BUTTON_TAG)
            {
                auto control = buttons_it->second;
                assert(control);
                if (!control)
                {
                    //todo log 
                    continue;
                }
                const auto ui_command = new UICommand(this, control);

                const auto button = new QPushButton(QLatin1String(control->Parameters().c_str()), parent);
                connect(button, &QPushButton::clicked, ui_command, &UICommand::OnButtonClicked);
                
                buttons_it++;
            }
        }
        onShow(false);
    }

    void UIFiltersFrame::onShow(const bool visible) 
    {
        setEnabled(visible);
        //setVisible(visible);
    }
}     