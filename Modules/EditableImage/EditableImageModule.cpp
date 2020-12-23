#include <stdafx.h>
#include <Modules/EditableImage/EditableImage.h>
#include "EditableImageModule.h"

namespace 
{
    using namespace ImageEditor;
    using namespace ImageEditor::Modules;
    IEditableImageInjector module() noexcept {
        return boost::di::make_injector(
            boost::di::bind<IEditableImage>().to<EditableImage>().in(boost::di::singleton)
        );
    }
}

namespace ImageEditor::Modules
{ 
    IEditableImageInjector InitEditableImageModule()
    {
        return boost::di::make_injector(module());
    }
}
