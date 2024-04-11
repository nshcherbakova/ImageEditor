#pragma once
#ifndef IMAGEEDITOR_CORE_OPEN_GL_FILTERBASE_FILTERS_H
#define IMAGEEDITOR_CORE_OPEN_GL_FILTERBASE_FILTERS_H
#include <Core/Filters/IFilter.h>
#include <QObject>
#include <QSize>

class QImage;
class QOpenGLFunctions;
namespace ImageEditor::Core {
class OpenGLFilterBase : public QObject, public virtual IFilter {
  Q_OBJECT
public:
  explicit OpenGLFilterBase() = default;
  OpenGLFilterBase &operator=(const OpenGLFilterBase &) = delete;

public: // IFilter
  virtual IImagePtr Apply(const IImagePtr image,
                          const std::string &parameters) override final;
  virtual const std::string Description() const override = 0;

protected:
  struct Parameters {
    bool resize_befor_applying = false;
    QSize filtered_image_size;
  };

protected:
  virtual std::vector<std::pair<const char *, const char *>>
  TransformFilters() const = 0;
  virtual Parameters FilterParameters() const;

private:
  QImage Apply(const QImage &image,
               const std::pair<const char *, const char *> &filter,
               const std::string & /*parameters*/);
  void InitializeOpenGL();

protected:
  static std::unique_ptr<QOpenGLFunctions> ogl_functions_;
};
} // namespace ImageEditor::Core

#endif // IMAGEEDITOR_CORE_FILTERBASE_FILTERS_H
