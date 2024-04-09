#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_CONTROLS_RADIOBUTTON_H
#define IMAGEEDITOR_UI_WIDGETS_CONTROLS_RADIOBUTTON_H

#include <UI/Widgets/Controls/ImageButton.h>

class QWidget;
class QString;

namespace ImageEditor::UI {

class RadioButton final : public ImageButton {
  Q_OBJECT
public:
  RadioButton(const QString &text, const QString &button_group_name,
              QWidget *parent = nullptr);

public:
  static void UncheckAll(QWidget *parent, const QString &button_group_name);

protected slots:
  void OnButtonClicked(const bool checked);
};

} // namespace ImageEditor::UI
#endif // IMAGEEDITOR_UI_WIDGETS_CONTROLS_RADIOBUTTON_H
