#pragma once
#ifndef IMAGEEDITOR_CORE_FILTERS_IFILTER_H
#define IMAGEEDITOR_CORE_FILTERS_IFILTER_H

namespace ImageEditor::Core::Filters
{
	struct IFilter
	{
	public:
		virtual ~IFilter() {}
	};
}

#endif // IMAGEEDITOR_CORE_FILTERS_IFILTER_H
