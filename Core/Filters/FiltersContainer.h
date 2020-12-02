#pragma once
#ifndef IMAGEEDITOR_CORE_FILTERS_FILTERSCONTAINER_H
#define IMAGEEDITOR_CORE_FILTERS_FILTERSCONTAINER_H
#include <Core/Filters/IFiltersContainer.h>

namespace ImageEditor::Core
{
	class FiltersContainer final : public IFiltersContainer
	{
	public: // IFiltersContainer
		virtual const IFilterPtrArr Filters() const  override final;
		virtual void AddFilter(IFilterPtr filter) override final;

	private:
		IFilterPtrArr filters_;
	};
}

#endif // IMAGEEDITOR_CORE_FILTERS_FILTERSCONTAINER_H
