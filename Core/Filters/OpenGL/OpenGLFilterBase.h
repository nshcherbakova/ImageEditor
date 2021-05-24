#pragma once
#ifndef IMAGEEDITOR_CORE_OPEN_GL_FILTERBASE_FILTERS_H
#define IMAGEEDITOR_CORE_OPEN_GL_FILTERBASE_FILTERS_H
#include <QObject>
#include <Core/Filters/IFilter.h>

class QImage;
class QOpenGLFunctions;
namespace ImageEditor::Core
{
	class OpenGLFilterBase: public QObject,  public virtual IFilter
	{
		Q_OBJECT
	public:
		explicit OpenGLFilterBase() = default;
		OpenGLFilterBase& operator= (const OpenGLFilterBase&) = delete;
	
	public: // IFilter
		virtual IImagePtr Apply(const IImagePtr image, const std::string& parameters) override final;
		virtual const std::string Description() const override = 0;

	protected:
		virtual std::vector< std::pair<const char*, const char*> > TransformFilters() const = 0;
	
	private:
		QImage Apply(const QImage& image, const std::pair<const char*, const char*>& filter, const std::string& /*parameters*/);
		void InitializeOpenGL();

	protected:
		static std::unique_ptr<QOpenGLFunctions> ogl_functions_;
	
	};
}

#endif // IMAGEEDITOR_CORE_FILTERBASE_FILTERS_H
