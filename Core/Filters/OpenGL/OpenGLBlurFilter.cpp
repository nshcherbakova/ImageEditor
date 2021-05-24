#include <stdafx.h>
#include "OpenGLBlurFilter.h"

static const char* c_filter_name_str = "Blur";
static const char* c_filter_vs_str = ":/Shaders/blur_filter_vs";
static const char* c_filter_fs_str = ":/Shaders/blur_filter_fs";
namespace ImageEditor::Core
{
	std::vector< std::pair<const char*, const char*> > OpenGLBlurFilter::TransformFilters() const
	{
        return { {c_filter_vs_str , c_filter_fs_str} };
	}

	const std::string OpenGLBlurFilter::Description() const
	{
		return c_filter_name_str;
	}
}