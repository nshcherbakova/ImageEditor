#include <stdafx.h>
#include "WidgetsModule.h"

namespace 
{
    using namespace ImageEditor;
    using namespace ImageEditor::UI;
    IWidgetInjector module(QWidget& parent, 
        Modules::IFramePtr frame, 
        Modules::IEditableImagePtr image
        ) noexcept {
        return boost::di::make_injector(
            boost::di::bind<IWidget>().to<FiltersWidget>().in(boost::di::unique),
            boost::di::bind<FiltersWidget::Parameters>.
            to(FiltersWidget::Parameters({ parent, std::move(frame), std::move(image) }))
        );
    }
}

namespace ImageEditor::UI
{ 
    IWidgetInjector InitWidgetsModule(QWidget& parent, 
        Modules::IFramePtr frame, 
        Modules::IEditableImagePtr image)
    {
        return boost::di::make_injector(module(parent,
            std::move(frame), std::move(image)));
    }
}
