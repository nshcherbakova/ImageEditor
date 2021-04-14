#pragma once
#ifndef IMAGEEDITOR_CORE_TESSFILTER_FILTERS_H
#define IMAGEEDITOR_CORE_TESSFILTER_FILTERS_H
#include <Core/Filters/FilterBase.h>

namespace ImageEditor::Core
{
	class TessFilter final : public FilterBase
	{
	public:
		TessFilter();
		TessFilter(const TessFilter&) = delete;
		TessFilter& operator= (const TessFilter&) = delete;

	public: // IFilter
		virtual const std::string Description() const override final;

	private: // FilterBase
		virtual void Transform(BGRAMatrix& image) const override final;
	};
}

#endif // IMAGEEDITOR_CORE_TESSFILTER_FILTERS_H
