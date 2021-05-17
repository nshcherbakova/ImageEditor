#include <stdafx.h>
#include <Core/Filters/SmoothFilter.h>
#include <Core/Filters/GrayFilter.h>
#include <Core/Filters/TessFilter.h>
#include <Core/Filters/WatercolorFilter.h>
#include <Core/Filters/SepiaFilter.h>
#include <Core/Filters/OpenGL/OpenGLGrayFilter.h>
#include <Core/Filters/OpenGL/OpenGLBlurFilter.h>
#include "FiltersModule.h"

namespace 
{
    using namespace ImageEditor;
    using namespace ImageEditor::Core;
    IFilterInjector module() noexcept {
        return boost::di::make_injector(
            boost::di::bind<IFilter* []>().to<GrayFilter, SepiaFilter, TessFilter, WatercolorFilter, SmoothFilter>(),
            boost::di::bind<IFilter>().to<GrayFilter>(),
            boost::di::bind<IFilter>().named<class SmoothFilter>().to<SmoothFilter>(),
            boost::di::bind<IFilter>().named<class TessFilter>().to<TessFilter>(),
            boost::di::bind<IFilter>().named<class WatercolorFilter>().to<WatercolorFilter>(),
            boost::di::bind<IFilter>().named<class SepiaFilter>().to<SepiaFilter>()
        );
    }

    IFilterInjector OpenGLmodule() noexcept {
        return boost::di::make_injector(
            boost::di::bind<IFilter* []>().to<OpenGLGrayFilter, OpenGLBlurFilter, SepiaFilter, SmoothFilter>(),/* OpenGL::TessFilter, OpenGL::WatercolorFilter, OpenGL::SmoothFilter>(),*/
            boost::di::bind<IFilter>().to<OpenGLGrayFilter>(),
            boost::di::bind<IFilter>().named<class OpenGLBlurFilter>().to<OpenGLBlurFilter>(),
            /*boost::di::bind<IFilter>().named<class OpenGL::TessFilter>().to<OpenGL::TessFilter>(),
            boost::di::bind<IFilter>().named<class OpenGL::WatercolorFilter>().to<OpenGL::WatercolorFilter>(),*/
            boost::di::bind<IFilter>().named<class SepiaFilter>().to<SepiaFilter>(),
            boost::di::bind<IFilter>().named<class SmoothFilter>().to<SmoothFilter>()
        );
    }
}

namespace ImageEditor::Core
{ 
    IFilterInjector InitFiltersModule()
    {
        return boost::di::make_injector(OpenGLmodule());
    }
}
