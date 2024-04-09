#include "ImageButton.h"
#include <stdafx.h>

namespace ImageEditor::UI {

ImageButton::ImageButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent) {
  UNI_ASSERT(parent);
  setAttribute(Qt::WA_TranslucentBackground);
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
