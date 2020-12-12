#include "MainWindow.h"
#include <stdafx.h>

namespace ImageEditor::UI
{
    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent)
    {
        ui.setupUi(this);
        delete ui.mainToolBar;
       
        setMaximumSize(size());
        setMinimumSize(size());
        setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
        setFixedSize(size());
        setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    }
}
