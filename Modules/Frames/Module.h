#pragma once
#ifndef IMAGEEDITOR_MODULES_FRAMES_MODULE_H
#define IMAGEEDITOR_MODULES_FRAMES_MODULE_H
#include <Core/Gears/Injector.h>
#include <Core/Filters/IFiltersContainer.h>
#include <Modules/Frames/FiltersFrame.h>
#include <Modules/EditableImage/IEditableImage.h>

namespace ImageEditor::Modules
{
    inline auto InitFramesModule(IEditableImagePtr image, Core::IFiltersContainerPtr filters)
    {
        auto injector = boost::di::make_injector(
            boost::di::bind<Modules::IFrame>().to<Modules::FiltersFrame>().in(boost::di::singleton),
            boost::di::bind<IEditableImage>.to(image),
            boost::di::bind<Core::IFiltersContainer>.to(filters)
        );
        return injector;
    }
}
#endif //IMAGEEDITOR_MODULES_FRAMES_MODULE_H