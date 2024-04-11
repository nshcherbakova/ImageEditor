#pragma once
#ifndef IMAGEEDITOR_CORE_OPEN_GL_WATERCOLOR_FILTER_FILTERS_H
#define IMAGEEDITOR_CORE_OPEN_GL_WATERCOLOR_FILTER_FILTERS_H
#include <Core/Filters/OpenGL/OpenGLFilterBase.h>

namespace ImageEditor::Core {
class OpenGLWaterColorFilter final : public OpenGLFilterBase {
public:
  explicit OpenGLWaterColorFilter() = default;
  OpenGLWaterColorFilter &operator=(const OpenGLWaterColorFilter &) = delete;

public: // IFilter
  virtual const std::string Description() const override final;

protected:
  virtual Parameters FilterParameters() const override final;

private: // OpenGLFilterBase
  virtual std::vector<std::pair<const char *, const char *>>
  TransformFilters() const override final;
};
} // namespace ImageEditor::Core

#endif // IMAGEEDITOR_CORE_OPEN_GL_WATERCOLOR_FILTER_FILTERS_H
