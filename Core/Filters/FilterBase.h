#pragma once
#ifndef IMAGEEDITOR_CORE_FILTERBASE_FILTERS_H
#define IMAGEEDITOR_CORE_FILTERBASE_FILTERS_H
#include <Core/Filters/IFilter.h>

namespace ImageEditor::Core
{
	class FilterBase: public virtual IFilter
	{
	public:
		FilterBase();
		FilterBase(const FilterBase&) = delete;
		FilterBase& operator= (const FilterBase&) = delete;
	
	public: // IFilter
		virtual IImagePtr Apply(const IImagePtr image, const std::string& parameters) const override final;
		virtual const std::string Description() const override = 0;

	protected: 
		struct bgra
		{
			bgra();
			bgra(int b, int g, int r, int a);
			
			uchar b = 0;
			uchar g = 0;
			uchar r = 0;
			uchar a = 0;

		};
		using bgraMatrix = std::vector<std::vector<bgra>>;
	
	protected:
		virtual void Transform(bgraMatrix& image) const = 0;

	private:
		bgraMatrix ConvertToRgb(const IImagePtr& image) const;
		IImagePtr ConvertToIImage(const bgraMatrix& image, unsigned int bytes_per_line, unsigned int format) const;
	};
}

#endif // IMAGEEDITOR_CORE_FILTERBASE_FILTERS_H
