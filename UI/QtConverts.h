#pragma once
#ifndef IMAGEEDITOR_UI_QTCONVERTS_H
#define IMAGEEDITOR_UI_QTCONVERTS_H
#include <Core/types.h>
#include <QImage>

namespace ImageEditor::UI
{
	QImage IImageToQtImage(const Core::IImagePtr& image);
	Core::IImagePtr QtImageToIImage(const QImage& image);
}

#endif // IMAGEEDITOR_UI_QTCONVERTS_H
