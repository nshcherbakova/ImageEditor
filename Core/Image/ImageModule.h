#pragma once
#ifndef IMAGEEDITOR_CORE_IMAGE_MODULE_H
#define IMAGEEDITOR_CORE_IMAGE_MODULE_H
#include <Core/types.h>

namespace ImageEditor::Core
{
    IImageinjector ImageModule(ByteArr data, const uint64_t width, const uint64_t height, const uint64_t bytes_per_line, const unsigned int format);
}
#endif //IMAGEEDITOR_CORE_IMAGE_MODULE_H