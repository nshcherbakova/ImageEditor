#include <stdafx.h>
#include <UI/QtConverts.h>
#include "ImageByDPIProvider.h"

static const char* c_2x_filter_str = ":/Images/2x";
static const char* c_default_filter_str = ":/Images/default";

namespace ImageEditor::UI
{
    ImageByDPIProvider::ImageByDPIProvider()
        :image_prefix_(QGuiApplication::primaryScreen()->devicePixelRatio() < 2
            ? c_2x_filter_str : c_default_filter_str)
    {
    }

    const QImage ImageByDPIProvider::image(const QString& name) const
    {
        return QImage(image_prefix_ + "/" + name);
    }

    const QString ImageByDPIProvider::imagesPath() const
    {
        return image_prefix_;
    }
}