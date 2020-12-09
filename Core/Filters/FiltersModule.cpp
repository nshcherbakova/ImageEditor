#pragma once
#include <stdafx.h>
#include <Core/Filters/StubFilter.h>
#include "FiltersModule.h"

namespace 
{
    using namespace ImageEditor;
    using namespace ImageEditor::Core;
    IFilterInjector module() noexcept {
        return boost::di::make_injector(
            boost::di::bind<IFilter>().to<StubFilter>().in(boost::di::singleton)
        );
    }
}

namespace ImageEditor::Core
{ 
    IFilterInjector InitFiltersModule()
    {
        return boost::di::make_injector(module());
    }
}