#include "OpenGLDitheringFilter.h"
#include <stdafx.h>

static const char *c_filter_name_str = "8-Bit";
static const char *c_filter_vs_str = ":/Shaders/dith_filter_vs";
static const char *c_filter_fs_str = ":/Shaders/dith_filter_fs";
namespace ImageEditor::Core {
std::vector<std::pair<const char *, const char *>>

OpenGLDitheringFilter::TransformFilters() const {
  return {{c_filter_vs_str, c_filter_fs_str}};
}

const std::string OpenGLDitheringFilter::Description() const {
  return c_filter_name_str;
}

OpenGLDitheringFilter::Parameters
OpenGLDitheringFilter::FilterParameters() const {
  return {true, {720, 720}};
}
} // namespace ImageEditor::Core
