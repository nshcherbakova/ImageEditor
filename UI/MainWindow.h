#pragma once
#ifndef IMAGEEDITOR_UI_MAINWINDOW_H
#define IMAGEEDITOR_UI_MAINWINDOW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QOpenGLWidget>
#include <UI/Widgets/IWidget.h>
#include "ui_ImageEditor.h"

namespace ImageEditor::UI
{
    class MainWindow : public QOpenGLWidget
    {
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = Q_NULLPTR);

    private:
        //Ui::ImageEditorClass ui;
    };
}
#endif // IMAGEEDITOR_UI_MAINWINDOW_H