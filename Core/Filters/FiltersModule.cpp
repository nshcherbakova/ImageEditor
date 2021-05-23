#include <stdafx.h>
#include <Core/Filters/SmoothFilter.h>
#include <Core/Filters/GrayFilter.h>
#include <Core/Filters/TessFilter.h>
#include <Core/Filters/WatercolorFilter.h>
#include <Core/Filters/SepiaFilter.h>
#include <Core/Filters/OpenGL/OpenGLGrayFilter.h>
#include <Core/Filters/OpenGL/OpenGLBlurFilter.h>
#include <Core/Filters/OpenGL/OpenGLDropsFilter.h>
#include <Core/Filters/OpenGL/OpenGLTessFilter.h>
#include <Core/Filters/OpenGL/OpenGLWatercolorFilter.h>
#include <Core/Filters/OpenGL/OpenGLSepiaFilter.h>
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
            boost::di::bind<IFilter* []>().to<OpenGLBlurFilter,OpenGLDropsFilter, OpenGLWaterColorFilter, OpenGLTessFilter>(),
            boost::di::bind<IFilter>().to<OpenGLBlurFilter>(),
            boost::di::bind<IFilter>().named<class OpenGLWaterColorFilter>().to<OpenGLWaterColorFilter>(),
            boost::di::bind<IFilter>().named<class OpenGLTessFilter>().to<OpenGLTessFilter>(),
            boost::di::bind<IFilter>().named<class OpenGLDropsFilter>().to<OpenGLDropsFilter>()
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
