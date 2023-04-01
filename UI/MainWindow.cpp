#include "MainWindow.h"
#include <stdafx.h>

namespace ImageEditor::UI
{
    MainWindow::MainWindow()
    {   
#ifdef Q_OS_ANDROID
        setWindowState(Qt::WindowFullScreen);
        showMaximized();
        QSize window_size(size());
#elif WIN32
        QSize window_size(640, 900);
        //QSize window_size(640, 1136);
#elif defined Q_OS_MACOS
        QSize window_size(640, 900);
#elif defined Q_OS_IOS
        QSize window_size(400, 800);
#endif
        setMaximumSize(window_size);
        setMinimumSize(window_size);
        setFixedSize(window_size);
        setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    }
}
