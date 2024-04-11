#include "FiltersWidget.h"
#include "Controls/ImageButton.h"
#include "Controls/RadioButton.h"
#include "MenuDialog.h"
#include "UICommand.h"
#include <stdafx.h>

// widget settings
static const char *c_last_opend_file_str = "last_opened_file";
static const QColor c_widget_background_color = QColor(250, 250, 248);
static const QColor c_widget_pen_color = QColor(255, 255, 255);
static const int c_widget_pen_width = 5;
// static const int c_widget_image_top_margin = 30;
static const int c_filter_buttons_bottom_margin = 20;
static const int c_up_buttons_top_margin = 30;
static const int c_up_buttons_side_margin = 12;
static const char *c_widget_background_image_str = ":/Images/widget_background";

// buttons settings
static const int c_menu_button_width = 80;
static const int c_menu_button_height = 50;
// #ifndef Q_OS_ANDROID
static const int c_filter_button_width = 72;
/*#else
static const int c_filter_button_width = 80;
static const char *c_round_button_str = "round_button_android";
#endif*/
static const char *c_filter_button_style_template_str =
    "QPushButton{"
    "background-color: rgba(255, 255, 255, 200);"
    "color: %1; "
    "font-size: 23px; "
    "font-family: Typo Round Regular Demo;"
    "border-style: solid;"
    "border-radius: 36;"
    "border-color: rgba(190, 190, 190, 255);"
    "border-width: 4;"
    "}"

    "QPushButton:disabled{color: rgb(190, 190, 190);}"
    "QPushButton:hover{border-color: rgba(170, 170, 170, 255);}"
    "QPushButton:checked{background-color: rgba(227, 215, 203, 220);}"
    "QPushButton:checked:pressed {border-color: rgba(170, 170, 170, 255);}"
    "QPushButton:pressed{background-color: rgba(239, 232, 225, 220);}";

static const char *c_menu_button_style_template_str =
    "QPushButton{"
    "background-color: rgba(255, 255, 255, 200);"
    "color: rgba(80, 80, 80, 255); "
    "font-size: 25px; "
    //   "font-weight: bold; "
    "font-family: Typo Round Regular Demo;"
    "border-style: solid;"
    "border-radius: 20;"
    "border-color: rgba(210, 210, 210, 255);"
    "border-width: 4;"
    "}"

    "QPushButton:disabled{"
    "color: rgba(160, 160, 160, 200);"
    "background-color: rgba(255, 255, 255, 85);"
    "border-color: rgba(240, 240, 240, 255);"
    "}"
    "QPushButton:pressed{background-color: rgba(239, 232, 225, 220);}";

static const char *c_filter_buttons_text_color_str_arr[] = {
    "rgb(95, 120, 180)", // first button color
    "#D1854F",           // second button color
    "#6F9B00",           // third button color
    "#308BB2",           // fourth button color
    "#8E2DB7"            // fifth button color
};

