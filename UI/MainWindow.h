#pragma once
#ifndef IMAGEEDITOR_UI_MAINWINDOW_H
#define IMAGEEDITOR_UI_MAINWINDOW_H

#include <QOpenGLWidget>
#include <UI/Widgets/IWidget.h>
#include "ui_ImageEditor.h"

namespace ImageEditor::UI
{
    class MainWindow : public QOpenGLWidget
    {
        Q_OBJECT

    public:

        explicit MainWindow();
        MainWindow& operator= (const MainWindow&) = delete;
    };
}
#endif // IMAGEEDITOR_UI_MAINWINDOW_H
