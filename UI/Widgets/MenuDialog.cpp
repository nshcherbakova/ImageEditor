#include "MenuDialog.h"
#include "Controls/ImageButton.h"
#include <stdafx.h>

static const char *c_open_str = "Open";
static const char *c_save_str = "Save";
static const char *c_upload_str = "Upload";
static const char *c_cancel_str = "Cancel";
static const char *c_open_image_str = "Open Image";
static const char *c_save_image_str = "Save Image";
static const char *c_file_types_str = "Image Files (*.png *.jpg *.jpeg *.bmp)";
static const char *c_last_opend_dir = "last_opened_dir";
static const char *c_button_style_str =
    "QPushButton{  background-color: rgba(253, 253, 255, 255);"
    "color: #308BB2; font-size: 44px; font-family: Typo Round Regular Demo;"
    "border-style: solid;"
    "border-radius: 30;"
    "border-color: rgba(190, 190, 190, 255);"
    "border-width: 5;"
    "}"
    "QPushButton:pressed{background-color: rgba(239, 232, 225, 225);}"
    "QPushButton:disabled{color: rgba(190, 190, 190, 225);}";

static const QColor c_background_color = QColor(250, 250, 247, 180);
static const int c_buttons_margin = 5;
static const int c_layout_margin_left = 50;
static const int c_layout_margin_top = 0;
static const int c_layout_margin_right = 50;
static const int c_layout_margin_bottom = 5;
static const int c_buttons_vmargin = 60;
static const QStringList c_mime_type_filters({"image/jpeg", "image/pjpeg",
                                              "image/png", "image/bmp"});

static const int c_about_margin_left = 20;
static const int c_about_margin_bottom = 105;
static const char *c_about_style_str =
    "QLabel{"
    "font-size: 20; font-family: Typo Round Regular Demo;"
    "}";
static const char *c_about_font_color_str = "#669692";
static const char *c_about_link_str =
    "\"https://github.com/nshcherbakova/ImageEditor\" ";
static const char *c_about_text_str = "About Image Editor";

