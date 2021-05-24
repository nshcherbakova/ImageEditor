#include <stdafx.h>
#include "OpenGLTessFilter.h"

static const char* c_filter_name_str = "Emboss";
static const char* c_filter_vs_str = ":/Shaders/tess_filter_vs";
static const char* c_filter_fs_str = ":/Shaders/tess_filter_fs";
namespace ImageEditor::Core
{  
	std::vector<std::pair<const char*, const char*>> OpenGLTessFilter::TransformFilters() const
	{
		return { {c_filter_vs_str , c_filter_fs_str} };
	}

	const std::string OpenGLTessFilter::Description() const
	{
		return c_filter_name_str;
	}
}