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
		virtual IImagePtr Apply(const IImagePtr image, const std::string& parameters) override final;
		virtual const std::string Description() const override = 0;

	protected: 
		struct bgra_ref
		{
			bgra_ref(uchar& ib, uchar& ig, uchar& ir, uchar& ia);
			
			void update(const int ib, const int ig, const int ir);
			void update(const int ib, const int ig, const int ir, const int ia);
			
			static uchar normalize(int val);

			uchar& b;
			uchar& g;
			uchar& r;
			uchar& a;

		};
	
		class BGRAMatrix
		{
		public:
			BGRAMatrix(const ByteArr& data,
				unsigned int width,
				unsigned int height,
				unsigned int bytes_per_line);

			FilterBase::bgra_ref GetPixel(const uint64_t x, const uint64_t y);
			unsigned int Height();
			unsigned int Width();
			ByteArr& Data();

		private:
			ByteArr data_;
			unsigned int width_;
			unsigned int height_;
			unsigned int bytes_per_line_;
		};

	protected:
		virtual void Transform(BGRAMatrix& image) const = 0;

	};
}

#endif // IMAGEEDITOR_CORE_FILTERBASE_FILTERS_H
