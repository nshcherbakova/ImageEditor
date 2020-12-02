#pragma once
#ifndef IMAGEEDITOR_MODILES_EDITABLEIMAGE_MODULE_H
#define IMAGEEDITOR_MODILES_EDITABLEIMAGE_MODULE_H
#include <Core/Gears/Injector.h>
#include <Modules/EditableImage/EditableImage.h>

namespace ImageEditor::Modules
{
    inline auto InitEditableImageModule()
    {
        auto injector = boost::di::make_injector(
            boost::di::bind<IEditableImage>().to<EditableImage>().in(boost::di::singleton)
        );
        return injector;
    }
}
#endif //IMAGEEDITOR_MODILES_EDITABLEIMAGE_MODULE_H