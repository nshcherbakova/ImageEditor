#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_MODULE_H
#define IMAGEEDITOR_UI_WIDGETS_MODULE_H
#include <Core/Gears/Injector.h>
#include <UI/Widgets/FiltersWidget.h>
#include <UI/types.h>

namespace ImageEditor::UI
{
    inline auto InitWidgetsModule(QWidget& parent, Modules::IFramePtr frame)
    {
        auto injector = boost::di::make_injector(
            boost::di::bind<IWidget>().to<FiltersWidget>().in(boost::di::unique),
            boost::di::bind<QWidget>.to(parent),
            boost::di::bind<ImageEditor::Modules::IFrame>.to(frame)
        );
        return injector;
    }
}
#endif //IMAGEEDITOR_UI_WIDGETS_MODULE_H