#pragma once
#ifndef IMAGEEDITOR_CORE_IMAGE_IIMAGE_H
#define IMAGEEDITOR_CORE_IMAGE_IIMAGE_H
#include <Core/types.h>

namespace ImageEditor::Core
{
	struct IImage
	{
		virtual ~IImage() {}
	};
}

#endif // IMAGEEDITOR_CORE_IMAGE_IIMAGE_H
