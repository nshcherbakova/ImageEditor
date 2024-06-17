#include "OpenGLTessFilter.h"
#include <stdafx.h>

static const char *c_filter_name_str = "Tess";
static const char *c_filter_vs_str = ":/Shaders/tess_filter_vs";
static const char *c_filter_fs_str = ":/Shaders/tess_filter_fs";
namespace ImageEditor::Core {
std::vector<std::pair<const char *, const char *>>
OpenGLTessFilter::TransformFilters() const {
  return {{c_filter_vs_str, c_filter_fs_str}};
}

const std::string OpenGLTessFilter::Description() const {
  return c_filter_name_str;
}
OpenGLTessFilter::Parameters OpenGLTessFilter::FilterParameters() const {
  return {true, {1024, 1024}};
}
} // namespace ImageEditor::Core
