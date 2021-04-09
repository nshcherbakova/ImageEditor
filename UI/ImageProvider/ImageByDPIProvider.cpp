#include <stdafx.h>
#include <UI/QtConverts.h>
#include "ImageByDPIProvider.h"

static const char* c_2x_suffix_str = "@2x";
static const char* c_empty_suffix_str = "";


namespace ImageEditor::UI
{
    ImageByDPIProvider::ImageByDPIProvider()
        :image_suffix_(QGuiApplication::primaryScreen()->devicePixelRatio() >= 2 
            ? c_2x_suffix_str : c_empty_suffix_str)
    {
    }

    const QImage ImageByDPIProvider::image(const QString& name) const
    {
        return QImage(name + image_suffix_);
    }
}