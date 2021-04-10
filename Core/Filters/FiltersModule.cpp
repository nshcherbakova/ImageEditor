#include <stdafx.h>
#include <Core/Filters/SmoothFilter.h>
#include <Core/Filters/GrayFilter.h>
#include <Core/Filters/TessFilter.h>
#include <Core/Filters/WatercolorFilter.h>
#include <Core/Filters/SepiaFilter.h>
#include "FiltersModule.h"

namespace 
{
    using namespace ImageEditor;
    using namespace ImageEditor::Core;
    IFilterInjector module() noexcept {
        return boost::di::make_injector(
            boost::di::bind<IFilter* []>().to</*GrayFilter,*/ SepiaFilter, TessFilter, WatercolorFilter, SmoothFilter>(),
            //boost::di::bind<IFilter>().to<GrayFilter>(),
            boost::di::bind<IFilter>().named<class SmoothFilter>().to<SmoothFilter>(),
            boost::di::bind<IFilter>().named<class TessFilter>().to<TessFilter>(),
            boost::di::bind<IFilter>().named<class WatercolorFilter>().to<WatercolorFilter>(),
            boost::di::bind<IFilter>().named<class SepiaFilter>().to<SepiaFilter>()
        );
    }
}

namespace ImageEditor::Core
{ 
    IFilterInjector InitFiltersModule()
    {
        return boost::di::make_injector(module());
    }
}
