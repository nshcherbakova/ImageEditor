#include <stdafx.h>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QOpenGLTexture>
#include <QOpenGLFramebufferObject>
#include <Core/Image/IImage.h>
#include "OpenGLFilterBase.h"

namespace ImageEditor::Core
{
    //QOpenGLContext*  OpenGLFilterBase::m_context = nullptr;
    //bool OpenGLFilterBase::init_context = false;
	IImagePtr OpenGLFilterBase::Apply(const IImagePtr image_src, const std::string& /*parameters*/)
	{
		UNI_ENSURE_RETURN(image_src, nullptr);

        if (!m_context) {
            m_context = new QOpenGLContext(this);
            m_context->setFormat(requestedFormat());
            m_context->create();
        }
        m_context->makeCurrent(this);

        {
            initializeOpenGLFunctions();

            QSurfaceFormat format;
            format.setSamples(16);
            setFormat(format);
        }

        GLint m_posAttr = 0;
        GLint m_texAttr = 0;
        GLint m_screenTextureUniform = 0;
        QOpenGLTexture* texture = nullptr;
        QOpenGLShaderProgram* m_program = nullptr;

        auto filters = TransformFilters();
        Q_ASSERT(filters.size() == 2);

        m_program = new QOpenGLShaderProgram(this);
        bool res = m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, filters[0]);
        Q_ASSERT(res);
        res = m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, filters[1]);
        Q_ASSERT(res);
        m_program->link();
        m_posAttr = m_program->attributeLocation("posAttr");
        Q_ASSERT(m_posAttr != -1);
        m_texAttr = m_program->attributeLocation("texAttr");
        Q_ASSERT(m_texAttr != -1);
        m_screenTextureUniform = m_program->uniformLocation("texture");
        Q_ASSERT(m_screenTextureUniform != -1);


        QImage image(image_src->Data().data(),
            image_src->Width(),
            image_src->Height(),
            image_src->BytesPerLine(),
            QImage::Format(image_src->Format()));

        glViewport(0, 0, image.width(), image.height());


        texture = new QOpenGLTexture(image.mirrored());
        m_program->bind();
        m_program->setUniformValue(m_screenTextureUniform, 0);


        static const GLfloat vertices[] = {
            // positions
             -1.0f, 1.0f,
            -1.0f, -1.0f,
             1.0f, -1.0f,

            -1.0f, 1.0f ,
             1.0f, -1.0f,
             1.0f, 1.0f
        };

        static const GLfloat texture_coords[] = {
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

            0.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 1.0f
        };

        glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glVertexAttribPointer(m_texAttr, 2, GL_FLOAT, GL_FALSE, 0, texture_coords);

        glEnableVertexAttribArray(m_posAttr);
        glEnableVertexAttribArray(m_texAttr);

        QOpenGLFramebufferObject fbo(QSize{ image.width(), image.height() });

        fbo.bind();
        // applay filter
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        texture->bind();
        m_program->bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);

        QImage fboImage(fbo.toImage());

        fbo.release();
        glDisableVertexAttribArray(m_texAttr);
        glDisableVertexAttribArray(m_posAttr);

        m_program->release();

		Core::IImagePtr new_image = Core::ImageModule(
            ByteArr(fboImage.bits(), fboImage.bits() + fboImage.sizeInBytes()),
			image_src->Width(),
            image_src->Height(),
            image_src->BytesPerLine(),
			QImage::Format_ARGB32).create<Core::IImagePtr>();

		return new_image;
	}
}
