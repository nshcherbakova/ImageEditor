#pragma once
#ifndef IMAGEEDITOR_CORE_WARECOLORFILTER_FILTERS_H
#define IMAGEEDITOR_CORE_WARECOLORFILTER_FILTERS_H
#include <Core/Filters/FilterBase.h>

namespace ImageEditor::Core
{
	class WatercolorFilter final : public FilterBase
	{
	public:
		WatercolorFilter();
		WatercolorFilter(const WatercolorFilter&) = delete;
		WatercolorFilter& operator= (const WatercolorFilter&) = delete;

	public: // IFilter
		virtual const std::string Description() const override final;

	private: // FilterBase
		virtual void Transform(BGRAMatrix& image) const override final;
	};
}

#endif // IMAGEEDITOR_CORE_WARECOLORFILTER_FILTERS_H
