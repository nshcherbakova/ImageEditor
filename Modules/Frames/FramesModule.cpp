#pragma once
#include <stdafx.h>
#include <Core/types.h>
#include <Modules/Frames/FiltersFrame.h>
#include "FramesModule.h"

namespace 
{
    using namespace ImageEditor;
    using namespace ImageEditor::Modules;
    IFrameInjector module(IEditableImagePtr image, Core::IFilterPtrArr filters) noexcept {
        return boost::di::make_injector(
            boost::di::bind<IFrame>().to<FiltersFrame>().in(boost::di::singleton),
            boost::di::bind<FiltersFrame::Parameters>.to(FiltersFrame::Parameters({ image, std::move(filters) }))
        );
    }
}

namespace ImageEditor::Modules
{ 
    IFrameInjector InitFramesModule(IEditableImagePtr image, Core::IFilterPtrArr filters)
    {
        return boost::di::make_injector(module(image, std::move(filters)));
    }
}