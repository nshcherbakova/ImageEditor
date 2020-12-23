#include <stdafx.h>
#include <Core/Gears/Injector.h>
#include <UI/Widgets/FiltersWidget.h>
#include <UI/Widgets/IWidget.h>
#include "WidgetsModule.h"

namespace 
{
    using namespace ImageEditor;
    using namespace ImageEditor::UI;
    IWidgetInjector module(QWidget& parent, Modules::IFramePtr frame, Modules::IEditableImagePtr image) noexcept {
        return boost::di::make_injector(
            boost::di::bind<IWidget>().to<FiltersWidget>().in(boost::di::unique),
            boost::di::bind<FiltersWidget::Parameters>.to(FiltersWidget::Parameters({ parent, frame, image }))
        );
    }
}

namespace ImageEditor::UI
{ 
    IWidgetInjector InitWidgetsModule(QWidget& parent, Modules::IFramePtr frame, Modules::IEditableImagePtr image)
    {
        return boost::di::make_injector(module(parent, frame, image));
    }
}
