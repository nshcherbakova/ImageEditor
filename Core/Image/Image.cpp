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
	}

	ByteArr& Image::Data()
	{
		return data_;
	}

	unsigned int Image::Width() const
	{
		return width_;
	}

	unsigned int Image::Height() const
	{
		return height_;
	}

	unsigned int Image::BytesPerLine() const
	{
		return bytes_per_line_;
	}

	unsigned int Image::Format() const
	{
		return format_;
	}
}

