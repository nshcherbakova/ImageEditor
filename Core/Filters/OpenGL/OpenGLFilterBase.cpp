#include <stdafx.h>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <Core/Image/IImage.h>
#include "OpenGLFilterBase.h"

static const char* c_position_attr_name_str = "in_position";
static const char* c_texture_coord_attr_name_str = "in_texture_coord";
static const char* c_texture_attr_name_str = "in_texture";
static const char* c_resolution_attr_name_str = "in_resolution";

static const GLfloat c_vertices[] = {
    // positions
     -1.0f, 1.0f,
    -1.0f, -1.0f,
     1.0f, -1.0f,

    -1.0f, 1.0f ,
     1.0f, -1.0f,
     1.0f, 1.0f
};

static const GLfloat c_texture_coords[] = {
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f

};
namespace ImageEditor::Core
{
    std::unique_ptr<QOpenGLFunctions> OpenGLFilterBase::ogl_functions_;

    void OpenGLFilterBase::InitializeOpenGL()
    {
        if (!ogl_functions_)
        {
            ogl_functions_ = std::make_unique<QOpenGLFunctions>();
            ogl_functions_->initializeOpenGLFunctions();
        }
    }

	IImagePtr OpenGLFilterBase::Apply(const IImagePtr image_src, const std::string& parameters)
	{
		UNI_ENSURE_RETURN(image_src, nullptr);

        InitializeOpenGL();

        QImage image(image_src->Data().data(),
            image_src->Width(),
            image_src->Height(),
            image_src->BytesPerLine(),
            QImage::Format(image_src->Format()));

        ogl_functions_->glViewport(0, 0, image.width(), image.height());

        const auto filters = TransformFilters();
        for (unsigned int i = 0; i < filters.size(); i++)
        {
            image = Apply(image, filters[i], parameters);
        }

		Core::IImagePtr new_image = Core::ImageModule(
            ByteArr(image.bits(), image.bits() + image.sizeInBytes()),
			image_src->Width(),
            image_src->Height(),
            image_src->BytesPerLine(),
			QImage::Format_ARGB32).create<Core::IImagePtr>();

		return new_image;
	}

    QImage OpenGLFilterBase::Apply(const QImage& image, const std::pair<const char*, const char*>& filter, const std::string& /*parameters*/)
    {
        UNI_ENSURE_RETURN(!image.isNull(), QImage());

        GLint position_attr = 0;
        GLint texture_attr = 0;
        GLint screen_texture_uniform = 0;
        GLint screen_resolution_uniform = 0;

        QOpenGLShaderProgram program(this);
        bool res = program.addShaderFromSourceFile(QOpenGLShader::Vertex, filter.first);
        UNI_ENSURE_RETURN(res, QImage());

        res = program.addShaderFromSourceFile(QOpenGLShader::Fragment, filter.second);
        UNI_ENSURE_RETURN(res, QImage());
        
        program.link();
        position_attr = program.attributeLocation(c_position_attr_name_str);
        UNI_ENSURE_RETURN(position_attr != -1, QImage());
        
        texture_attr = program.attributeLocation(c_texture_coord_attr_name_str);
        UNI_ENSURE_RETURN(texture_attr != -1, QImage());
        
        screen_texture_uniform = program.uniformLocation(c_texture_attr_name_str);
        UNI_ENSURE_RETURN(screen_texture_uniform != -1, QImage());
        
        screen_resolution_uniform = program.uniformLocation(c_resolution_attr_name_str);


        QOpenGLTexture texture(image.mirrored());
        program.bind();
        program.setUniformValue(screen_texture_uniform, 0);

        program.setUniformValue(screen_resolution_uniform, image.width(), image.height());

        ogl_functions_->glVertexAttribPointer(position_attr, 2, GL_FLOAT, GL_FALSE, 0, c_vertices);
        ogl_functions_->glVertexAttribPointer(texture_attr, 2, GL_FLOAT, GL_FALSE, 0, c_texture_coords);

        ogl_functions_->glEnableVertexAttribArray(position_attr);
        ogl_functions_->glEnableVertexAttribArray(texture_attr);

        QOpenGLFramebufferObject fbo(QSize{ image.width(), image.height() });

        fbo.bind();
        // applay filter
        ogl_functions_->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        ogl_functions_->glClear(GL_COLOR_BUFFER_BIT);

        texture.bind();
        program.bind();

        ogl_functions_->glDrawArrays(GL_TRIANGLES, 0, 6);

        fbo.release();
        ogl_functions_->glDisableVertexAttribArray(texture_attr);
        ogl_functions_->glDisableVertexAttribArray(position_attr);

        program.release();

        return QImage(fbo.toImage());
    }
}
