#include "FiltersWidget.h"
#include "MenuDialog.h"
#include <stdafx.h>

// widget settings
static const char *c_last_opend_file_str = "last_opened_file";
static const QColor c_widget_background_color = QColor(250, 250, 248);
static const QColor c_widget_pen_color = QColor(Qt::white);
static const int c_widget_pen_width = 3;
static const int c_widget_image_top_margin = 30;
static const char *c_widget_background_image_str = ":/Images/widget_background";

// buttons settings
static const int c_button_width = 100;

static const char *c_filter_button_style_template_str =
    "QPushButton{ "
    "background-image: url(:/Images/round_button);"
    "background-color: transparent; "
    "font-size: 21px; "
    "font-family: Typo Round Regular Demo;"
    "color: %1;}"
    "QPushButton:disabled{color: rgb(190, 190, 190);}"
    "QPushButton:hover{background-image: url(:/Images/round_button_pressed);}"
    "QPushButton:checked{background-image: url(:/Images/round_button_checked);}"
    "QPushButton:checked:pressed {background-image: "
    "url(:/Images/round_button_checked);}"
    "QPushButton:pressed{background-image: "
    "url(:/Images/round_button_checked);}";

static const char *c_filter_buttons_text_color_str_arr[] = {
    "rgb(95, 120, 180)", // first button color
    "#D1854F",           // second button color
    "#6F9B00",           // third button color
    "#308BB2",           // fourth button color
    "#8E2DB7"            // fifth button color
};

static const char *c_image_button_style_template_str =
    "QPushButton{ "
    "background-image: "
    "url(:/Images/%1_button); "
    "background-color: transparent;}"
    "QPushButton:disabled{background-image: url(:/Images/%1_button_disabled)} "
    "QPushButton:hover{background-image: url(:/Images/%1_button_pressed)} "
    "QPushButton:pressed{background-image: url(:/Images/%1_button_pressed)}";

static const char *c_menu_button_image_prefix_str = "menu";
static const char *c_undo_button_image_prefix_str = "undo";