namespace ImageEditor::UI {
FiltersWidget::FiltersWidget(Parameters parameters)
    : QWidget(&(parameters.parent)),
      editable_image_(std::move(parameters.image)),
      background_image_(c_widget_background_image_str),
      network_(std::move(parameters.network)) {
  UNI_ENSURE_RETURN(parameters.filters_frame && editable_image_);

  setContentsMargins(0, 0, 0, 0);
  setGeometry(parameters.parent.geometry());
  setAutoFillBackground(true);
  auto palette = QWidget::palette();
  palette.setColor(QPalette::Window, c_widget_background_color);
  setPalette(palette);

  CreateMenuButton();
  CreateCleanButton();
  CreateFilterButtons(parameters.filters_frame->Controls());

  spdlog::info("FiltersWidget UI created");

  onShow(false);
  emit SignalEnableFilterButtons(false);
  emit SignalEnableCleanButton(false);
}

void FiltersWidget::CreateMenuButton() {
  QRect parent_rect = geometry();
  const int button_width = c_menu_button_width;

  // create menu button
  QPushButton *menu_button = new ImageButton("", this);
  QRect menu_button_rect =
      QRect(parent_rect.width() - button_width - c_up_buttons_side_margin,
            c_up_buttons_top_margin, button_width, c_menu_button_height);
  menu_button->setFlat(true);
  menu_button->setGeometry(menu_button_rect);
  menu_button->setContentsMargins(0, 0, 0, 0);
  menu_button->setMinimumWidth(button_width);
  menu_button->setMinimumHeight(c_menu_button_height);
  menu_button->setMaximumHeight(c_menu_button_height);
  menu_button->setMaximumWidth(button_width);
  menu_button->setText("Menu");
  menu_button->setStyleSheet(QString(c_menu_button_style_template_str));
  //    .arg(c_menu_button_image_prefix_str));

  connect(menu_button, &QPushButton::clicked, this,
          &FiltersWidget::OnMenuButtonClicked);
}

void FiltersWidget::OnMenuButtonClicked() {
  if (!menu_) {
    QSettings settings(QSettings::Scope::UserScope);
    const QString last_file = settings.value(c_last_opend_file_str).toString();
    menu_ = new MenuDialog(MenuDialog::Parameters{this, last_file});
    connect(*menu_, &MenuDialog::SignalOpenImage, this,
            &FiltersWidget::OnSignalOpenImage);
    connect(*menu_, &MenuDialog::SignalSaveImage, this,
            &FiltersWidget::OnSignalSaveImage);
    /*connect(*menu_, &MenuDialog::SignalUploadImage, this,
            &FiltersWidget::OnSignalUploadImage);*/
    connect(*menu_, &MenuDialog::SignalShareImage, this,
            &FiltersWidget::OnSignalShareImage);
  }
  (*menu_)->setVisible(true);
}

void FiltersWidget::CreateCleanButton() {
  // create clean button
  QPushButton *button = new ImageButton("", this);
  const QRect button_rect =
      QRect(c_up_buttons_side_margin, c_up_buttons_top_margin,
            c_menu_button_width, c_menu_button_height);
  button->setGeometry(button_rect);
  button->setFlat(true);
  button->setContentsMargins(0, 0, 0, 0);
  button->setMinimumWidth(c_menu_button_width);
  button->setMinimumHeight(c_menu_button_height);
  button->setMaximumHeight(c_menu_button_height);
  button->setMaximumWidth(c_menu_button_width);
  button->setText("Undo");
  button->setStyleSheet(QString(c_menu_button_style_template_str));
  //    .arg(c_menu_button_image_prefix_str));

  connect(button, &QPushButton::clicked, this,
          &FiltersWidget::OnCleanButtonClicked);
  connect(this, &FiltersWidget::SignalEnableCleanButton,
          static_cast<ImageButton *>(button), &ImageButton::OnSignalEnable);
}

void FiltersWidget::OnCleanButtonClicked() {
  UNI_ENSURE_RETURN(editable_image_ && editable_image_->Image());

  spdlog::info("FiltersWidget clean button clicked");

  editable_image_->UpdateImage(editable_image_->OriginalImage());
  UpdateImage();
  RadioButton::UncheckAll(this, Modules::FILTER_BUTTON_TAG);
  emit SignalEnableCleanButton(false);
}

void FiltersWidget::CreateFilterButtons(Modules::IControlsMapPtr controls) {
  UNI_ENSURE_RETURN(controls);

  const QRect parent_rect = geometry();
  const int button_width = c_filter_button_width;

  // buttons widget
  QWidget *filter_buttons_widget = new QWidget(this);
  filter_buttons_widget->setContentsMargins(0, 0, 0, 0);
  filter_buttons_widget->setGeometry(QRect(
      0, parent_rect.height() - button_width - c_filter_buttons_bottom_margin,
      parent_rect.width(), button_width));

  // buttons layput
  auto filter_buttons_layout = new QHBoxLayout(filter_buttons_widget);
  filter_buttons_layout->setContentsMargins(0, 0, 0, 0);

  filter_buttons_widget->setLayout(filter_buttons_layout);

  // bind button with controls, add to layout
  int num = 0;
  auto buttons_it = controls->find(Modules::FILTER_BUTTON_TAG);
  if (buttons_it != controls->end()) {
    while (buttons_it != controls->end() &&
           buttons_it->first == Modules::FILTER_BUTTON_TAG) {
      auto control = buttons_it->second;
      UNI_ENSURE_RETURN(control);

      // create buttons
      const auto button =
          new RadioButton(UIString(control->Parameters()),
                          Modules::FILTER_BUTTON_TAG, filter_buttons_widget);
      QRect button_rect = QRect(0, 0, button_width - 10, button_width);
      button->setGeometry(button_rect);
      button->setMinimumWidth(button_width);
      button->setMinimumHeight(button_width);
      button->setMaximumHeight(button_width);
      button->setMaximumWidth(button_width);
      button->setFlat(true);

      const int index = num % std::size(c_filter_buttons_text_color_str_arr);
      QString style_template(c_filter_button_style_template_str);
      QString style_with_args =
          style_template.arg(c_filter_buttons_text_color_str_arr[index]);
      // .arg(c_round_button_str);
      button->setStyleSheet(style_with_args);

      // bind button with control
      const auto ui_command = new UICommand(this, control);
      connect(button, &QPushButton::clicked, ui_command,
              &UICommand::OnButtonClicked);
      connect(ui_command, &UICommand::SignalCommandAppyed, this,
              &FiltersWidget::OnSignalCommandAppyed);

      connect(this, &FiltersWidget::SignalEnableFilterButtons, button,
              &ImageButton::OnSignalEnable);

      // add button to layout
      filter_buttons_layout->addWidget(button);

      buttons_it++;
      num++;
    }
  }
}

void FiltersWidget::OnSignalOpenImage(const QString path) {
  spdlog::info("Open new image {0}", path.toStdString());

  RadioButton::UncheckAll(this, Modules::FILTER_BUTTON_TAG);

  QSettings settings(QSettings::Scope::UserScope);
  settings.setValue(c_last_opend_file_str, path);

  QImageReader reader(path);
  reader.setAutoTransform(true);

  image_ = std::make_shared<QImage>();

  if (reader.read(image_.get())) {
    editable_image_->SetOriginalImage(QtImageToIImage(*image_));
    update();
  } else {
    image_.reset();
    spdlog::error("Fail to open image {0}", path.toStdString());
  }
  emit SignalEnableFilterButtons(image_ && !(image_->isNull()));
  emit SignalEnableCleanButton(false);
}

void FiltersWidget::OnSignalSaveImage(const QString path) {
  UNI_ENSURE_RETURN(image_);

  if (image_->save(path, "JPG")) {
    spdlog::info("Image was saved {0}", path.toStdString());

  } else {
    spdlog::error("Fail to save image {0}", path.toStdString());
    qWarning() << "Failed to save image";
  }
  /* QJniObject::callStaticMethod<void>("aha/androscanner/AndroScannerInJava",
                                              "scanForPicture",
                                              "(Ljava/lang/String;)V",
                                              QJniObject::fromString(path).object<jstring>());*/
}

void FiltersWidget::OnSignalUploadImage() {

  QByteArray byte_arr;
  QBuffer buffer(&byte_arr);
  buffer.open(QIODevice::WriteOnly);
  image_->save(&buffer, "JPG");

  Modules::Network::HttpPostBinary(
      network_.get(), network_->ImageServerUrl(), "image/jpeg", "1.jpg",
      std::vector<char>(byte_arr.cbegin(), byte_arr.cend()),
      [](int error_code) {
        spdlog::info("OnSignalUploadImage POST request code {0}", error_code);
        qWarning() << "OnSignalUploadImage POST request code " << error_code;
      });
}

void FiltersWidget::OnSignalShareImage() {}

void FiltersWidget::OnSignalCommandAppyed() { UpdateImage(); }

void FiltersWidget::UpdateImage() {
  UNI_ENSURE_RETURN(editable_image_ && editable_image_->Image());

  image_ = std::make_shared<QImage>(IImageToQtImage(editable_image_->Image()));

  emit SignalEnableCleanButton(true);

  update();
}

void FiltersWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  // Draw background
  QRectF dirty_rect = geometry().toRectF();
  QImage scaled_background_image = background_image_.scaledToWidth(
      dirty_rect.width(), Qt::SmoothTransformation);
  painter.drawImage(0, dirty_rect.height() - scaled_background_image.height(),
                    scaled_background_image);

