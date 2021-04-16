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
			ByteArr data;
			const uint64_t width;
			const uint64_t height;
			const uint64_t bytes_per_line;
			const unsigned int format;
		};
		explicit Image(Parameters parameters);
		Image& operator= (const Image&) = delete;

	public: // IImage
		virtual ByteArr& Data() final override;
		virtual uint64_t Width() const final override;
		virtual uint64_t Height()  const final override;
		virtual uint64_t BytesPerLine() const final override;
		virtual unsigned int Format() const final override;

	private:
		ByteArr data_;
		const uint64_t width_;
		const uint64_t height_;
		const uint64_t bytes_per_line_;
		const uint64_t format_;
	};
}

#endif // IMAGEEDITOR_CORE_IMAGE_IMAGE_H
