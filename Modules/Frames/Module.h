#pragma once
#ifndef IMAGEEDITOR_MODULES_FRAMES_MODULE_H
#define IMAGEEDITOR_MODULES_FRAMES_MODULE_H
#include <Core/Gears/Injector.h>
#include <Modules/Frames/FiltersFrame.h>
#include <Core/types.h>
#include <Modules/types.h>

namespace ImageEditor::Modules
{
    inline auto InitFramesModule(IEditableImagePtr image, Core::IFilterPtrArr filters)
    {
        auto injector = boost::di::make_injector(
            boost::di::bind<IFrame>().to<FiltersFrame>().in(boost::di::singleton),
            boost::di::bind<FiltersFrame::Parameters>.to(FiltersFrame::Parameters({ image, std::move(filters) }))
        );

        return injector;
    }
}
#endif //IMAGEEDITOR_MODULES_FRAMES_MODULE_H