#pragma once
#ifndef IMAGEEDITOR_CORE_IMAGE_IIMAGE_H
#define IMAGEEDITOR_CORE_IMAGE_IIMAGE_H
#include <Core/types.h>

namespace ImageEditor::Core
{
	struct IImage
	{
		virtual ByteArr& Data() = 0;
		virtual uint64_t Width() const = 0;
		virtual uint64_t Height() const = 0;
		virtual uint64_t BytesPerLine() const = 0;
		virtual unsigned int Format() const = 0;
		
		virtual ~IImage() = default;
	};
}

#endif // IMAGEEDITOR_CORE_IMAGE_IIMAGE_H
