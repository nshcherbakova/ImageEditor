#include <stdafx.h>
#include "FilterBase.h"

namespace ImageEditor::Core
{

	FilterBase::bgra_ref::bgra_ref(uchar& ib, uchar& ig, uchar& ir, uchar& ia)
		:b(ib), g(ig), r(ir), a(ia)
	{
	}

	uchar FilterBase::bgra_ref::normalize(int val)
	{
		return val > std::numeric_limits<unsigned char>::max() ? std::numeric_limits<unsigned char>::max() : (val < 0 ? 0 : val);
	}

	void FilterBase::bgra_ref::update(const int ib, const int ig, const int ir)
	{
		b = normalize(ib);
		g = normalize(ig);
		r = normalize(ir);
	}

	void FilterBase::bgra_ref::update(const int ib, const int ig, const int ir, const int ia)
	{
		update(ib, ig, ir);
		a = normalize(ia);
	}

	IImagePtr FilterBase::Apply(const IImagePtr image, const std::string& /*parameters*/)
	{
		UNI_ENSURE_RETURN(image, nullptr);
        spdlog::info("Applyng filter {0}", Description() );

		BGRAMatrix matrix(image->Data(), image->Width(), image->Height(), image->BytesPerLine());
		Transform(matrix);

		Core::IImagePtr new_image = Core::ImageModule(
			std::move(matrix.Data()),
			matrix.Width(),
			matrix.Height(),
			image->BytesPerLine(),
			image->Format()).create<Core::IImagePtr>();

        spdlog::info("Image processed");
		return new_image;
	}

	FilterBase::BGRAMatrix::BGRAMatrix(const ByteArr& data,
		unsigned int width,
		unsigned int height,
		unsigned int bytes_per_line)
		: data_(data)
		, width_(width)
		, height_(height)
		, bytes_per_line_(bytes_per_line)
	{

	}

	FilterBase::bgra_ref FilterBase::BGRAMatrix::GetPixel(const uint64_t x, const uint64_t y)
	{
		const uint64_t line = x * bytes_per_line_;
		const int linr_shift = line + y * 4;
		return FilterBase::bgra_ref{
			data_[linr_shift + 0],
			data_[linr_shift + 1],
			data_[linr_shift + 2],
			data_[linr_shift + 3]
		};

	}

	unsigned int FilterBase::BGRAMatrix::Height()
	{
		return height_;
	}

	unsigned int FilterBase::BGRAMatrix::Width()
	{
		return width_;
	}

	ByteArr& FilterBase::BGRAMatrix::Data()
	{
		return data_;
	}
}
