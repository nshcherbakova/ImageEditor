#include "RadioButton.h"
#include <stdafx.h>

namespace ImageEditor::UI {

RadioButton::RadioButton(const QString &text, const QString &button_group_name,
                         QWidget *parent)
    : ImageButton(text, parent) {
  setObjectName(button_group_name);
  setCheckable(true);
  connect(this, &QPushButton::clicked, this, &RadioButton::OnButtonClicked);
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

} // namespace ImageEditor::UI
