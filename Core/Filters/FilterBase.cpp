#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "FilterBase.h"

namespace ImageEditor::Core
{
	FilterBase::bgra_ref::bgra_ref(uchar& ib, uchar& ig, uchar& ir, uchar& ia)
		:b(ib), g(ig), r(ir), a(ia)
	{
	}
	
	uchar FilterBase::bgra_ref::normalize(int val)
	{
		return val > 255 ? 255 : (val < 0 ? 0 : val);
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

	FilterBase::FilterBase()
	{
	}
	
	IImagePtr FilterBase::Apply(const IImagePtr image, const std::string& /*parameters*/) const
	{
		UNI_ENSURE_RETURN(image, nullptr);

		BGRAMatrix matrix(image->Data(), image->Width(), image->Height(), image->BytesPerLine());
		Transform(matrix);

		Core::IImagePtr new_image = Core::ImageModule(
			std::move(matrix.Data()),
			matrix.Width(),
			matrix.Height(),
			image->BytesPerLine(),
			image->Format()).create<Core::IImagePtr>();

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
			return FilterBase::bgra_ref{
				data_[line + y * 4 + 0],
				data_[line + y * 4 + 1],
				data_[line + y * 4 + 2],
				data_[line + y * 4 + 3]
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
