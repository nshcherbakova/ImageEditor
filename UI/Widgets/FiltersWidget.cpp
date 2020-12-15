#include <stdafx.h>
#include <UI/UIString.h>
#include <Modules/EditableImage/IEditableImage.h>
#include <Modules/Frames/IFrame.h>
#include <Modules/Frames/IControl.h>
#include <Core/Image/IImage.h>
#include <UI/QtConverts.h>
#include "FiltersWidget.h"
#include "MenuDialog.h"


static const char* c_menu_str = "";
static const char* c_clean_str = "";
static const char* c_last_opend_file_str = "last_opened_file";
static const QColor c_background_color = QColor(250, 250, 248);
static const QColor c_frame_pen_color = QColor(Qt::white);
static const int c_frame_pen_width = 3;
static const int c_image_top_margin = 20;
static const int c_button_width = 100;
static const char* c_filter_button_style_str = "QPushButton{ "
"background-image: url(:/ImageEditor/round_button);"
"background-color: rgba(255, 255, 255, 0); "
"font-size: 21px; "
"font-family: Typo Round Regular Demo;";

static const char* c_color_str_arr[] = {
    "color: rgb(150, 95, 95); }",
    "color: #D1854F; }",
    "color: #6F9B00; }",
    "color: #308BB2; }",
    "color: #8E2DB7; }"};

static const char* c_hover_str_arr[] = {
    "QPushButton:hover{background-image: url(:/ImageEditor/round_button_r); color: rgb(70, 70, 70);}",
    "QPushButton:hover{background-image: url(:/ImageEditor/round_button_y); color: rgb(70, 70, 70);}",
    "QPushButton:hover{background-image: url(:/ImageEditor/round_button_g); color: rgb(70, 70, 70);}",
    "QPushButton:hover{background-image: url(:/ImageEditor/round_button_b); color: rgb(70, 70, 70);}",
    "QPushButton:hover{background-image: url(:/ImageEditor/round_button_v); color: rgb(70, 70, 70);}" };

static const char* c_pressed_str_arr[] = { 
    "QPushButton:pressed{background-image: url(:/ImageEditor/round_button_r); color: rgb(70, 70, 70);}", 
    "QPushButton:pressed{background-image: url(:/ImageEditor/round_button_y); color: rgb(70, 70, 70);}",
    "QPushButton:pressed{background-image: url(:/ImageEditor/round_button_g); color: rgb(70, 70, 70);}", 
    "QPushButton:pressed{background-image: url(:/ImageEditor/round_button_b); color: rgb(70, 70, 70);}", 
    "QPushButton:pressed{background-image: url(:/ImageEditor/round_button_v); color: rgb(70, 70, 70);}" };

static const char* c_menu_button_style_str = "QPushButton{ background-image: "
"url(:/ImageEditor/round_button_menu); "
"background-color: rgba(255, 255, 255, 0);}"
"QPushButton:hover{background-image: url(:/ImageEditor/round_button_menu_hover); color: rgb(70, 70, 70);} "
"QPushButton:pressed{background-image: url(:/ImageEditor/round_button_menu_hover); color: rgb(70, 70, 70); }";

static const char* c_undo_button_style_str = "QPushButton{ background-image: "
"url(:/ImageEditor/button_undo); "
"background-color: rgba(255, 255, 255, 0);}"
"QPushButton:hover{background-image: url(:/ImageEditor/button_undo_hover); color: rgb(70, 70, 70);} "
"QPushButton:pressed{background-image: url(:/ImageEditor/button_undo_hover); color: rgb(70, 70, 70);}";

static const char* c_background_image_str = ":/ImageEditor/background";

namespace ImageEditor::UI
{
    FiltersWidget::FiltersWidget(Parameters parameters)
        : QWidget(&(parameters.parent))
        , editable_image_(parameters.image)
        , background_image_(c_background_image_str)
    {
        UNI_ENSURE_RETURN(parameters.filters_frame);

        setContentsMargins(0, 0, 0, 0);
        setGeometry(parameters.parent.geometry());
        setAutoFillBackground(true);
        auto palette = QWidget::palette();
        palette.setColor(QPalette::Window, c_background_color);
        setPalette(palette);
        //setStyleSheet(c_widget_style_str);

        CreateMenuButton(parameters.filters_frame->Controls());
        CreateCleanButton(parameters.filters_frame->Controls());
        CreateFilterButtons(parameters.filters_frame->Controls());

        onShow(false);
    }

    void FiltersWidget::CreateMenuButton(Modules::IControlsMapPtr controls)
    {
        UNI_ENSURE_RETURN(controls);
        
        QRect parent_rect = geometry();
        const int button_width = c_button_width;

        // create button
        QPushButton* menu_button = new Button(UIString(c_menu_str), this);
        QRect menu_button_rect = QRect(parent_rect.width() - button_width, 0, button_width, button_width);
        menu_button->setFlat(true);
        menu_button->setGeometry(menu_button_rect);
        menu_button->setContentsMargins(0, 0, 0, 0);
        menu_button->setMinimumWidth(button_width);
        menu_button->setMinimumHeight(button_width);
        menu_button->setMaximumHeight(button_width);
        menu_button->setMaximumWidth(button_width);
        menu_button->setStyleSheet(c_menu_button_style_str);

        connect(menu_button, &QPushButton::clicked, this, &FiltersWidget::OnMenuButtonClicked);
    }

    void FiltersWidget::OnMenuButtonClicked()
    {
        if (!menu_)
        {
            QSettings settings;
            const QString last_file = settings.value(c_last_opend_file_str).toString();
            menu_ = new MenuDialog(MenuDialog::Parameters{ this, last_file });
            connect(*menu_, &MenuDialog::SignalOpenImage, this, &FiltersWidget::OnSignalOpenImage);
            connect(*menu_, &MenuDialog::SignalSaveImage, this, &FiltersWidget::OnSignalSaveImage);
        }
        (*menu_)->setVisible(true);
    }

