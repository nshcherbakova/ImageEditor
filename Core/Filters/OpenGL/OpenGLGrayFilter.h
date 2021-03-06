#pragma once
#ifndef IMAGEEDITOR_CORE_OPEN_GL_GRAYFILTER_FILTERS_H
#define IMAGEEDITOR_CORE_OPEN_GL_GRAYFILTER_FILTERS_H
#include <Core/Filters/OpenGL/OpenGLFilterBase.h>

namespace ImageEditor::Core
{
	class OpenGLGrayFilter final :  public  OpenGLFilterBase
	{
	public:
		explicit OpenGLGrayFilter() = default;
		OpenGLGrayFilter& operator= (const OpenGLGrayFilter&) = delete;

	public: // IFilter
		virtual const std::string Description() const override final;

	private: // OpenGLFilterBase
		virtual std::vector< std::pair<const char*, const char*> > TransformFilters() const override final;
	};
}

#endif // IMAGEEDITOR_CORE_STUBFILTER_FILTERS_H
