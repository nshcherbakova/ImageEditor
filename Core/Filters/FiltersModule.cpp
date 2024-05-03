#include "FiltersModule.h"
#include <stdafx.h>

namespace {
using namespace ImageEditor;
using namespace ImageEditor::Core;
IFilterInjector module() noexcept {
  return boost::di::make_injector(
      boost::di::bind<IFilter *[]>()
          .to<GrayFilter, SepiaFilter, TessFilter, WatercolorFilter,
              SmoothFilter>(),
      boost::di::bind<IFilter>().to<GrayFilter>(),
      boost::di::bind<IFilter>().named<class SmoothFilter>().to<SmoothFilter>(),
      boost::di::bind<IFilter>().named<class TessFilter>().to<TessFilter>(),
      boost::di::bind<IFilter>()
          .named<class WatercolorFilter>()
          .to<WatercolorFilter>(),
      boost::di::bind<IFilter>().named<class SepiaFilter>().to<SepiaFilter>());
}

IFilterInjector OpenGLmodule() noexcept {
  return boost::di::make_injector(
      boost::di::bind<IFilter *[]>()
          .to<OpenGLSepiaFilter, /*OpenGLTessFilter,*/ OpenGLDropsFilter,
              OpenGLWaterColorFilter, OpenGLDitheringFilter>(),
      boost::di::bind<IFilter>().to<OpenGLSepiaFilter>(),
      boost::di::bind<IFilter>()
          .named<class OpenGLWaterColorFilter>()
          .to<OpenGLWaterColorFilter>(),
      // boost::di::bind<IFilter>().named<class
      // OpenGLTessFilter>().to<OpenGLTessFilter>(),
      boost::di::bind<IFilter>()
          .named<class OpenGLDitheringFilter>()
          .to<OpenGLDitheringFilter>(),
      boost::di::bind<IFilter>()
          .named<class OpenGLDropsFilter>()
          .to<OpenGLDropsFilter>());
}
} // namespace

namespace ImageEditor::Core {
IFilterInjector InitFiltersModule() {
  return boost::di::make_injector(OpenGLmodule());
}
} // namespace ImageEditor::Core
