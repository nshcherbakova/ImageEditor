#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "OpenGLGrayFilter.h"

static const char* c_filter_name_str = "Drops";
static const char* c_filter_vs_str = ":/Shaders/gray_filter_vs";
static const char* c_filter_fs_str = ":/Shaders/gray_filter_fs";
namespace ImageEditor::Core
{
    OpenGLGrayFilter::OpenGLGrayFilter()
    {
 
    }
  
	std::vector<const char*> OpenGLGrayFilter::TransformFilters() const
	{
       
        return { c_filter_vs_str , c_filter_fs_str };
	}

	const std::string OpenGLGrayFilter::Description() const
	{
		return c_filter_name_str;
	}
}