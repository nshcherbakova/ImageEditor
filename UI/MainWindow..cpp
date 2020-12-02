#include "MainWindow.h"
#include <stdafx.h>

namespace ImageEditor::UI
{
    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent)
    {
        ui.setupUi(this);
    }
}
