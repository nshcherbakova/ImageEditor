#include "OpenGLSepiaFilter.h"
#include <stdafx.h>

static const char *c_filter_name_str = "Retro";
static const char *c_filter_vs_str = ":/Shaders/sepia_filter_vs";
static const char *c_filter_fs_str = ":/Shaders/sepia_filter_fs";
namespace ImageEditor::Core {
std::vector<std::pair<const char *, const char *>>
OpenGLSepiaFilter::TransformFilters() const {
  return {{c_filter_vs_str, c_filter_fs_str}};
}

const std::string OpenGLSepiaFilter::Description() const {
  return c_filter_name_str;
}

OpenGLSepiaFilter::Parameters OpenGLSepiaFilter::FilterParameters() const {
  return {true, {2048, 2048}};
}
} // namespace ImageEditor::Core
