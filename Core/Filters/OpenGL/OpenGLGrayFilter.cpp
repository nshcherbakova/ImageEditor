#include <stdafx.h>
#include "OpenGLGrayFilter.h"

static const char* c_filter_name_str = "Gray";
static const char* c_filter_vs_str = ":/Shaders/gray_filter_vs";
static const char* c_filter_fs_str = ":/Shaders/gray_filter_fs";
namespace ImageEditor::Core
{
	std::vector< std::pair<const char*, const char*> > OpenGLGrayFilter::TransformFilters() const
	{
		return { {c_filter_vs_str , c_filter_fs_str} };
	}

	const std::string OpenGLGrayFilter::Description() const
	{
		return c_filter_name_str;
	}
}