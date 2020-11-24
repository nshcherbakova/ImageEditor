#pragma once
#ifndef IMAGEEDITOR_UI_FRAMES_MODULE_H
#define IMAGEEDITOR_UI_FRAMES_MODULE_H
#include <Core/Gears/Module.h>
#include <Core/Image/IImage.h>
#include <UI/Frames/FiltersFrame.h>
#include <Modules/IFrame.h>

namespace ImageEditor::UI::Frames
{
    auto InitModule(QWidget* parent, const Modules::IFramePtr& frame, const Core::Image::IImagePtr& image)
    {
        auto injector = boost::ext::di::make_injector(
            boost::ext::di::bind<IFrame, FiltersFrame>.in(boost::ext::di::shared),
            boost::ext::di::bind<QWidget>.to(parent),
            boost::ext::di::bind<Modules::IFramePtr>.to(frame),
            boost::ext::di::bind<Core::Image::IImagePtr>.to(image)
        );
        return injector;
    }
}
#endif //IMAGEEDITOR_UI_FRAMES_MODULE_H