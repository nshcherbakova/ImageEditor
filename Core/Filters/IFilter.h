#pragma once
#ifndef IMAGEEDITOR_CORE_FILTERS_IFILTER_H
#define IMAGEEDITOR_CORE_FILTERS_IFILTER_H
#include <string>
#include <Core/types.h>

namespace ImageEditor::Core
{
	struct IFilter
	{
		virtual IImagePtr Apply(const IImagePtr image, const std::string& parameters) = 0;
		virtual const std::string Description() const = 0;

		virtual ~IFilter() {}
	};
}

#endif // IMAGEEDITOR_CORE_FILTERS_IFILTER_H
