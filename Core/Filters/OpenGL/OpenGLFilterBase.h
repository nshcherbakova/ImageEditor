#pragma once
#ifndef IMAGEEDITOR_CORE_OPEN_GL_FILTERBASE_FILTERS_H
#define IMAGEEDITOR_CORE_OPEN_GL_FILTERBASE_FILTERS_H
#include <QOpenGLContext>
#include <Core/Filters/IFilter.h>

namespace ImageEditor::Core
{
	class OpenGLFilterBase: public QWindow, protected QOpenGLFunctions,  public virtual IFilter
	{
	public:
		OpenGLFilterBase() {}
		OpenGLFilterBase(const OpenGLFilterBase&) = delete;
		OpenGLFilterBase& operator= (const OpenGLFilterBase&) = delete;
	
	public: // IFilter
		virtual IImagePtr Apply(const IImagePtr image, const std::string& parameters) override final;
		virtual const std::string Description() const override = 0;

	protected:
		virtual std::vector<const char*> TransformFilters() const = 0;

	private:
		QOpenGLContext* m_context = nullptr;
	};
}

#endif // IMAGEEDITOR_CORE_FILTERBASE_FILTERS_H
