#pragma once
#ifndef IMAGEEDITOR_CORE_STUBFILTER_FILTERS_H
#define IMAGEEDITOR_CORE_STUBFILTER_FILTERS_H
#include <Core/Filters/IFilter.h>

namespace ImageEditor::Core
{
	class StubFilter final : public IFilter
	{
	public:
		StubFilter();

	public: // IFilter
		virtual IImagePtr Apply(const IImagePtr image, const std::string& parameters) const override final;
		virtual const std::string Description() const override final;
	};
}

#endif // IMAGEEDITOR_CORE_STUBFILTER_FILTERS_H
