#include "OpenGLFilterBase.h"
#include <stdafx.h>

static const char *c_texture_coord_attr_name_str = "in_texture_coord";
static const char *c_texture_attr_name_str = "in_texture";
static const char *c_rnd_texture_attr_name_str = "random_texture";
static const char *c_resolution_attr_name_str = "in_resolution";

static const GLfloat sg_vertexes[] = {
    1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
};

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

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

  // const qreal retinaScale = QApplication::activeWindow()->devicePixelRatio();
  // qWarning() << "*********** " << image.height();
  //  qWarning() << "*********** " << image.width();
  /* if(720 / 1280 < image.height()/ image.width())
       image = image.scaledToWidth(2560, Qt::SmoothTransformation);
   else
       image = image.scaledToHeight(1440, Qt::SmoothTransformation);*/

  // qWarning() << "*********** " << image.height();
  // qWarning() << "*********** " << image.width();

  /* QImage image(image_src->Data().data(), image_src->Width(),
                image_src->Height(), image_src->BytesPerLine(),
                QImage::Format(image_src->Format()));*/

  ogl_functions_->glViewport(0, 0, image.width(), image.height());

  const auto filters = TransformFilters();
  for (unsigned int i = 0; i < filters.size(); i++) {
    image = Apply(image, filters[i], parameters);
  }

  Core::IImagePtr new_image =
      Core::ImageModule(
          ByteArr(image.bits(), image.bits() + image.sizeInBytes()),
          image.width(), image.height(), image.bytesPerLine(),
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

  GLint texture_attr = 0;
  GLint screen_texture_uniform = 0;
  GLint screen_rnd_texture_uniform = 0;
  GLint screen_resolution_uniform = 0;

  QOpenGLFramebufferObject fbo(QSize{image.width(), image.height()});
  QOpenGLBuffer vertex(QOpenGLBuffer::VertexBuffer);
  QOpenGLBuffer index(QOpenGLBuffer::IndexBuffer);
  QOpenGLVertexArrayObject object;

  // Create Shader (Do not release until VAO is created)
  QOpenGLShaderProgram program;

  QFile vfile(filter.first);
  vfile.open(QFile::ReadOnly | QFile::Text);
  auto vtext = QTextStream(&vfile).readAll();
  vfile.close();

  QFile ffile(filter.second);
  ffile.open(QFile::ReadOnly | QFile::Text);
  auto ftext = QTextStream(&ffile).readAll();
  ffile.close();

  QString version;
#ifdef Q_OS_ANDROID
  version = "320 es";
#else
  version = "330 core";
#endif

  program.addShaderFromSourceCode(QOpenGLShader::Vertex, vtext.arg(version));
  program.addShaderFromSourceCode(QOpenGLShader::Fragment, ftext.arg(version));
  program.link();
  program.bind();

  // Create texture
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

  program.setUniformValue(screen_resolution_uniform, image.width(),
                          image.height());

  // Create Buffer (Do not release until VAO is created)
  vertex.create();
  index.create();

  object.create();
  object.bind();

  vertex.bind();
  vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

  index.bind();
  index.setUsagePattern(QOpenGLBuffer::StaticDraw);
  index.allocate(indices, sizeof(indices));

  // Create Vertex Array Object
  program.enableAttributeArray(0);
  program.setAttributeBuffer(0, GL_FLOAT, 0, 3, 5 * sizeof(float));
  program.enableAttributeArray(1);
  program.setAttributeBuffer(1, GL_FLOAT, 3 * sizeof(float), 2,
                             5 * sizeof(float));

  glClear(GL_COLOR_BUFFER_BIT);

  // Render using our shader
  program.bind();

  object.bind();
  fbo.bind();
  ogl_functions_->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  fbo.release();

  object.release();
  index.release();
  vertex.release();
  program.release();
  texture.release();
  if (screen_rnd_texture_uniform != -1) {
    rnd_texture.release();
  }

  spdlog::info("Image processed");
  return QImage(fbo.toImage()).convertToFormat(image.format());
}
} // namespace ImageEditor::Core
