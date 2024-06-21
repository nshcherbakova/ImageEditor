#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_FILTERSSCROLLWIDGET_H
#define IMAGEEDITOR_UI_WIDGETS_FILTERSSCROLLWIDGET_H

#include <Modules/types.h>
#include <QScrollArea>

namespace ImageEditor::UI {
class UICommand;

class FiltersScrollWidget final : public QScrollArea {
  Q_OBJECT
public:
  static const int c_filter_button_width = 72;

  explicit FiltersScrollWidget(QWidget *parent,
                               Modules::IControlsMapPtr controls);
  FiltersScrollWidget &operator=(const FiltersScrollWidget &) = delete;

signals:
  void SignalCommandAppyed();

private:
  void CreateFilterButtons(Modules::IControlsMapPtr controls);

private:
};

} // namespace ImageEditor::UI
#endif // IMAGEEDITOR_UI_WIDGETS_FILTERSSCROLLWIDGET_H
