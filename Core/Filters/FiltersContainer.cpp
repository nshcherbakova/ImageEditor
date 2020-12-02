#include <stdafx.h>
#include "FiltersContainer.h"

namespace ImageEditor::Core
{
	const IFilterPtrArr FiltersContainer::Filters() const
	{
		return filters_;
	}
	void FiltersContainer::AddFilter(IFilterPtr filter)
	{
		core::return_if_check(!filter);
		filters_.push_back(filter);
	}
}