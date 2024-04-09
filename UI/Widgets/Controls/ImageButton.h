#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_CONTROLS_IMAGEBUTTON_H
#define IMAGEEDITOR_UI_WIDGETS_CONTROLS_IMAGEBUTTON_H

#include <QPushButton>

namespace ImageEditor::UI {

class ImageButton : public QPushButton {
  Q_OBJECT
public:
  ImageButton(const QString &text, QWidget *parent = nullptr);

public slots:
  void OnSignalEnable(const bool enable);

protected:
  virtual void keyPressEvent(QKeyEvent *) override final;
  virtual void focusInEvent(QFocusEvent *) override final;
  virtual void focusOutEvent(QFocusEvent *) override final;
  virtual void mouseMoveEvent(QMouseEvent *e) override final;
  virtual void mousePressEvent(QMouseEvent *e) override final;
  virtual void mouseReleaseEvent(QMouseEvent *e) override final;
  virtual void leaveEvent(QEvent *e) override final;
};

} // namespace ImageEditor::UI
#endif // IMAGEEDITOR_UI_WIDGETS_CONTROLS_IMAGEBUTTON_H
