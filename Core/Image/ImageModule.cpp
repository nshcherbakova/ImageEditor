#include <stdafx.h>
#include <Core/Image/Image.h>
#include "ImageModule.h"

namespace 
{
    using namespace ImageEditor;
    using namespace ImageEditor::Core;
    IImageinjector module(ByteArr data, unsigned int width, unsigned int height, unsigned int bytes_per_line, unsigned int format) noexcept {
        return boost::di::make_injector(
            boost::di::bind<IImage>().to<Image>().in(boost::di::unique),
            boost::di::bind<Image::Parameters>().to(Image::Parameters({ std::move(data), width, height, bytes_per_line, format }))
        );
    }
}

namespace ImageEditor::Core
{ 
    IImageinjector InitImageModule(ByteArr data, unsigned int width, unsigned int height, unsigned int bytes_per_line, unsigned int format)
    {
        return boost::di::make_injector(module(std::move(data), width, height, bytes_per_line, format));
    }
}
