#include <stdafx.h>
#include <fstream>
#include "EditableImage.h"

namespace ImageEditor::Modules
{
	void EditableImage::UpdateImage(Core::IImagePtr image) 
	{
		image_ = image;
	}

	Core::IImagePtr EditableImage::Image() const
	{
		return image_;
	}
}