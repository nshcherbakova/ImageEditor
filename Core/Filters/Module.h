#pragma once
#ifndef IMAGEEDITOR_CORE_FILTER_MODULE_H
#define IMAGEEDITOR_CORE_FILTER_MODULE_H
#include <Core/Gears/Injector.h>
#include <Core/Filters/StubFilter.h>

namespace ImageEditor::Core
{
    inline auto InitFiltersModule()
    {
        auto injector = boost::di::make_injector(
            boost::di::bind<IFilter>().to<StubFilter>().in(boost::di::singleton)
        );
        return injector;
    }
}
#endif //IMAGEEDITOR_CORE_FILTER_MODULE_H