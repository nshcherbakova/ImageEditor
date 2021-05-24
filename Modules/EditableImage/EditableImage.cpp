#include <stdafx.h>
#include "EditableImage.h"

namespace ImageEditor::Modules
{
	void EditableImage::UpdateImage(Core::IImagePtr image)
	{
		image_ = std::move(image);
	}

	Core::IImagePtr EditableImage::Image() const
	{
		return image_;
	}

	void EditableImage::SetOriginalImage(Core::IImagePtr image)
	{
		original_image_ = std::move(image);
		UpdateImage(image);
	}
	Core::IImagePtr EditableImage::OriginalImage() const
	{
		return original_image_;
	}
}