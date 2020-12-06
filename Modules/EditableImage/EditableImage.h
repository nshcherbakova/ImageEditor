#pragma once
#ifndef IMAGEEDITOR_MODILES_EDITABLEIMAGE_EDITABLEIMAGE_H
#define IMAGEEDITOR_MODILES_EDITABLEIMAGE_EDITABLEIMAGE_H

#include "IEditableImage.h"

namespace ImageEditor::Modules
{
	class EditableImage final: public IEditableImage
	{
	public: // IEditableImage
		virtual void UpdateImage(Core::IImagePtr image) override final;
		virtual Core::IImagePtr Image() const override final;
	
	private:
		Core::IImagePtr image_;
		std::string path_;
	};
}

#endif // IMAGEEDITOR_MODILES_EDITABLEIMAGE_EDITABLEIMAGE_H
