#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H
#define IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H

#include <Modules/types.h>
#include <QPushButton>
#include <QWidget>
#include <UI/Widgets/IWidget.h>
#include <UI/types.h>

namespace ShareUtils {
class ShareUtilsCpp;
}

namespace ImageEditor::UI {
class UICommand;
class MenuDialog;
class Button;
class FiltersScrollWidget;

class FiltersWidget final : public QWidget, public IWidget {
  Q_OBJECT
public:
  struct Parameters {
    QWidget &parent;
    Modules::IFramePtr filters_frame;
    Modules::IEditableImagePtr image;
    Modules::INetworkPtr network;
  };

  explicit FiltersWidget(Parameters parameters);
  FiltersWidget &operator=(const FiltersWidget &) = delete;

public: // IWidget
  virtual void onShow(const bool visible) override final;

signals:
  void SignalImageOpened(const bool enable);
  void SignalEnableCleanButton(const bool enable);

public slots:
  void OnSignalOpenImage(const QString path);
  void OnSignalSaveImage(const QString path);
  void OnSignalUploadImage();
  void OnSignalShareImage();
  void OnMenuButtonClicked();
  void OnCleanButtonClicked();
  void OnSignalCommandAppyed();

private: // QWidget
  virtual void paintEvent(QPaintEvent *event) override final;

private:
  void CreateMenuButton();
  void CreateMenu();
  void CreateCleanButton();
  void CreateFilterButtons(Modules::IControlsMapPtr controls);
  void CreateOpenImageButton();
  void CreateShareButton();

  void UpdateImage();
  void DrawImage();

private:
  MenuDialog *menu_ = nullptr;
  QPushButton *open_image_button_ = nullptr;
  FiltersScrollWidget *filter_scroll_ = nullptr;

  Modules::IEditableImagePtr editable_image_;
  std::shared_ptr<QImage> image_;
  QImage background_image_;

  Modules::INetworkPtr network_;
  std::shared_ptr<ShareUtils::ShareUtilsCpp> share_utiles_;

  QPixmap image_to_draw_;
};

} // namespace ImageEditor::UI
#endif // IMAGEEDITOR_UI_WIDGETS_FILTERSWIDGET_H
