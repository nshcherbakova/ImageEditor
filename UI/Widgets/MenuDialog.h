#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_MENUDIALOG_H
#define IMAGEEDITOR_UI_WIDGETS_MENUDIALOG_H

#include <Modules/types.h>
#include <QString>
#include <QWidget>
#include <UI/Widgets/IWidget.h>
#include <UI/types.h>

class QPushButton;
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

protected:
  void mouseReleaseEvent(QMouseEvent *event);

private slots:
  void OnButtonOpenClicked();
  void OnButtonSaveClicked();
  void OnButtonUploadClicked();
  void OnButtonCancelClicked();

private:
  void CreateMenuButtons();
  QPushButton *CreateButton(const QString name, const int button_width);

private:
  QString image_file_name_;
  QPushButton *save_button_ = nullptr;
};
} // namespace ImageEditor::UI
#endif // IMAGEEDITOR_UI_WIDGETS_MENUDIALOG_H
