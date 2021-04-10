#include <stdafx.h>
#include <UI/UIString.h>
#include <Modules/EditableImage/IEditableImage.h>
#include <Modules/Frames/IFrame.h>
#include <Modules/Frames/IControl.h>
#include <Core/Image/IImage.h>
#include <UI/ImageProvider/IImageProvider.h>
#include <UI/QtConverts.h>
#include "FiltersWidget.h"
#include "MenuDialog.h"

// widget settings
static const char* c_last_opend_file_str = "last_opened_file";
static const QColor c_widget_background_color = QColor(250, 250, 248);
static const QColor c_widget_pen_color = QColor(Qt::white);
static const int c_widget_pen_width = 3;
static const int c_widget_image_top_margin = 30;
static const char* c_widget_background_image_str = "widget_background";
// buttons settings
static const int c_button_width = 100;

static const char* c_filter_button_style_template_str = "QPushButton{ "
"background-image: url(%2/round_button);"
"background-color: transparent; "
"font-size: 21px; "
"font-family: Typo Round Regular Demo;"
"color: %1;}"
"QPushButton:hover{background-image: url(%2/round_button_pressed);}"
"QPushButton:checked{background-image: url(%2/round_button_checked);}"
"QPushButton:checked:pressed {background-image: url(%2/round_button_checked);}"
"QPushButton:pressed{background-image: url(%2/round_button_checked);}";

static const char* c_filter_buttons_text_color_str_arr[] = {
    "rgb(95, 120, 180)", // first button color
    "#D1854F", // second button color
    "#6F9B00", // third button color
    "#308BB2", // fourth button color
    "#8E2DB7" // fifth button color
};

static const char* c_image_button_style_template_str = "QPushButton{ "
"background-image: "
"url(%2/%1_button); "
"background-color: transparent;}"
"QPushButton:hover{background-image: url(%2/%1_button_pressed)} "
"QPushButton:pressed{background-image: url(%2/%1_button_pressed)}";

static const char* c_menu_button_image_prefix_str = "menu";
static const char* c_undo_button_image_prefix_str = "undo";


namespace ImageEditor::UI
{
    FiltersWidget::FiltersWidget(Parameters parameters)
        : QWidget(&(parameters.parent))
        , editable_image_(std::move(parameters.image))
        , ui_image_provider_(std::move(parameters.image_provider))
        , background_image_(ui_image_provider_->image(c_widget_background_image_str))
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
        QPushButton* menu_button = new ImageButton("", this);
        QRect menu_button_rect = QRect(parent_rect.width() - button_width, 0, button_width, button_width);
        menu_button->setFlat(true);
        menu_button->setGeometry(menu_button_rect);
        menu_button->setContentsMargins(0, 0, 0, 0);
        menu_button->setMinimumWidth(button_width);
        menu_button->setMinimumHeight(button_width);
        menu_button->setMaximumHeight(button_width);
        menu_button->setMaximumWidth(button_width);
        menu_button->setStyleSheet(QString(c_image_button_style_template_str).arg(c_menu_button_image_prefix_str)
            .arg(ui_image_provider_->imagesPath()));

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
        QPushButton* button = new ImageButton("", this);
        const QRect button_rect = QRect(0, 0, button_width, button_width);
        button->setGeometry(button_rect);
        button->setFlat(true);
        button->setContentsMargins(0, 0, 0, 0);
        button->setMinimumWidth(button_width);
        button->setMinimumHeight(button_width);
        button->setMaximumHeight(button_width);
        button->setMaximumWidth(button_width);
        button->setStyleSheet(QString(c_image_button_style_template_str).arg(c_undo_button_image_prefix_str)
            .arg(ui_image_provider_->imagesPath()));