namespace ImageEditor::UI {
MenuDialog::MenuDialog(const Parameters parameters)
    : QWidget(parameters.parent), image_file_name_(parameters.image_file_name) {
  UNI_ENSURE_RETURN(parameters.parent);

  setContentsMargins(0, 0, 0, 0);
  setGeometry(parameters.parent->geometry());

  setAutoFillBackground(true);
  auto palette = QWidget::palette();
  palette.setColor(QPalette::Window, c_background_color);
  setPalette(palette);

  CreateMenuButtons();
  CreateAbout();
}

void MenuDialog::CreateMenuButtons() {
  const QRect parent_rect = geometry();
  const int button_height = parent_rect.height() / 7;

  // buttons widget
  QWidget *buttons_widget = new QWidget(this);
  buttons_widget->setContentsMargins(0, 0, 0, c_buttons_margin);
  buttons_widget->setGeometry(QRect(
      0, (parent_rect.height() - button_height * 3) / 2 - c_buttons_vmargin,
      parent_rect.width(), button_height * 3 + c_buttons_vmargin));

  // buttons layput
  auto buttons_layout = new QVBoxLayout(buttons_widget);
  buttons_layout->setContentsMargins(c_layout_margin_left, c_layout_margin_top,
                                     c_layout_margin_right,
                                     c_layout_margin_bottom);

  buttons_widget->setLayout(buttons_layout);

  // create buttons
  QPushButton *open_button = CreateButton(UIString(c_open_str), button_height);
  connect(open_button, &QPushButton::clicked, this,
          &MenuDialog::OnButtonOpenClicked);
  open_button->setStyleSheet(c_button_style_str);
  open_button->setMaximumHeight(button_height);

  save_button_ = CreateButton(UIString(c_save_str), button_height);
  connect(save_button_, &QPushButton::clicked, this,
          &MenuDialog::OnButtonSaveClicked);
  save_button_->setEnabled(!image_file_name_.isEmpty());
  save_button_->setStyleSheet(c_button_style_str);
  save_button_->setMaximumHeight(button_height);

#ifndef IMAGE_EDITOR_NO_UPLPAD
  QPushButton *upload_button =
      CreateButton(UIString(c_upload_str), button_height);
  connect(upload_button, &QPushButton::clicked, this,
          &MenuDialog::OnButtonUploadClicked);
  upload_button->setStyleSheet(c_button_style_str);
  upload_button->setMaximumHeight(button_height);
#endif

  /* QPushButton* canel_button = CreateButton(UIString(c_cancel_str),
   button_height); connect(canel_button, &QPushButton::clicked, this,
   &MenuDialog::OnButtonCancelClicked);
   canel_button->setStyleSheet(c_button_style_str);
   canel_button->setMaximumHeight(button_height);*/

  buttons_layout->addWidget(open_button);
  buttons_layout->addWidget(save_button_);

#ifndef IMAGE_EDITOR_NO_UPLPAD
  buttons_layout->addWidget(upload_button);
#endif

  // filter_buttons_layout->addWidget(upload_button);
  // filter_buttons_layout->addWidget(canel_button);
}

QPushButton *MenuDialog::CreateButton(const QString name,
                                      const int button_height) {
  QPushButton *button = new ImageButton(name, this);
  const QRect menu_button_rect = QRect(0, 0, 0, button_height);
  button->setGeometry(menu_button_rect);
  button->setMinimumHeight(button_height);
  button->setContentsMargins(0, 0, 0, 0);

  return button;
}

void MenuDialog::CreateAbout() {
  const QRect parent_rect = geometry();

  about_ = new QLabel(this);
  about_->setStyleSheet(c_about_style_str);

  QString text("<a style=text-decoration:none style=color:%1 href=%2>%3</a>");
  text = text.arg(c_about_font_color_str, c_about_link_str, c_about_text_str);

  about_->setText(text);
  about_->setOpenExternalLinks(true);

  about_->adjustSize();

  QRect rect;
  rect.setHeight(about_->height());
  rect.setWidth(about_->width());
  rect.moveTopLeft(
      {c_about_margin_left,
       parent_rect.height() - about_->height() - c_about_margin_bottom});
  about_->setGeometry(rect);
}

void MenuDialog::OnButtonOpenClicked() {
  QString path = image_file_name_;
  if (path.isEmpty()) {
    const QSettings settings(QSettings::Scope::UserScope);
    path = settings.value(c_last_opend_dir).toString();
  }

  QFileDialog dialog(this, UIString(c_open_image_str), path,
                     UIString(c_file_types_str));

  dialog.setMimeTypeFilters(c_mime_type_filters);
  dialog.setFileMode(QFileDialog::ExistingFile);

  QStringList file_names;
  if (dialog.exec()) {
    file_names = dialog.selectedFiles();
  }

  if (!file_names.isEmpty()) {
    image_file_name_ = file_names.front();
    save_button_->setEnabled(!image_file_name_.isEmpty());
    emit SignalOpenImage(image_file_name_);
    setVisible(false);

    QSettings settings(QSettings::Scope::UserScope);
    settings.setValue(c_last_opend_dir,
                      QFileInfo(image_file_name_).dir().path());
  }
}

void MenuDialog::OnButtonSaveClicked() {
  const QSettings settings(QSettings::Scope::UserScope);
  auto path =
      QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);

  QString file =
      path + "/" + QString::number(QDateTime::currentSecsSinceEpoch()) + ".jpg";

  const QString file_name = QFileDialog::getSaveFileName(
      this, UIString(c_save_image_str), file, UIString(c_file_types_str), 0);

  if (!file_name.isEmpty()) {
    image_file_name_ = file_name;
    emit SignalSaveImage(file_name);
    setVisible(false);
  }
}

void MenuDialog::OnButtonUploadClicked() {
  emit SignalUploadImage();
  setVisible(false);
}

void MenuDialog::OnButtonCancelClicked() { setVisible(false); }

void MenuDialog::mouseReleaseEvent(QMouseEvent *event) {
  QWidget::mouseReleaseEvent(event);
  OnButtonCancelClicked();
}
} // namespace ImageEditor::UI
