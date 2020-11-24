#pragma once
#ifndef IMAGEEDITOR_FRAMES_FILTERSFRAME_MODULE_H
#define IMAGEEDITOR_FRAMES_FILTERSFRAME_MODULE_H
#include <Core/Gears/Module.h>
#include <Core/Image/IImage.h>
#include <Modules/FiltersFrame/FiltersFrame.h>

namespace ImageEditor::Modules::FiltersFrame
{
    auto InitModule(Core::Image::IImagePtr image)
    {
        auto injector = boost::ext::di::make_injector(
            boost::ext::di::bind<Modules::IFrame, FiltersFrame>.in(boost::ext::di::shared),
            boost::ext::di::bind<Core::Image::IImagePtr>.to(image)
        );
        return injector;
    }
}
#endif //IMAGEEDITOR_FRAMES_FILTERSFRAME_MODULE_H