#pragma once
#ifndef IMAGEEDITOR_CORE_IMAGE_IIMAGE_H
#define IMAGEEDITOR_CORE_IMAGE_IIMAGE_H
#include <memory>

namespace ImageEditor::Core::Image
{
	struct IImage;
	using IImagePtr = std::shared_ptr<IImage>;

	struct IImage
	{
	public:
		virtual ~IImage() {}
	private:
	};
}

#endif // IMAGEEDITOR_CORE_IMAGE_IIMAGE_H
