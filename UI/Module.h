#pragma once
#ifndef IMAGEEDITOR_UI_FRAMETOUIBINDER_H
#define IMAGEEDITOR_UI_FRAMETOUIBINDER_H


namespace ImageEditor::UI
{
    class FrameToUIBinder : public QObject
    {
        Q_OBJECT

    public:
        FrameToUIBinder(QWidget* parent = Q_NULLPTR);

    private:
    };
}
#endif // IMAGEEDITOR_UI_FRAMETOUIBINDER_H