        connect(button, &QPushButton::clicked, this, &FiltersWidget::OnCleanButtonClicked);
    }

    void FiltersWidget::OnCleanButtonClicked()
    {
        UNI_ENSURE_RETURN(editable_image_ && editable_image_->Image());

        editable_image_->UpdateImage(editable_image_->OriginalImage());
        UpdateImage();
        RadioButton::UncheckAll(this, Modules::FILTER_BUTTON_TAG);
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
                const auto button = new RadioButton(UIString(control->Parameters()), Modules::FILTER_BUTTON_TAG, filter_buttons_widget);
                QRect button_rect = QRect(0, 0, button_width, button_width);
                button->setGeometry(button_rect);
                button->setMinimumWidth(button_width);
                button->setMinimumHeight(button_width);
                button->setMaximumHeight(button_width);
                button->setMaximumWidth(button_width);
                button->setFlat(true);

                int index = num % std::size(c_filter_buttons_text_color_str_arr);
                QString style_template(c_filter_button_style_template_str);
                QString style_with_args = style_template.arg(c_filter_buttons_text_color_str_arr[index])
                    .arg(ui_image_provider_->imagesPath());
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
        RadioButton::UncheckAll(this, Modules::FILTER_BUTTON_TAG);

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
         //QDir picDir = QDir(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
         //QString filePath = picDir.filePath("test123.jpg");

           image_->save(path);
      /*   QAndroidJniObject::callStaticMethod<void>("aha/androscanner/AndroScannerInJava",
                                                    "scanForPicture",
                                                    "(Ljava/lang/String;)V",
                                                    QAndroidJniObject::fromString(filePath).object<jstring>());*/
    }

    void FiltersWidget::OnSignalCommandAppyed()
    {
        UpdateImage();
    }

    void FiltersWidget::UpdateImage()
    {
        UNI_ENSURE_RETURN(editable_image_ && editable_image_->Image());

        image_ = std::make_shared<QImage>(IImageToQtImage(editable_image_->Image()));

        update();
    }

    void FiltersWidget::paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        QRect dirty_rect = event->rect();
        QImage scaled_background_image = background_image_.scaledToWidth(dirty_rect.width(), Qt::SmoothTransformation);
        painter.drawImage(0, dirty_rect.height() - scaled_background_image.height()
            , scaled_background_image);

        if (image_)
        {
            const auto new_image_height = geometry().size().height() - c_widget_image_top_margin;
            QImage image = image_->scaledToHeight(new_image_height, Qt::SmoothTransformation);

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
    
    void RadioButton::UncheckAll(QWidget* parent, const QString& button_group_name)
    {
        QList<QPushButton*> buttons = parent->findChildren<QPushButton*>(button_group_name);
        for (auto& button : buttons)
        {
            if (button->isChecked())
            {
                button->setChecked(false);
                button->update();
                button->parentWidget()->update();
            }
        }
    }

    RadioButton::RadioButton(const QString& text, const QString& button_group_name, QWidget* parent)
        : ImageButton(text, parent)
    {
        setObjectName(button_group_name);
        setCheckable(true);
        connect(this, &QPushButton::clicked, this, &RadioButton::OnButtonClicked);
    }

    void RadioButton::OnButtonClicked(bool checked)
    {
        if (checked)
        {
            QList<QPushButton*> buttons = parentWidget()->findChildren<QPushButton*>(objectName());
            for (auto& button : buttons)
            {
                if (button != this && button->isChecked())
                {
                    button->setChecked(false);
                }
            }
        }
        else
        {
            QPushButton::setChecked(true);
        }
        update();
        parentWidget()->update();
    }

    ImageButton::ImageButton(const QString& text, QWidget* parent)
        : QPushButton(text, parent)
    {
    }

    void ImageButton::keyPressEvent(QKeyEvent* e)
    {
        update();
        parentWidget()->update();
        QPushButton::keyPressEvent(e);
    }

    void ImageButton::focusInEvent(QFocusEvent* e)
    {
        update();
        parentWidget()->update();
        QPushButton::focusInEvent(e);
    }

    void ImageButton::focusOutEvent(QFocusEvent* e)
    {
        update();
        parentWidget()->update();
        QPushButton::focusOutEvent(e);
    }

    void ImageButton::mousePressEvent(QMouseEvent* e)
    {
        update();
        parentWidget()->update();
        QPushButton::mousePressEvent(e);
    }

    void ImageButton::mouseReleaseEvent(QMouseEvent* e)
    {
        update();
        parentWidget()->update();
        QPushButton::mouseReleaseEvent(e);
    }

    void ImageButton::mouseMoveEvent(QMouseEvent* e)
    {
        update();
        parentWidget()->update();
        QPushButton::mouseMoveEvent(e);
    }

    void ImageButton::leaveEvent(QEvent* e)
    {
        update();
        parentWidget()->update();
        QWidget::leaveEvent(e);
    }

    void ImageButton::enterEvent(QEvent* e)
    {
        update();
        parentWidget()->update();
        QWidget::enterEvent(e);
    }
}     
