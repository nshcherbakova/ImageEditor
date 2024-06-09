#include "OpenGLFilterBase.h"
#include "platform/GLPlatform.h"
#include <stdafx.h>

namespace {

static const char *c_texture_coord_attr_name_str = "in_texture_coord";
static const char *c_texture_attr_name_str = "in_texture";
static const char *c_rnd_texture_attr_name_str = "random_texture";
static const char *c_resolution_attr_name_str = "in_resolution";
static const char *c_random_attr_name_str = "in_random";
static const char *c_noise_texture_attr_name_str = "noise_texture";

// clang-format off
// rectangle and texture vertexes
static const GLfloat sg_vertexes[] = {
     1.0f,  1.0f, 0.0f,      1.0f, 1.0f,
     1.0f, -1.0f, 0.0f,      1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,      0.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,      0.0f, 1.0f,
};
// clang-format on

// triangles indexes  to draw rectangle for texture
unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

QString shaderDataFromFile(QString file_name) {
  // shader file has no glsl version
  // add version  dependend of platform
  // right now shader code crossplatfom, but version of GLSL are different
  QFile file(file_name);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    spdlog::error("Can't open shader file {0}", file_name.toStdString());
    UNI_ASSERT(false);
  }
  auto text = QTextStream(&file).readAll();
  file.close();

  QString version = ImageEditor::Core::GLPlatform::GLSLVersion();
  return text.arg(version);
}

QImage resizeImage(QImage image, QSize size) {
  QImage new_image(size, image.format());
  QRect rect({0, 0}, size);
  QPainter(&new_image)
      .drawImage(rect, image, image.rect(), Qt::AutoColor | Qt::DiffuseDither);

  // qWarning() << "Image resizing" << " " << image.width() << " " <<
  // image.height(); qWarning() << "New image size" << " " << new_image.width()
  // << " " << new_image.height();

  return new_image;
}
} // namespace

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

  auto filter_parameters = FilterParameters();
  if (filter_parameters.resize_befor_applying) {
    // resize image to sutable for this filter size
    auto new_size = filter_parameters.filtered_image_size;
    // qWarning() << " new size " << new_size;
    if (float(image.width()) / float(image.height()) > 1.0) {
      new_size.setWidth(image.width() * new_size.height() / image.height());
    } else {
      new_size.setHeight(image.height() * new_size.width() / image.width());
    }
    image = resizeImage(image, new_size);
  }

  ogl_functions_->glViewport(0, 0, image.width(), image.height());

  const auto filters = TransformFilters();
  for (unsigned int i = 0; i < filters.size(); i++) {
    image = Apply(image, filters[i], parameters);
  }

  if (filter_parameters.resize_befor_applying) {
    // resize image back
    image =
        resizeImage(image, {int(image_src->Width()), int(image_src->Height())});
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
  GLint screen_noise_texture_uniform = 0;
  GLint screen_resolution_uniform = 0;
  GLint random_uniform = 0;

  QOpenGLFramebufferObject fbo(QSize{image.width(), image.height()});
  QOpenGLBuffer vertex(QOpenGLBuffer::VertexBuffer);
  QOpenGLBuffer index(QOpenGLBuffer::IndexBuffer);
  QOpenGLVertexArrayObject object;

  // Create Shader (Do not release until VAO is created)
  QOpenGLShaderProgram program;

  program.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                  shaderDataFromFile(filter.first));
  program.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                  shaderDataFromFile(filter.second));
  program.link();
  program.bind();

  // Create texture
  texture_attr = program.attributeLocation(c_texture_coord_attr_name_str);
  UNI_ENSURE_RETURN(texture_attr != -1, QImage());

  screen_texture_uniform = program.uniformLocation(c_texture_attr_name_str);
  UNI_ENSURE_RETURN(screen_texture_uniform != -1, QImage());

  screen_rnd_texture_uniform =
      program.uniformLocation(c_rnd_texture_attr_name_str);

  screen_noise_texture_uniform =
      program.uniformLocation(c_noise_texture_attr_name_str);

  screen_resolution_uniform =
      program.uniformLocation(c_resolution_attr_name_str);

  random_uniform = program.uniformLocation(c_random_attr_name_str);

  auto gl_compatible_img =
      image.mirrored().convertToFormat(QImage::Format_RGBA8888);
  QOpenGLTexture texture(gl_compatible_img);
  texture.setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
  texture.setMagnificationFilter(QOpenGLTexture::Linear);

  auto gl_compatible_random_img = QImage(":/Images/random")
                                      .mirrored()
                                      .convertToFormat(QImage::Format_RGBA8888);

  auto gl_compatible_noise_img = QImage(":/Images/noise")
                                     .mirrored()
                                     .convertToFormat(QImage::Format_RGBA8888);

  QOpenGLTexture rnd_texture(gl_compatible_random_img);
  rnd_texture.setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
  rnd_texture.setMagnificationFilter(QOpenGLTexture::Linear);

  QOpenGLTexture noise_texture(gl_compatible_noise_img);
  noise_texture.setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
  noise_texture.setMagnificationFilter(QOpenGLTexture::Linear);

  ogl_functions_->glActiveTexture(GL_TEXTURE0);
  texture.bind(0);

  if (screen_rnd_texture_uniform != -1) {
    ogl_functions_->glActiveTexture(GL_TEXTURE1);
    rnd_texture.bind(1);
  }

  auto screen_noise_texture_id =
      screen_rnd_texture_uniform != -1 ? GL_TEXTURE2 : GL_TEXTURE1;
  if (screen_noise_texture_uniform != -1) {

    ogl_functions_->glActiveTexture(screen_noise_texture_id);
    noise_texture.bind(1);
  }

  program.bind();
  program.setUniformValue(screen_texture_uniform, 0);
  if (screen_rnd_texture_uniform != -1) {
    program.setUniformValue(screen_rnd_texture_uniform,
                            GL_TEXTURE1 - GL_TEXTURE0);
  }

  if (screen_noise_texture_uniform != -1) {
    program.setUniformValue(screen_noise_texture_uniform,
                            screen_noise_texture_id - GL_TEXTURE0);
  }

  program.setUniformValue(screen_resolution_uniform, image.width(),
                          image.height());

  if (random_uniform != -1) {
    // TODO make it more general. Now this code ajusted for drops filter
    // quint32 rv1 = QRandomGenerator::global()->bounded(1, image.width());
    // quint32 rv2 = QRandomGenerator::global()->bounded(1, image.height());
    quint32 rv3 = QRandomGenerator::global()->bounded(1, 2000);
    program.setUniformValue(random_uniform, 1, 1, rv3);
    // qWarning() << rv1 << " " << rv2 << " " << rv3;
  }

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

  if (screen_noise_texture_uniform != -1) {
    noise_texture.release();
  }
  spdlog::info("Image processed");
  return QImage(fbo.toImage()).convertToFormat(image.format());
}

OpenGLFilterBase::Parameters OpenGLFilterBase::FilterParameters() const {
  return Parameters();
}

} // namespace ImageEditor::Core
