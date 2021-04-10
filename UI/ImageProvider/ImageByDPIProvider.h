#pragma once
#ifndef IMAGEEDITOR_UI_IMAGE_PROVIDER_H
#define IMAGEEDITOR_UI_IMAGE_PROVIDER_H

#include <Modules/types.h>
#include <UI/types.h>
#include <UI/ImageProvider/IImageProvider.h>

namespace ImageEditor::UI
{
    class ImageByDPIProvider final:  public IImageProvider
    {
    public:
        struct Parameters
        {
        };

        explicit ImageByDPIProvider();
        ImageByDPIProvider& operator= (const ImageByDPIProvider&) = delete;

    public: // IImageProvider
        virtual const QImage image(const QString& name) const override final;
        virtual const QString imagesPath() const override final;

    private: // 
        const QString image_prefix_;
    };
}
#endif // IMAGEEDITOR_UI_IIMAGE_PROVIDER_H
