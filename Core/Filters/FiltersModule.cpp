#include <stdafx.h>
#include "SmoothFilter.h"
#include "GrayFilter.h"
#include "TessFilter.h"
#include "WatercolorFilter.h"
#include "SepiaFilter.h"
#include "OpenGL/OpenGLDropsFilter.h"
#include "OpenGL/OpenGLGrayFilter.h"
#include "OpenGL/OpenGLTessFilter.h"
#include "OpenGL/OpenGLWatercolorFilter.h"
#include "OpenGL/OpenGLSepiaFilter.h"
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
            boost::di::bind<IFilter* []>().to<OpenGLSepiaFilter,OpenGLDropsFilter, OpenGLWaterColorFilter, OpenGLTessFilter>(),
            boost::di::bind<IFilter>().to<OpenGLSepiaFilter>(),
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
