// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "openglwindow.h"

#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QScreen>
#include <QtMath>

//! [1]
class TriangleWindow : public OpenGLWindow {
public:
  using OpenGLWindow::OpenGLWindow;

  void initialize() override;
  void render() override;
  void Apply();

private:
  GLint position_attr = 0;
  GLint texture_attr = 0;
  GLint screen_texture_uniform = 0;
  GLint screen_rnd_texture_uniform = 1;
  GLint screen_resolution_uniform = 0;

  QOpenGLTexture *texture = nullptr;
  QOpenGLTexture *rnd_texture = nullptr;

  QOpenGLShaderProgram *m_program = nullptr;
  QImage image;
  // int m_frame = 0;
};
//! [1]

//! [2]
int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(16);

  /* qWarning()<< "******* " << format.majorVersion();
   qWarning()<< "******* " << format.minorVersion();
   format.setMajorVersion(3);
   format.setMinorVersion(3);
   format.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);*/

  TriangleWindow window;
  window.setFormat(format);
  window.resize(1280, 720);
  window.show();

  window.setAnimating(true);

  return app.exec();
}

static const char *c_position_attr_name_str = "in_position";
static const char *c_texture_coord_attr_name_str = "in_texture_coord";
static const char *c_texture_attr_name_str = "in_texture";
static const char *c_random_texture_attr_name_str = "random_texture";
static const char *c_resolution_attr_name_str = "in_resolution";

static const QString c_fs_file_str = ":/Shaders/drops_filter_fs";
static const QString c_vs_file_str = ":/Shaders/filter_vs";
static const QString c_random_file_str = ":/Images/random";
static const QString c_picture_file_str = ":/Images/download";

static const GLfloat c_vertices[] = {
    // positions
    -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,

    -1.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 1.0f};

static const GLfloat c_texture_coords[] = {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                                           0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f};

void TriangleWindow::initialize() {
  m_program = new QOpenGLShaderProgram(this);

  QOpenGLShaderProgram program(this);
  bool res =
      m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, c_vs_file_str);

  Q_ASSERT(res);

  res = m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           c_fs_file_str);

  // Q_ASSERT(res);

  m_program->link();

  position_attr = m_program->attributeLocation(c_position_attr_name_str);
  Q_ASSERT(position_attr != -1);

  texture_attr = m_program->attributeLocation(c_texture_coord_attr_name_str);
  Q_ASSERT(texture_attr != -1);

  screen_texture_uniform = m_program->uniformLocation(c_texture_attr_name_str);
  // Q_ASSERT(screen_texture_uniform != -1);

  screen_rnd_texture_uniform =
      m_program->uniformLocation(c_random_texture_attr_name_str);
  // Q_ASSERT(screen_rnd_texture_uniform != -1);

  screen_resolution_uniform =
      m_program->uniformLocation(c_resolution_attr_name_str);

  image = QImage(c_picture_file_str); //.scaledToHeight(4320);

  auto gl_compatible_img =
      image.mirrored().convertToFormat(QImage::Format_RGBA8888);
  texture = new QOpenGLTexture(
      gl_compatible_img, QOpenGLTexture::MipMapGeneration::GenerateMipMaps);
  texture->setAutoMipMapGenerationEnabled(true);
  // texture->setMipLevels(texture->maximumMipLevels());

  texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  // texture->allocateStorage();
  // texture->generateMipMaps();

  QImage random_image(c_random_file_str);

  auto gl_compatible_random_img =
      random_image.mirrored().convertToFormat(QImage::Format_RGBA8888);
  rnd_texture = new QOpenGLTexture(gl_compatible_random_img);
  rnd_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
  rnd_texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void TriangleWindow::Apply() {

  const qreal retinaScale = devicePixelRatio();
  glViewport(0, 0, image.width(), image.height());

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glActiveTexture(GL_TEXTURE0);
  texture->bind(0);

  glActiveTexture(GL_TEXTURE1);
  rnd_texture->bind(1);

  m_program->bind();

  m_program->setUniformValue(screen_texture_uniform, 0);
  m_program->setUniformValue(screen_rnd_texture_uniform,
                             GL_TEXTURE1 - GL_TEXTURE0);
  m_program->setUniformValue(screen_resolution_uniform, image.width(),
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
  m_program->enableAttributeArray(c_position_attr_name_str);
  m_program->setAttributeBuffer(c_position_attr_name_str, GL_FLOAT, 0, 2);

  vertexColorBuffer.bind();
  m_program->enableAttributeArray(c_texture_coord_attr_name_str);
  m_program->setAttributeBuffer(c_texture_coord_attr_name_str, GL_FLOAT, 0, 2);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  texture->release();
  rnd_texture->release();
  m_program->disableAttributeArray(c_position_attr_name_str);
  m_program->disableAttributeArray(c_texture_coord_attr_name_str);

  m_program->release();
}
void TriangleWindow::render() {
  Apply();
  //++m_frame;
}
//! [5]
