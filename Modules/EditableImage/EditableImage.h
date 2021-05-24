#pragma once
#ifndef IMAGEEDITOR_MODILES_EDITABLEIMAGE_EDITABLEIMAGE_H
#define IMAGEEDITOR_MODILES_EDITABLEIMAGE_EDITABLEIMAGE_H

#include "IEditableImage.h"

namespace ImageEditor::Modules
{
	class EditableImage final: public IEditableImage
	{
	public:
		explicit EditableImage() = default;
		EditableImage(const EditableImage&) = delete;
		EditableImage& operator= (const EditableImage&) = delete;

	public: // IEditableImage
		virtual void UpdateImage(Core::IImagePtr image) override final;
		virtual Core::IImagePtr Image() const override final;
		virtual void SetOriginalImage(Core::IImagePtr image) override final;
		virtual Core::IImagePtr OriginalImage() const override final;

	private:
		Core::IImagePtr original_image_;
		Core::IImagePtr image_;
	};
}

#endif // IMAGEEDITOR_MODILES_EDITABLEIMAGE_EDITABLEIMAGE_H
