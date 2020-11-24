#pragma once
#ifndef IMAGEEDITOR_CORE_FILTER_MODULE_H
#define IMAGEEDITOR_CORE_FILTER_MODULE_H
#include <Core/Gears/Module.h>
#include <Core/Filters/Filters.h>

namespace ImageEditor::Core::Filters
{
    auto InitModule()
    {
        auto injector = boost::ext::di::make_injector(
            boost::ext::di::bind<IFilter, Filter>.in(boost::ext::di::shared)
        );
        return injector;
    }
}
#endif //IMAGEEDITOR_CORE_FILTER_MODULE_H