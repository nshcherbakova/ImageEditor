#pragma once
#ifndef IMAGEEDITOR_UI_IIMAGE_PROVIDER_H 
#define IMAGEEDITOR_UI_IIMAGE_PROVIDER_H

namespace ImageEditor::UI
{
    struct IImageProvider
    {
        //virtual void onShow(const bool visible) = 0;

        virtual ~IImageProvider() = default;
        virtual const QImage image(const QString& name) const = 0;
        virtual const QString imagesPath() const = 0;
    };
}
#endif // IMAGEEDITOR_UI_IIMAGE_PROVIDER_H