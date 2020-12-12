#include <stdafx.h>
#include <Core/Image/IImage.h>
#include "QtConverts.h"

namespace ImageEditor::UI
{
	QImage IImageToQtImage(const Core::IImagePtr& image)
	{
		UNI_ENSURE_RETURN(image, QImage());

		return QImage(
			image->Data().data(),
			image->Width(),
			image->Height(),
			image->BytesPerLine(),
			QImage::Format(image->Format())
			);
	}

	Core::IImagePtr QtImageToIImage(const QImage& image)
	{
		Core::IImagePtr core_image = Core::InitImageModule(
			Core::ByteArr(
			image.bits(), image.bits() + image.sizeInBytes()),
			image.width(),
			image.height(),
			image.bytesPerLine(),
			image.format()).create<Core::IImagePtr>();
		return core_image;
	}
}