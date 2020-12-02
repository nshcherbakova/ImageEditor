#pragma once
#ifndef IMAGEEDITOR_CORE_IMAGE_IMAGE_H
#define IMAGEEDITOR_CORE_IMAGE_IMAGE_H
#include <Core/Image/IImage.h>

namespace ImageEditor::Core
{
	class Image final: public IImage
	{
	public:
		Image();
	};
}

#endif // IMAGEEDITOR_CORE_IMAGE_IMAGE_H