    void FiltersWidget::CreateCleanButton(Modules::IControlsMapPtr controls)
    {
        UNI_ENSURE_RETURN(controls);

        const  QRect parent_rect = geometry();
        int button_width = c_button_width;

        // create button
        QPushButton* button = new Button(UIString(c_clean_str), this);
        const QRect button_rect = QRect(0, 0, button_width, button_width);
        button->setGeometry(button_rect);
        button->setFlat(true);
        button->setContentsMargins(0, 0, 0, 0);
        button->setMinimumWidth(button_width);
        button->setMinimumHeight(button_width);
        button->setMaximumHeight(button_width);
        button->setMaximumWidth(button_width);
        button->setStyleSheet(c_undo_button_style_str);

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
        
        const QRect parent_rect = geometry();
        int button_width = c_button_width;

        // buttons widget
        QWidget* filter_buttons_widget = new QWidget(this);
        filter_buttons_widget->setContentsMargins(0, 0, 0, 0);
        filter_buttons_widget->setGeometry(QRect(0, parent_rect.height() - button_width, parent_rect.width(), button_width));

        // buttons layput
        auto filter_buttons_layout = new QHBoxLayout(filter_buttons_widget);
        filter_buttons_layout->setContentsMargins(0, 0, 0, 0);

        filter_buttons_widget->setLayout(filter_buttons_layout);

        // bind button with controls, add to layout
        int num = 0;
        auto buttons_it = controls->find(Modules::FILTER_BUTTON_TAG);
        if (buttons_it != controls->end())
        {
            while (buttons_it != controls->end() && buttons_it->first == Modules::FILTER_BUTTON_TAG)
            {
                auto control = buttons_it->second;
                UNI_ENSURE_RETURN(control);

                // create buttons
                const auto button = new Button(UIString(control->Parameters()), filter_buttons_widget);
                QRect button_rect = QRect(0, 0, button_width, button_width);
                button->setGeometry(button_rect);
                button->setMinimumWidth(button_width);
                button->setMinimumHeight(button_width);
                button->setMaximumHeight(button_width);
                button->setMaximumWidth(button_width);
                button->setFlat(true);
                
                int index = num % std::size(c_hover_str_arr);
                QString pressed(c_pressed_str_arr[index]);
                QString hover(c_hover_str_arr[index]);
                QString color(c_color_str_arr[index]);
                button->setStyleSheet(QString(c_filter_button_style_str) + color + hover + pressed);
              
                // bind button with control
                const auto ui_command = new UICommand(this, control);
                connect(button, &QPushButton::clicked, ui_command, &UICommand::OnButtonClicked);
                connect(ui_command, &UICommand::SignalCommandAppyed, this, &FiltersWidget::OnSignalCommandAppyed);

                //add button to layout
                filter_buttons_layout->addWidget(button);

                buttons_it++;
                num++;
            }
        }

        //const auto place_holder = new QWidget(filter_buttons_widget);
       /* const QRect rect = QRect(0, 0, button_width, button_width);
        place_holder->setGeometry(rect);
        place_holder->setMinimumHeight(button_width);
        filter_buttons_layout->addWidget(place_holder);*/
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
        QPainter painter(this);
        QRect dirty_rect = event->rect();
        painter.drawImage(dirty_rect, background_image_, dirty_rect);

        if (image_)
        {
            const auto new_image_height = geometry().size().height() - c_image_top_margin;
            QImage image = image_->scaledToHeight(new_image_height);

            dirty_rect.setLeft((dirty_rect.width() - image.rect().width()) / 2);
            dirty_rect.setTop(c_image_top_margin / 2);
            dirty_rect.setWidth(image.rect().width());
            dirty_rect.setHeight(image.rect().height());
            auto pen = painter.pen();
            pen.setColor(c_frame_pen_color);
            pen.setWidth(c_frame_pen_width);
            painter.setPen(pen);
            painter.drawRect(dirty_rect);
            painter.drawImage(dirty_rect, image, image.rect());
        }
    }

    void FiltersWidget::onShow(const bool visible)
    {
        QSettings settings;
        const QString last_file = settings.value(c_last_opend_file_str).toString();
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
    
    Button::Button(const QString& text, QWidget* parent)
        : QPushButton(text, parent)
    {}

    void Button::keyPressEvent(QKeyEvent* e)
    {
        update();
        parentWidget()->update();
        QPushButton::keyPressEvent(e);
    }

    void Button::focusInEvent(QFocusEvent* e)
    {
        update();
        parentWidget()->update();
        QPushButton::focusInEvent(e);
    }

    void Button::focusOutEvent(QFocusEvent* e)
    {
        update();
        parentWidget()->update();
        QPushButton::focusOutEvent(e);
    }

    void Button::mousePressEvent(QMouseEvent* e)
    {
        update();
        parentWidget()->update();
        QPushButton::mousePressEvent(e);
    }

    void Button::mouseReleaseEvent(QMouseEvent* e)
    {
        update();
        parentWidget()->update();
        QPushButton::mouseReleaseEvent(e);
    }

    void Button::mouseMoveEvent(QMouseEvent* e)
    {
        update();
        parentWidget()->update();
        QPushButton::mouseMoveEvent(e);
    }

    void Button::leaveEvent(QEvent* e)
    {
        update();
        parentWidget()->update();
        QWidget::leaveEvent(e);
    }

    void Button::enterEvent(QEvent* e)
    {
        update();
        parentWidget()->update();
        QWidget::enterEvent(e);
    }
}     