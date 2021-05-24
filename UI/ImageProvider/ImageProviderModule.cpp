#include <stdafx.h>
#include "ImageProviderModule.h"
#include "ImageByDPIProvider.h"

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
