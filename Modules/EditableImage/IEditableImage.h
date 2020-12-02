#pragma once
#ifndef IMAGEEDITOR_MODILES_EDITABLEIMAGE_IEDITABLEIMAGE_H
#define IMAGEEDITOR_MODILES_EDITABLEIMAGE_IEDITABLEIMAGE_H
#include <Modules/types.h>

namespace ImageEditor::Modules
{
	class IEditableImage
	{
	public:
		virtual void UpdateImage(Core::IImagePtr image) = 0;
		virtual Core::IImagePtr Image() const = 0;

		virtual ~IEditableImage() {}
	};
}

#endif // IMAGEEDITOR_MODILES_EDITABLEIMAGE_IEDITABLEIMAGE_H
