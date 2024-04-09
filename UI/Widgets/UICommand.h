#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_UICOMMAND_H
#define IMAGEEDITOR_UI_WIDGETS_UICOMMAND_H

#include <Modules/types.h>
#include <QObject>

namespace ImageEditor::UI {

class UICommand final : public QObject {
  Q_OBJECT
public:
  explicit UICommand(QObject *parent, Modules::IControlPtr control);
  UICommand &operator=(const UICommand &) = delete;

public slots:
  void OnButtonClicked();

signals:
  void SignalCommandAppyed();

private:
  const Modules::IControlPtr control_;
};

} // namespace ImageEditor::UI
#endif // IMAGEEDITOR_UI_WIDGETS_UICOMMAND_H
