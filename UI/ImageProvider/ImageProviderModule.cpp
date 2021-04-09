#include <stdafx.h>
#include <UI/ImageProvider/ImageByDPIProvider.h>
#include "ImageProviderModule.h"

namespace 
{
    using namespace ImageEditor;
    using namespace ImageEditor::UI;
    ImageProviderInjector module() noexcept {
        return boost::di::make_injector(
            boost::di::bind<IImageProvider>().to<ImageByDPIProvider>().in(boost::di::singleton)
        );
    }
}

namespace ImageEditor::UI
{ 
    ImageProviderInjector InitImageProviderModule()
    {
        return boost::di::make_injector(module());
    }
}
