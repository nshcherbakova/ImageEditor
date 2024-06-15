#pragma once
#ifndef IMAGEEDITOR_CORE_OPEN_GL_SEPIA_FILTERS_H
#define IMAGEEDITOR_CORE_OPEN_GL_SEPIA_FILTERS_H
#include <Core/Filters/OpenGL/OpenGLFilterBase.h>

namespace ImageEditor::Core {
class OpenGLSepiaFilter final : public OpenGLFilterBase {
public:
  explicit OpenGLSepiaFilter() = default;
  OpenGLSepiaFilter &operator=(const OpenGLSepiaFilter &) = delete;

public: // IFilter
  virtual const std::string Description() const override final;

protected:
  virtual Parameters FilterParameters() const override final;

private: // OpenGLFilterBase
  virtual std::vector<std::pair<const char *, const char *>>
  TransformFilters() const override final;
};
} // namespace ImageEditor::Core

#endif // IMAGEEDITOR_CORE_OPEN_GL_SEPIA_FILTERS_H
