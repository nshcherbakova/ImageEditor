#pragma once
#ifndef IMAGEEDITOR_MODULES_FRAMES_MODULE_H
#define IMAGEEDITOR_MODULES_FRAMES_MODULE_H
#include <Modules/types.h>

namespace ImageEditor::Modules
{
    IFrameInjector InitFramesModule(IEditableImagePtr image, Core::IFilterPtrArr filters);
}
#endif //IMAGEEDITOR_MODULES_FRAMES_MODULE_H