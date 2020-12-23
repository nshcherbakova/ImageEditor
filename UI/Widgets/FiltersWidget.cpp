#include <stdafx.h>
#include <UI/UIString.h>
#include <Modules/EditableImage/IEditableImage.h>
#include <Modules/Frames/IFrame.h>
#include <Modules/Frames/IControl.h>
#include <Core/Image/IImage.h>
#include <UI/QtConverts.h>
#include "FiltersWidget.h"
#include "MenuDialog.h"

// widget settings
static const char* c_last_opend_file_str = "last_opened_file";
static const QColor c_widget_background_color = QColor(250, 250, 248);
static const QColor c_widget_pen_color = QColor(Qt::white);
static const int c_widget_pen_width = 3;
static const int c_widget_image_top_margin = 20;
static const char* c_widget_background_image_str = ":/ImageEditor/widget_background";
// buttons settings
static const int c_button_width = 100;

static const char* c_filter_button_style_template_str = "QPushButton{ "
"background-image: url(:/ImageEditor/round_button);"
"background-color: rgba(255, 255, 255, 0); "
"font-size: 21px; "
"font-family: Typo Round Regular Demo;"
"color: %1;}"
"QPushButton:hover{background-image: url(:/ImageEditor/round_button_pressed); color: rgb(70, 70, 70);}"
"QPushButton:pressed{background-image: url(:/ImageEditor/round_button_pressed); color: rgb(70, 70, 70);}";

static const char* c_filter_buttons_text_color_str_arr[] = {
    "rgb(95, 120, 180)", // first button color
    "#D1854F", // second button color
    "#6F9B00", // third button color
    "#308BB2", // fourth button color
    "#8E2DB7" // fifth button color
};

static const char* c_image_button_style_template_str = "QPushButton{ "
"background-image: "
"url(:/ImageEditor/%1_button); "
"background-color: rgba(255, 255, 255, 0);}"
"QPushButton:hover{background-image: url(:/ImageEditor/%1_button_pressed)} "
"QPushButton:pressed{background-image: url(:/ImageEditor/%1_button_pressed)}";

static const char* c_menu_button_image_prefix_str = "menu";
static const char* c_undo_button_image_prefix_str = "undo";


namespace ImageEditor::UI
{
    FiltersWidget::FiltersWidget(Parameters parameters)
        : QWidget(&(parameters.parent))
        , editable_image_(parameters.image)
        , background_image_(c_widget_background_image_str)
    {
        UNI_ENSURE_RETURN(parameters.filters_frame);

        setContentsMargins(0, 0, 0, 0);
        setGeometry(parameters.parent.geometry());
        setAutoFillBackground(true);
        auto palette = QWidget::palette();
        palette.setColor(QPalette::Window, c_widget_background_color);
        setPalette(palette);

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
        QPushButton* menu_button = new Button("", this);
        QRect menu_button_rect = QRect(parent_rect.width() - button_width, 0, button_width, button_width);
        menu_button->setFlat(true);
        menu_button->setGeometry(menu_button_rect);
        menu_button->setContentsMargins(0, 0, 0, 0);
        menu_button->setMinimumWidth(button_width);
        menu_button->setMinimumHeight(button_width);
        menu_button->setMaximumHeight(button_width);
        menu_button->setMaximumWidth(button_width);
        menu_button->setStyleSheet(QString(c_image_button_style_template_str).arg(c_menu_button_image_prefix_str));

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

        int button_width = c_button_width;

        // create button
        QPushButton* button = new Button("", this);
        const QRect button_rect = QRect(0, 0, button_width, button_width);
        button->setGeometry(button_rect);
        button->setFlat(true);
        button->setContentsMargins(0, 0, 0, 0);
        button->setMinimumWidth(button_width);
        button->setMinimumHeight(button_width);
        button->setMaximumHeight(button_width);
        button->setMaximumWidth(button_width);
        button->setStyleSheet(QString(c_image_button_style_template_str).arg(c_undo_button_image_prefix_str));

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
                
                int index = num % std::size(c_filter_buttons_text_color_str_arr);
                QString style_template(c_filter_button_style_template_str);
                QString style_with_args = style_template.arg(c_filter_buttons_text_color_str_arr[index]);
                button->setStyleSheet(style_with_args);
              
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
            const auto new_image_height = geometry().size().height() - c_widget_image_top_margin;
            QImage image = image_->scaledToHeight(new_image_height);

            dirty_rect.setLeft((dirty_rect.width() - image.rect().width()) / 2);
            dirty_rect.setTop(c_widget_image_top_margin / 2);
            dirty_rect.setWidth(image.rect().width());
            dirty_rect.setHeight(image.rect().height());
            auto pen = painter.pen();
            pen.setColor(c_widget_pen_color);
            pen.setWidth(c_widget_pen_width);
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
