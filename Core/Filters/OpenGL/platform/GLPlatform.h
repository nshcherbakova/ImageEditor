#pragma once
#ifndef IMAGEEDITOR_CORE_OPEN_GL_PLATFORM_H
#define IMAGEEDITOR_CORE_OPEN_GL_PLATFORM_H
#include <Core/Filters/OpenGL/OpenGLFilterBase.h>

namespace ImageEditor::Core::GLPlatform {
QString GLSLVersion() {
#ifdef Q_OS_ANDROID
  return "320 es";
#else
  return "330 core";
#endif
}
} // namespace ImageEditor::Core::GLPlatform

#endif // IMAGEEDITOR_CORE_OPEN_GL_PLATFORM_H
