#include "FiltersScrollWidget.h"
#include "Controls/RadioButton.h"
#include "UICommand.h"
#include <stdafx.h>

static const char *c_filter_button_style_template_str =
    "QPushButton{"
    "background-color: rgba(255, 255, 255, 200);"
    "color: %1; "
    "font-size: 23px; "
    "font-family: Typo Round Regular Demo;"
    "border-style: solid;"
    "border-radius: 36;"
    "border-color: rgba(190, 190, 190, 255);"
    "border-width: 4;"
    "}"

    "QPushButton:disabled{color: rgb(190, 190, 190);}"
    "QPushButton:hover{border-color: rgba(170, 170, 170, 255);}"
    "QPushButton:checked{background-color: rgba(246, 228, 215, 220);}"
    "QPushButton:checked:pressed {border-color: rgba(170, 170, 170, 255);}"
    "QPushButton:pressed{background-color: rgba(239, 232, 225, 220);}";

static const char *c_filter_buttons_text_color_str_arr[] = {
    "rgb(95, 120, 180)", // first button color
    "#D1854F",           // second button color
    "#6F9B00",           // third button color
    "#308BB2",           // fourth button color
    "#8E2DB7"            // fifth button color
};

static const char *c_filter_widget_style_str = "QWidget{"
                                               "background: transparent;"
                                               "border: none;"
                                               "}";

static const char *c_scroll_style_str = "QScrollArea{"
                                        "background: transparent;"
                                        "border: none;"
                                        "}";

namespace ImageEditor::UI {
FiltersScrollWidget::FiltersScrollWidget(QWidget *parent,
                                         Modules::IControlsMapPtr controls)
    : QScrollArea(parent) {

  setStyleSheet(c_scroll_style_str);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setContentsMargins(0, 0, 0, 0);

  QScrollerProperties properties =
      QScroller::scroller(this)->scrollerProperties();
  properties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy,
                             QScrollerProperties::OvershootAlwaysOff);
  properties.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy,
                             QScrollerProperties::OvershootAlwaysOff);
  properties.setScrollMetric(QScrollerProperties::DragVelocitySmoothingFactor,
                             0.6);
  properties.setScrollMetric(QScrollerProperties::MinimumVelocity, 0.0);
  properties.setScrollMetric(QScrollerProperties::MaximumVelocity, 0.5);
  properties.setScrollMetric(QScrollerProperties::AcceleratingFlickMaximumTime,
                             0.4);
  properties.setScrollMetric(
      QScrollerProperties::AcceleratingFlickSpeedupFactor, 1.2);
  properties.setScrollMetric(QScrollerProperties::SnapPositionRatio, 0.2);
  properties.setScrollMetric(QScrollerProperties::MaximumClickThroughVelocity,
                             0);
  properties.setScrollMetric(QScrollerProperties::DragStartDistance, 0.001);
  properties.setScrollMetric(QScrollerProperties::MousePressEventDelay, 0.5);

  QScroller::scroller(this)->setScrollerProperties(properties);

  QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);

  CreateFilterButtons(std::move(controls));

  spdlog::info("FiltersScrollWidget UI created");
}

void FiltersScrollWidget::CreateFilterButtons(
    Modules::IControlsMapPtr controls) {
  UNI_ENSURE_RETURN(controls);

  const int button_width = c_filter_button_width;

  // buttons widget
  QWidget *filter_buttons_widget = new QWidget();
  filter_buttons_widget->setContentsMargins(0, 0, 0, 0);
  filter_buttons_widget->setStyleSheet(c_filter_widget_style_str);

  // buttons layput
  auto filter_buttons_layout = new QHBoxLayout(filter_buttons_widget);
  filter_buttons_layout->setContentsMargins(0, 0, 0, 0);
  filter_buttons_layout->setSpacing(5);
  // filter_buttons_widget->setLayout(filter_buttons_layout);

  // bind button with controls, add to layout
  int num = 0;
  auto buttons_it = controls->find(Modules::FILTER_BUTTON_TAG);
  if (buttons_it != controls->end()) {
    while (buttons_it != controls->end() &&
           buttons_it->first == Modules::FILTER_BUTTON_TAG) {
      auto control = buttons_it->second;
      UNI_ENSURE_RETURN(control);

      // create buttons
      const auto button =
          new RadioButton(UIString(control->Parameters()),
                          Modules::FILTER_BUTTON_TAG, filter_buttons_widget);
      QRect button_rect = QRect(0, 0, button_width - 10, button_width);
      button->setGeometry(button_rect);
      button->setMinimumWidth(button_width);
      button->setMinimumHeight(button_width);
      button->setMaximumHeight(button_width);
      button->setMaximumWidth(button_width);
      button->setFlat(true);

      const int index = num % std::size(c_filter_buttons_text_color_str_arr);
      QString style_template(c_filter_button_style_template_str);
      QString style_with_args =
          style_template.arg(c_filter_buttons_text_color_str_arr[index]);
      // .arg(c_round_button_str);
      button->setStyleSheet(style_with_args);

      // bind button with control
      const auto ui_command = new UICommand(this, control);
      connect(button, &QPushButton::clicked, ui_command,
              &UICommand::OnButtonClicked);
      connect(ui_command, &UICommand::SignalCommandAppyed, this,
              &FiltersScrollWidget::SignalCommandAppyed);

      //  connect(this, &FiltersWidget::SignalImageOpened, button,
      //        &ImageButton::OnSignalEnable);

      // add button to layout
      filter_buttons_layout->addWidget(button);

      buttons_it++;
      num++;
    }
  }
  setWidget(filter_buttons_widget);
}

} // namespace ImageEditor::UI
