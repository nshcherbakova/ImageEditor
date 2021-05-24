#pragma once
#ifndef IMAGEEDITOR_MODILES_EDITABLEIMAGE_IEDITABLEIMAGE_H
#define IMAGEEDITOR_MODILES_EDITABLEIMAGE_IEDITABLEIMAGE_H
#include <Modules/types.h>

namespace ImageEditor::Modules
{
	struct IEditableImage
	{
		virtual void SetOriginalImage(Core::IImagePtr image) = 0;
		virtual Core::IImagePtr OriginalImage() const = 0;
		virtual void UpdateImage(Core::IImagePtr image) = 0;
		virtual Core::IImagePtr Image() const = 0;

		virtual ~IEditableImage() = default;
	};
}

#endif // IMAGEEDITOR_MODILES_EDITABLEIMAGE_IEDITABLEIMAGE_H
