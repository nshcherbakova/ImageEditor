#pragma once
#ifndef IMAGEEDITOR_CORE_IMAGE_MODULE_H
#define IMAGEEDITOR_CORE_IMAGE_MODULE_H
#include <Core/types.h>

namespace ImageEditor::Core
{
    IImageinjector InitImageModule(std::vector<uchar> data, unsigned int width, unsigned int height, unsigned int bytes_per_line, unsigned int format);
}
#endif //IMAGEEDITOR_CORE_IMAGE_MODULE_H