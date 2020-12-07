#pragma once
#ifndef IMAGEEDITOR_CORE_IMAGE_IMAGE_H
#define IMAGEEDITOR_CORE_IMAGE_IMAGE_H
#include <Core/Image/IImage.h>

namespace ImageEditor::Core
{
	class Image final: public IImage
	{
	public:
		struct Parameters
		{
			std::vector<uchar> data;
			unsigned int width;
			unsigned int height;
			unsigned int bytes_per_line;
			unsigned int format;
		};
		explicit Image(Parameters parameters);
		Image& operator= (const Image&) = delete;

	public: // IImage
		virtual const std::vector<uchar>& Data() const final override;
		virtual unsigned int Width() const final override;
		virtual unsigned int Height()  const final override;
		virtual unsigned int BytesPerLine() const final override;
		virtual unsigned int Format() const final override;

	private:
		const std::vector<uchar> data_;
		unsigned int width_;
		unsigned int height_;
		unsigned int bytes_per_line_;
		unsigned int format_;
	};
}

#endif // IMAGEEDITOR_CORE_IMAGE_IMAGE_H
