#pragma once
#ifndef IMAGEEDITOR_CORE_IMAGE_MODULE_H
#define IMAGEEDITOR_CORE_IMAGE_MODULE_H
#include <Core/Gears/Injector.h>
#include <Core/Image/Image.h>

namespace ImageEditor::Core
{
    inline auto InitImageModule(std::vector<uchar> data, unsigned int width, unsigned int height, unsigned int bytes_per_line, unsigned int format)
    {
        auto injector = boost::di::make_injector(
            boost::di::bind<IImage>().to<Image>().in(boost::di::unique),
            boost::di::bind<Image::Parameters>().to(Image::Parameters({std::move(data), width, height, bytes_per_line, format}))
        );

        return injector;
    }
}
#endif //IMAGEEDITOR_CORE_IMAGE_MODULE_H