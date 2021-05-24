#pragma once
#ifndef IMAGEEDITOR_CORE_SEPIAFILTER_FILTERS_H
#define IMAGEEDITOR_CORE_SEPIAFILTER_FILTERS_H
#include <Core/Filters/FilterBase.h>

namespace ImageEditor::Core
{
	class SepiaFilter final : public  FilterBase
	{
	public:
		explicit SepiaFilter() = default;
		SepiaFilter& operator= (const SepiaFilter&) = delete;

	public: // IFilter
		virtual const std::string Description() const override final;
	
	private: // FilterBase
		virtual void Transform(BGRAMatrix& image) const override final;
	};
}

#endif // IMAGEEDITOR_CORE_SEPIAFILTER_FILTERS_H
