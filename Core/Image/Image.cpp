#include <stdafx.h>
#include "Image.h"

namespace ImageEditor::Core
{
	Image::Image(Parameters parameters)
		: data_(std::move(parameters.data))
		, width_(parameters.width)
		, height_(parameters.height)
		, bytes_per_line_(parameters.bytes_per_line)
		, format_(parameters.format)
	{
		IsValid();
	}

	ByteArr& Image::Data()
	{
		IsValid();
		return data_;
	}

	uint64_t Image::Width() const
	{
		IsValid();
		return width_;
	}

	uint64_t Image::Height() const
	{
		IsValid();
		return height_;
	}

	uint64_t Image::BytesPerLine() const
	{
		IsValid();
		return bytes_per_line_;
	}

	unsigned int Image::Format() const
	{
		IsValid();
		return format_;
	}

	bool Image::IsValid() const
	{
		bool is_valide =  data_.empty() && width_ == 0 && height_ == 0 && bytes_per_line_ == 0 ||
			!data_.empty() && width_ != 0 && height_ != 0 && bytes_per_line_ != 0;

		UNI_ASSERT(is_valide);

		return is_valide;
	}
}

