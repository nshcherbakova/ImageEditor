#pragma once
#ifndef IMAGEEDITOR_UI_WIDGETS_MODULE_H
#define IMAGEEDITOR_UI_WIDGETS_MODULE_H
#include <Core/Gears/Injector.h>
#include <Modules/types.h>
#include <UI/Widgets/FiltersWidget.h>
#include <UI/types.h>

namespace ImageEditor::UI
{
    inline auto InitWidgetsModule(QWidget& parent, Modules::IFramePtr frame, Modules::IEditableImagePtr image)
    {
        auto injector = boost::di::make_injector(
            boost::di::bind<IWidget>().to<FiltersWidget>().in(boost::di::unique),
            boost::di::bind<FiltersWidget::Parameters>.to(FiltersWidget::Parameters({ parent, frame, image }))
        );

        return injector;
    }
}
#endif //IMAGEEDITOR_UI_WIDGETS_MODULE_H