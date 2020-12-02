#pragma once
#ifndef IMAGEEDITOR_CORE_IMAGE_MODULE_H
#define IMAGEEDITOR_CORE_IMAGE_MODULE_H
#include <Core/Gears/Injector.h>
#include <Core/Image/Image.h>

namespace ImageEditor::Core
{
    inline auto InitModule()
    {
        auto injector = boost::di::make_injector(
            boost::di::bind<IImage>().to<Image>().in(boost::di::singleton)
        );
        return injector;
    }
}
#endif //IMAGEEDITOR_CORE_IMAGE_MODULE_H