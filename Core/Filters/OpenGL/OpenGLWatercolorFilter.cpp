#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "OpenGLWatercolorFilter.h"

static const char* c_filter_name_str = "Aqua";
static const char* c_filter_vs_str = ":/Shaders/watercolor_filter_vs";
static const char* c_filter_fs1_str = ":/Shaders/watercolor_filter_1_fs";
static const char* c_filter_fs2_str = ":/Shaders/watercolor_filter_2_fs";
namespace ImageEditor::Core
{
	OpenGLWaterColorFilter::OpenGLWaterColorFilter()
    {
 
    }
  
	std::vector<std::pair<const char*, const char*>> OpenGLWaterColorFilter::TransformFilters() const
	{
       
		return { {c_filter_vs_str , c_filter_fs1_str}
		,  {c_filter_vs_str , c_filter_fs2_str} };
	}

	const std::string OpenGLWaterColorFilter::Description() const
	{
		return c_filter_name_str;
	}
}