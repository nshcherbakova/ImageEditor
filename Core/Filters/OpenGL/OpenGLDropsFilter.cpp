#include "OpenGLDropsFilter.h"
#include <stdafx.h>

static const char *c_filter_name_str = "Drops";
static const char *c_filter_vs_str = ":/Shaders/drops_filter_vs";
static const char *c_filter_fs2_str = ":/Shaders/drops_filter_fs";

namespace ImageEditor::Core {

std::vector<std::pair<const char *, const char *>>
OpenGLDropsFilter::TransformFilters() const {
  return {{c_filter_vs_str, c_filter_fs2_str}};
}

const std::string OpenGLDropsFilter::Description() const {
  return c_filter_name_str;
}

OpenGLDropsFilter::Parameters OpenGLDropsFilter::FilterParameters() const {
  return {true, {1280, 1280}};
}

} // namespace ImageEditor::Core
