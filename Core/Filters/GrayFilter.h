#pragma once
#ifndef IMAGEEDITOR_CORE_STUBFILTER_FILTERS_H
#define IMAGEEDITOR_CORE_STUBFILTER_FILTERS_H
#include <Core/Filters/FilterBase.h>

namespace ImageEditor::Core
{
	class GrayFilter final : public  FilterBase
	{
	public:
		GrayFilter();
		GrayFilter(const GrayFilter&) = delete;
		GrayFilter& operator= (const GrayFilter&) = delete;

	public: // IFilter
		virtual const std::string Description() const override final;
	
	private: // FilterBase
		virtual void Transform(FilterBase::bgraMatrix& image) const override final;
	};
}

#endif // IMAGEEDITOR_CORE_STUBFILTER_FILTERS_H
