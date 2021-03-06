#pragma once
#ifndef IMAGEEDITOR_CORE_SMOOTHFILTER_FILTERS_H
#define IMAGEEDITOR_CORE_SMOOTHFILTER_FILTERS_H
#include <Core/Filters/FilterBase.h>

namespace ImageEditor::Core
{
	class SmoothFilter final : public  FilterBase
	{
	public:
		explicit SmoothFilter() = default;
		SmoothFilter& operator= (const SmoothFilter&) = delete;

	public: // IFilter
		virtual const std::string Description() const override final;

	private: // FilterBase
		virtual void Transform(BGRAMatrix& image) const override final;
	};
}

#endif // IMAGEEDITOR_CORE_STUBFILTER_FILTERS_H
