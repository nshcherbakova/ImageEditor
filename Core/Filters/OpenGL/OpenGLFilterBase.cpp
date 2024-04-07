#include "OpenGLFilterBase.h"
#include <stdafx.h>

static const char *c_position_attr_name_str = "in_position";
static const char *c_texture_coord_attr_name_str = "in_texture_coord";
static const char *c_texture_attr_name_str = "in_texture";
static const char *c_rnd_texture_attr_name_str = "random_texture";
static const char *c_resolution_attr_name_str = "in_resolution";

static const GLfloat c_vertices[] = {
    // positions
    -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,

    -1.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 1.0f};

static const GLfloat c_texture_coords[] = {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                                           0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f};
namespace ImageEditor::Core {
std::unique_ptr<QOpenGLFunctions> OpenGLFilterBase::ogl_functions_;

void OpenGLFilterBase::InitializeOpenGL() {
  if (!ogl_functions_) {
    ogl_functions_ = std::make_unique<QOpenGLFunctions>();
    ogl_functions_->initializeOpenGLFunctions();
  }
}

IImagePtr OpenGLFilterBase::Apply(const IImagePtr image_src,
                                  const std::string &parameters) {
  UNI_ENSURE_RETURN(image_src, nullptr);
  spdlog::info("Applyng GL filter {0}", Description());
  InitializeOpenGL();

  UNI_ENSURE_RETURN(ogl_functions_, nullptr);

  QImage image(image_src->Data().data(), image_src->Width(),
               image_src->Height(), image_src->BytesPerLine(),
               QImage::Format(image_src->Format()));

  ogl_functions_->glViewport(0, 0, image.width(), image.height());

  const auto filters = TransformFilters();
  for (unsigned int i = 0; i < filters.size(); i++) {
    image = Apply(image, filters[i], parameters);
  }

  Core::IImagePtr new_image =
      Core::ImageModule(
          ByteArr(image.bits(), image.bits() + image.sizeInBytes()),
          image_src->Width(), image_src->Height(), image_src->BytesPerLine(),
          QImage::Format_ARGB32)
          .create<Core::IImagePtr>();

  return new_image;
}

QImage
OpenGLFilterBase::Apply(const QImage &image,
                        const std::pair<const char *, const char *> &filter,
                        const std::string & /*parameters*/) {
  UNI_ENSURE_RETURN(!image.isNull(), QImage());
  UNI_ENSURE_RETURN(ogl_functions_, QImage());

  GLint position_attr = 0;
  GLint texture_attr = 0;
  GLint screen_texture_uniform = 0;
  GLint screen_rnd_texture_uniform = 0;
  GLint screen_resolution_uniform = 0;

  QOpenGLFramebufferObject fbo(QSize{image.width(), image.height()});

  QOpenGLShaderProgram program(this);
  bool res =
      program.addShaderFromSourceFile(QOpenGLShader::Vertex, filter.first);
  if (res)
    spdlog::info("Vertex shader added from file {0}", filter.first);
  UNI_ENSURE_RETURN(res, QImage());

  res = program.addShaderFromSourceFile(QOpenGLShader::Fragment, filter.second);
  if (res)
    spdlog::info("Fragment shader added from file {0}", filter.first);
  UNI_ENSURE_RETURN(res, QImage());

  program.link();

  position_attr = program.attributeLocation(c_position_attr_name_str);
  UNI_ENSURE_RETURN(position_attr != -1, QImage());

  texture_attr = program.attributeLocation(c_texture_coord_attr_name_str);
  UNI_ENSURE_RETURN(texture_attr != -1, QImage());

  screen_texture_uniform = program.uniformLocation(c_texture_attr_name_str);
  UNI_ENSURE_RETURN(screen_texture_uniform != -1, QImage());

  screen_rnd_texture_uniform =
      program.uniformLocation(c_rnd_texture_attr_name_str);

  screen_resolution_uniform =
      program.uniformLocation(c_resolution_attr_name_str);

  auto gl_compatible_img =
      image.mirrored().convertToFormat(QImage::Format_RGBA8888);
  QOpenGLTexture texture(gl_compatible_img);
  texture.setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
  texture.setMagnificationFilter(QOpenGLTexture::Linear);

  auto gl_compatible_random_img = QImage(":/Images/random")
                                      .mirrored()
                                      .convertToFormat(QImage::Format_RGBA8888);
  QOpenGLTexture rnd_texture(gl_compatible_random_img);
  rnd_texture.setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
  rnd_texture.setMagnificationFilter(QOpenGLTexture::Linear);

  // applay filter
  ogl_functions_->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  ogl_functions_->glClear(GL_COLOR_BUFFER_BIT);

  ogl_functions_->glActiveTexture(GL_TEXTURE0);
  texture.bind(0);

  if (screen_rnd_texture_uniform != -1) {
    ogl_functions_->glActiveTexture(GL_TEXTURE1);
    rnd_texture.bind(1);
  }

  program.bind();
  program.setUniformValue(screen_texture_uniform, 0);
  if (screen_rnd_texture_uniform != -1) {
    program.setUniformValue(screen_rnd_texture_uniform,
                            GL_TEXTURE1 - GL_TEXTURE0);
  }
  const qreal retinaScale = QApplication::activeWindow()->devicePixelRatio();

  // program.setUniformValue(screen_resolution_uniform,
  // QApplication::activeWindow()->width() * retinaScale,
  // QApplication::activeWindow()->height() * retinaScale);
  program.setUniformValue(screen_resolution_uniform, image.width(),
                          image.height());

  QOpenGLBuffer vertexPositionBuffer(QOpenGLBuffer::VertexBuffer);
  vertexPositionBuffer.create();
  vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vertexPositionBuffer.bind();
  vertexPositionBuffer.allocate(c_vertices, 12 * sizeof(float));

  QOpenGLBuffer vertexColorBuffer(QOpenGLBuffer::VertexBuffer);
  vertexColorBuffer.create();
  vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vertexColorBuffer.bind();
  vertexColorBuffer.allocate(c_texture_coords, 12 * sizeof(float));

  vertexPositionBuffer.bind();
  program.enableAttributeArray(c_position_attr_name_str);
  program.setAttributeBuffer(c_position_attr_name_str, GL_FLOAT, 0, 2);

  vertexColorBuffer.bind();
  program.enableAttributeArray(c_texture_coord_attr_name_str);
  program.setAttributeBuffer(c_texture_coord_attr_name_str, GL_FLOAT, 0, 2);

  fbo.bind();
  ogl_functions_->glDrawArrays(GL_TRIANGLES, 0, 6);

  fbo.release();
  texture.release();
  rnd_texture.release();

  program.disableAttributeArray(c_position_attr_name_str);
  program.disableAttributeArray(c_texture_coord_attr_name_str);

  program.release();
  spdlog::info("Image processed");
  return QImage(fbo.toImage()).convertToFormat(image.format());
}
} // namespace ImageEditor::Core
