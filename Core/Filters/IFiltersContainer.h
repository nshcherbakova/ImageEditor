#pragma once
#ifndef IMAGEEDITOR_CORE_FILTERS_IFILTERSCONTAINER_H
#define IMAGEEDITOR_CORE_FILTERS_IFILTERSCONTAINER_H
#include <memory>
#include <Core/types.h>

namespace ImageEditor::Core
{
	struct IFiltersContainer
	{
		virtual const IFilterPtrArr Filters() const = 0;
		virtual void AddFilter(IFilterPtr filter) = 0;

		virtual ~IFiltersContainer() {}
	};
}

#endif // IMAGEEDITOR_CORE_FILTERS_IFILTERSCONTAINER_H
