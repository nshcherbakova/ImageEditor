#pragma once
#ifndef IMAGEEDITOR_UI_IMAGEEDITOR_H
#define IMAGEEDITOR_UI_IMAGEEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_ImageEditor.h"

class UIImageEditor : public QMainWindow
{
    Q_OBJECT

public:
    UIImageEditor(QWidget *parent = Q_NULLPTR);

private:
    Ui::ImageEditorClass ui;
};

#endif // IMAGEEDITOR_UI_IMAGEEDITOR_H