#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_MENUDIALOG_H
#define IMAGEEDITOR_UI_WIDGETS_MENUDIALOG_H

#include <Modules/types.h>
#include <UI/types.h>
#include <UI/Widgets/IWidget.h>

namespace ImageEditor::UI
{
    class UICommand;

    class MenuDialog final: public QWidget, public IWidget
    {
        Q_OBJECT
    public:
        struct Parameters
        {
           
        };

        MenuDialog(Parameters parameters);
        MenuDialog& operator= (const MenuDialog&) = delete;

    public: // IWidget
       // virtual void onShow(const bool visible) override final;

    public slots: 
       

    private: // QWidget

    private:
    

    private:
       
    };
}
#endif // IMAGEEDITOR_UI_WIDGETS_MENUDIALOG_H