#include "SplashScreen.h"
#include <stdafx.h>

namespace ImageEditor::UI {
SplashScreen::SplashScreen(const Parameters parameters) {
  QGridLayout *layout = new QGridLayout(this);
  QLabel *label = new QLabel;

  QPixmap pixmap(parameters.image_file_name);
  label->setPixmap(pixmap);
  layout->addWidget(label, 0, 0, Qt::AlignCenter);

  setAutoFillBackground(true);

  auto palette = QSplashScreen::palette();
  palette.setColor(QPalette::Window, Qt::white);
  QSplashScreen::setPalette(palette);
}
} // namespace ImageEditor::UI
