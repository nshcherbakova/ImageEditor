#pragma once
#ifndef IMAGEEDITOR_CORE_TYPES_H
#define IMAGEEDITOR_CORE_TYPES_H
#include <memory>
#include <vector>
#include <Core/Gears/Injector.h>

namespace ImageEditor::Core
{
	struct IFilter;
	using IFilterPtr = std::shared_ptr<IFilter>;
	using IFilterPtrArr = std::vector<IFilterPtr>;

	struct IImage;
	using IImagePtr = std::shared_ptr<IImage>;

	using IFilterInjector = boost::di::injector<IFilterPtr>;
	using IImageinjector = boost::di::injector<IImagePtr>;
	
}
#endif //IMAGEEDITOR_CORE_TYPES_H