namespace ImageEditor::UI {
FiltersWidget::FiltersWidget(Parameters parameters)
    : QWidget(&(parameters.parent)),
      editable_image_(std::move(parameters.image)),
      background_image_(c_widget_background_image_str) {
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
  const int button_width = c_button_width;

  // create menu button
  QPushButton *menu_button = new ImageButton("", this);
  QRect menu_button_rect =
      QRect(parent_rect.width() - button_width, 0, button_width, button_width);
  menu_button->setFlat(true);
  menu_button->setGeometry(menu_button_rect);
  menu_button->setContentsMargins(0, 0, 0, 0);
  menu_button->setMinimumWidth(button_width);
  menu_button->setMinimumHeight(button_width);
  menu_button->setMaximumHeight(button_width);
  menu_button->setMaximumWidth(button_width);
  menu_button->setStyleSheet(QString(c_image_button_style_template_str)
                                 .arg(c_menu_button_image_prefix_str));

  connect(menu_button, &QPushButton::clicked, this,
          &FiltersWidget::OnMenuButtonClicked);
}

void FiltersWidget::OnMenuButtonClicked() {
  if (!menu_) {
    QSettings settings;
    const QString last_file = settings.value(c_last_opend_file_str).toString();
    menu_ = new MenuDialog(MenuDialog::Parameters{this, last_file});
    connect(*menu_, &MenuDialog::SignalOpenImage, this,
            &FiltersWidget::OnSignalOpenImage);
    connect(*menu_, &MenuDialog::SignalSaveImage, this,
            &FiltersWidget::OnSignalSaveImage);
    connect(*menu_, &MenuDialog::SignalUploadImage, this,
            &FiltersWidget::OnSignalUploadImage);
  }
  (*menu_)->setVisible(true);
}

void FiltersWidget::CreateCleanButton() {
  // create clean button
  QPushButton *button = new ImageButton("", this);
  const QRect button_rect = QRect(0, 0, c_button_width, c_button_width);
  button->setGeometry(button_rect);
  button->setFlat(true);
  button->setContentsMargins(0, 0, 0, 0);
  button->setMinimumWidth(c_button_width);
  button->setMinimumHeight(c_button_width);
  button->setMaximumHeight(c_button_width);
  button->setMaximumWidth(c_button_width);
  button->setStyleSheet(QString(c_image_button_style_template_str)
                            .arg(c_undo_button_image_prefix_str));

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
  const int button_width = c_button_width;

  // buttons widget
  QWidget *filter_buttons_widget = new QWidget(this);
  filter_buttons_widget->setContentsMargins(0, 0, 0, 0);
  filter_buttons_widget->setGeometry(QRect(0,
                                           parent_rect.height() - button_width,
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
      QRect button_rect = QRect(0, 0, button_width, button_width);
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

  QSettings settings;
  settings.setValue(c_last_opend_file_str, path);

  image_ = std::make_shared<QImage>();

  QImageReader reader(path);
  reader.setAutoTransform(true);

  if (reader.read(image_.get())) {
    editable_image_->SetOriginalImage(QtImageToIImage(*image_));
    update();
  } else {
    spdlog::error("Fail to open image {0}", path.toStdString());
  }
  emit SignalEnableFilterButtons(image_ && !(image_->isNull()));
  emit SignalEnableCleanButton(false);
}

void FiltersWidget::OnSignalSaveImage(const QString path) {
  UNI_ENSURE_RETURN(image_);
  // QDir picDir =
  // QDir(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
  // QString filePath = picDir.filePath("test123.jpg");

  if (image_->save(path)) {
    spdlog::info("Image was saved {0}", path.toStdString());
  } else {
    spdlog::error("Fail to save image {0}", path.toStdString());
  }
  /*   QAndroidJniObject::callStaticMethod<void>("aha/androscanner/AndroScannerInJava",
                                                "scanForPicture",
                                                "(Ljava/lang/String;)V",
                                                QAndroidJniObject::fromString(filePath).object<jstring>());*/
}

void FiltersWidget::OnSignalUploadImage() {
  QUrl url = QUrl("http://localhost:8081/");

  QNetworkAccessManager *mgr = new QNetworkAccessManager(this);

  // connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinish(QNetworkReply*)));
  // connect(mgr,SIGNAL(finished(QNetworkReply*)),mgr,SLOT(deleteLater()));

  QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);

  QHttpPart receipt_part;
  receipt_part.setHeader(QNetworkRequest::ContentTypeHeader,
                         QVariant("image/jpeg"));
  receipt_part.setHeader(
      QNetworkRequest::ContentDispositionHeader,
      QVariant("multipart/form-data; name=\"image\"; filename=\"1.jpg\""));
  receipt_part.setRawHeader("Content-Transfer-Encoding", "binary");
  QByteArray byte_arr;
  QBuffer buffer(&byte_arr);
  buffer.open(QIODevice::WriteOnly);
  image_->save(&buffer, "JPG");
  receipt_part.setBody(byte_arr);

  multi_part->append(receipt_part);

  mgr->post(QNetworkRequest(url), multi_part);
}

void FiltersWidget::OnSignalCommandAppyed() { UpdateImage(); }

void FiltersWidget::UpdateImage() {
  UNI_ENSURE_RETURN(editable_image_ && editable_image_->Image());

  image_ = std::make_shared<QImage>(IImageToQtImage(editable_image_->Image()));

  emit SignalEnableCleanButton(true);

  update();
}

void FiltersWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QRect dirty_rect = event->rect();
  QImage scaled_background_image = background_image_.scaledToWidth(
      dirty_rect.width(), Qt::SmoothTransformation);
  painter.drawImage(0, dirty_rect.height() - scaled_background_image.height(),
                    scaled_background_image);

  if (image_) {
    const auto new_image_height =
        geometry().size().height() - c_widget_image_top_margin;
    QImage image =
        image_->scaledToHeight(new_image_height, Qt::SmoothTransformation);

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

void FiltersWidget::onShow(const bool visible) {
  QSettings settings;
  const QString last_file = settings.value(c_last_opend_file_str).toString();
  if (!last_file.isEmpty()) {
    OnSignalOpenImage(last_file);
  }

  setEnabled(visible);
}
} // namespace ImageEditor::UI

namespace ImageEditor::UI {
UICommand::UICommand(QObject *parent, Modules::IControlPtr control)
    : QObject(parent), control_(control) {
  UNI_ENSURE_RETURN(control_);
}

void UICommand::OnButtonClicked() {
  UNI_ENSURE_RETURN(control_);
  control_->Activate(control_->Parameters());
  emit SignalCommandAppyed();
}

void RadioButton::UncheckAll(QWidget *parent,
                             const QString &button_group_name) {
  UNI_ENSURE_RETURN(parent);

  QList<QPushButton *> buttons =
      parent->findChildren<QPushButton *>(button_group_name);
  for (auto &button : buttons) {
    if (button->isChecked()) {
      button->setChecked(false);
      button->update();
      button->parentWidget()->update();
    }
  }
}

RadioButton::RadioButton(const QString &text, const QString &button_group_name,
                         QWidget *parent)
    : ImageButton(text, parent) {
  setObjectName(button_group_name);
  setCheckable(true);
  connect(this, &QPushButton::clicked, this, &RadioButton::OnButtonClicked);
}

void RadioButton::OnButtonClicked(const bool checked) {
  if (checked) {
    QList<QPushButton *> buttons =
        parentWidget()->findChildren<QPushButton *>(objectName());
    for (auto &button : buttons) {
      if (button != this && button->isChecked()) {
        button->setChecked(false);
      }
    }
  } else {
    QPushButton::setChecked(true);
  }
  update();
  parentWidget()->update();
}

ImageButton::ImageButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent) {
  UNI_ASSERT(parent);
}

void ImageButton::OnSignalEnable(const bool enable) { setEnabled(enable); }

void ImageButton::keyPressEvent(QKeyEvent *e) {
  UNI_ENSURE_RETURN(parentWidget());
  update();
  parentWidget()->update();
  QPushButton::keyPressEvent(e);
}

void ImageButton::focusInEvent(QFocusEvent *e) {
  UNI_ENSURE_RETURN(parentWidget());
  update();
  parentWidget()->update();
  QPushButton::focusInEvent(e);
}

void ImageButton::focusOutEvent(QFocusEvent *e) {
  UNI_ENSURE_RETURN(parentWidget());
  update();
  parentWidget()->update();
  QPushButton::focusOutEvent(e);
}

void ImageButton::mousePressEvent(QMouseEvent *e) {
  UNI_ENSURE_RETURN(parentWidget());
  update();
  parentWidget()->update();
  QPushButton::mousePressEvent(e);
}

void ImageButton::mouseReleaseEvent(QMouseEvent *e) {
  UNI_ENSURE_RETURN(parentWidget());
  update();
  parentWidget()->update();
  QPushButton::mouseReleaseEvent(e);
}

void ImageButton::mouseMoveEvent(QMouseEvent *e) {
  UNI_ENSURE_RETURN(parentWidget());
  update();
  parentWidget()->update();
  QPushButton::mouseMoveEvent(e);
}

void ImageButton::leaveEvent(QEvent *e) {
  UNI_ENSURE_RETURN(parentWidget());
  update();
  parentWidget()->update();
  QWidget::leaveEvent(e);
}
} // namespace ImageEditor::UI
