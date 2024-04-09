#include "UICommand.h"
#include <stdafx.h>

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

} // namespace ImageEditor::UI
