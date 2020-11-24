#pragma once
#ifndef IMAGEEDITOR_CORE_IMAGE_MODULE_H
#define IMAGEEDITOR_CORE_IMAGE_MODULE_H
#include <Core/Gears/Module.h>
#include <Core/Image/Image.h>

namespace ImageEditor::Core::Image
{
    auto InitModule()
    {
        auto injector = boost::ext::di::make_injector(
            boost::ext::di::bind<IImage, Image>.in(boost::ext::di::shared)
        );
        return injector;
    }
}
#endif //IMAGEEDITOR_CORE_IMAGE_MODULE_H