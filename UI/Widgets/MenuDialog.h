#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_MENUDIALOG_H
#define IMAGEEDITOR_UI_WIDGETS_MENUDIALOG_H

#include <Modules/types.h>
#include <QString>
#include <QWidget>
#include <UI/Widgets/IWidget.h>
#include <UI/types.h>

class QPushButton;
class QLabel;

namespace ImageEditor::UI {
class UICommand;

class MenuDialog final : public QWidget {
  Q_OBJECT
public:
  struct Parameters {
    QWidget *parent;
    QString image_file_name;
  };

  explicit MenuDialog(Parameters parameters);
  MenuDialog &operator=(const MenuDialog &) = delete;

signals:
  void SignalOpenImage(const QString file_name);
  void SignalSaveImage(const QString file_name);
  void SignalUploadImage();
  void SignalShareImage();

protected:
  void mouseReleaseEvent(QMouseEvent *event);

public slots:
  void OnButtonOpenClicked();

private slots:
  void OnButtonSaveClicked();
  void OnButtonUploadClicked();
  void OnButtonCancelClicked();

private:
  void CreateMenuButtons();
  void CreateAbout();
  QPushButton *CreateButton(const QString name, const int button_width);

private:
  QString image_file_name_;
  QPushButton *save_button_ = nullptr;
  QLabel *about_ = nullptr;
};
} // namespace ImageEditor::UI
#endif // IMAGEEDITOR_UI_WIDGETS_MENUDIALOG_H