  // Draw Image
  if (image_ && !image_->isNull()) {
    const auto geom_height = dirty_rect.height();
    const auto geom_width = dirty_rect.width();

    QRectF paint_rect;
    if (geom_height / geom_width > image_->height() / image_->width()) {
      paint_rect.setWidth(geom_width - 2.0 * c_widget_pen_width);
      paint_rect.setHeight(image_->height() * paint_rect.width() /
                           image_->width());
      paint_rect.moveTop((dirty_rect.height() - paint_rect.height()) / 2.0);
      paint_rect.moveLeft(c_widget_pen_width);
    } else {
      paint_rect.setHeight(geom_height - 2.0 * c_widget_pen_width);
      paint_rect.setWidth(image_->width() * paint_rect.height() /
                          image_->height());
      paint_rect.moveLeft((dirty_rect.width() - paint_rect.width()) / 2.0);
      paint_rect.moveTop(c_widget_pen_width);
    }

    auto pen = painter.pen();
    pen.setColor(c_widget_pen_color);
    pen.setWidth(c_widget_pen_width);
    painter.setPen(pen);
    painter.drawRect(paint_rect);

    painter.drawImage(paint_rect, *image_, image_->rect(),
                      Qt::AutoColor | Qt::DiffuseDither);
  }
}

void FiltersWidget::onShow(const bool visible) {
  QSettings settings(QSettings::Scope::UserScope);
  const QString last_file = settings.value(c_last_opend_file_str).toString();
  if (!last_file.isEmpty()) {
    OnSignalOpenImage(last_file);
  }

  setEnabled(visible);
}
} // namespace ImageEditor::UI
