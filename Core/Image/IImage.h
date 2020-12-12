#pragma once
#ifndef IMAGEEDITOR_CORE_IMAGE_IIMAGE_H
#define IMAGEEDITOR_CORE_IMAGE_IIMAGE_H
#include <Core/types.h>

namespace ImageEditor::Core
{
	struct IImage
	{
		virtual ByteArr& Data() = 0;
		virtual unsigned int Width() const = 0;
		virtual unsigned int Height() const = 0;
		virtual unsigned int BytesPerLine() const = 0;
		virtual unsigned int Format() const = 0;
		
		virtual ~IImage() {}
	};
}

#endif // IMAGEEDITOR_CORE_IMAGE_IIMAGE_H
