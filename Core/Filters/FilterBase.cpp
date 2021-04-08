#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "FilterBase.h"

namespace ImageEditor::Core
{
	FilterBase::bgra::bgra()
	{
	}

	FilterBase::bgra::bgra(int ib, int ig, int ir, int ia)
	{
		b = ib > 255 ? 255 : (ib < 0 ? 0 : ib);
		g = ig > 255 ? 255 : (ig < 0 ? 0 : ig);
		r = ir > 255 ? 255 : (ir < 0 ? 0 : ir);
		a = ia > 255 ? 255 : (ia < 0 ? 0 : ia);
	}
	FilterBase::FilterBase()
	{
	}
	
	IImagePtr FilterBase::Apply(const IImagePtr image, const std::string& /*parameters*/) const
	{
		UNI_ENSURE_RETURN(image, nullptr);
		bgraMatrix arr = ConvertToRgb(image);

		Transform(arr);

		Core::IImagePtr new_image = ConvertToIImage(arr, image->BytesPerLine(), image->Format());
		return new_image;
	}

	FilterBase::bgraMatrix FilterBase::ConvertToRgb(const IImagePtr& image) const
	{
		UNI_ENSURE_RETURN(image, FilterBase::bgraMatrix());

		bgraMatrix arr;
		arr.resize(image->Height());
		for (uint64_t i = 0 ; i < image->Height(); i++)
		{
			arr[i].resize(image->Width());
		}
		
		for (uint64_t i = 0; i < image->Height(); i++)
		{
			for (uint64_t j = 0;  j < image->Width(); j++)
			{
				const uint64_t line = i * image->BytesPerLine();
				arr[i][j] = bgra{
					image->Data()[line + j * 4 + 0], 
					image->Data()[line + j * 4 + 1], 
					image->Data()[line + j * 4 + 2],  
					image->Data()[line + j * 4 + 3] 
				};
			}
		}

		return arr;
	}

	IImagePtr FilterBase::ConvertToIImage(const FilterBase::bgraMatrix& arr, unsigned int bytes_per_line, unsigned int format) const
	{
		UNI_ENSURE_RETURN(!arr.empty(), nullptr);

		ByteArr new_img_data(arr.size()*arr[0].size()*16, 0);

		uint64_t k = 0;
		for (uint64_t i = 0; i < arr.size(); i++)
		{
			for (uint64_t j = 0; j < arr[0].size(); j++)
			{
				new_img_data[k] = arr[i][j].b;
				k++;
				new_img_data[k] = arr[i][j].g;
				k++;
				new_img_data[k] = arr[i][j].r;
				k++;
				new_img_data[k] = arr[i][j].a;
				k++;
			}
		}

		Core::IImagePtr new_image = Core::ImageModule(
			new_img_data,
			arr[0].size(),
			arr.size(),
			bytes_per_line,
			format).create<Core::IImagePtr>();

		return new_image;
	}


	const std::string FilterBase::Description() const
	{
		return "gray";
	}
}