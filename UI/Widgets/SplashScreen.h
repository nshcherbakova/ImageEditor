#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_SPLASHSCREEN_H
#define IMAGEEDITOR_UI_WIDGETS_SPLASHSCREEN_H

#include <QSplashScreen>
#include <QString>

namespace ImageEditor::UI {

class SplashScreen final : public QSplashScreen {
public:
  struct Parameters {
    QString image_file_name;
  };

  explicit SplashScreen(Parameters parameters);
  SplashScreen &operator=(const SplashScreen &) = delete;
};
} // namespace ImageEditor::UI
#endif // IMAGEEDITOR_UI_WIDGETS_SPLASHSCREEN_H
