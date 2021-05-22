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

	public:
		template<typename T> struct bgra;

		typedef bgra<uchar> ucbgra;
		typedef bgra<int> ibgra;
		typedef bgra<float> fbgra;
		typedef bgra<float> dbgra;

		struct bgra_ref
		{
			bgra_ref(uchar& ib, uchar& ig, uchar& ir, uchar& ia);
			
			void update(const int ib, const int ig, const int ir);
			void update(const int ib, const int ig, const int ir, const int ia);
			template<class T> void updateBGRA(const bgra<T>& color)
			{
				update(color.b, color.g, color.r, color.a);
			}
			template<class T> void updateBGR(const bgra<T>& color)
			{
				update(color.b, color.g, color.r);
			}
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

		template<typename T> struct bgra
		{
			bgra() {}

			template<typename C> bgra(const bgra<C>& color)
				: b(color.b), g(color.g), r(color.r), a(color.a)
			{}

			bgra(const T ib, const  T ig, const  T ir, const  T ia)
				: b(ib), g(ig), r(ir), a(ia)
			{}

			bgra& operator+=(const T val)
			{
				b += val;
				g += val;
				r += val;
				a += val;
				return *this;
			}

			bgra& operator*=(const T val)
			{
				b *= val;
				g *= val;
				r *= val;
				a *= val;
				return *this;
			}

			bgra& operator+=(const bgra color)
			{
				b += color.b;
				g += color.g;
				r += color.r;
				a += color.a;
				return *this;
			}
			T b = 0;
			T g = 0;
			T r = 0;
			T a = 0;
		};
	protected:
		virtual void Transform(BGRAMatrix& image) const = 0;

	};

	template<typename T> inline FilterBase::bgra<T> operator * (FilterBase::bgra_ref const& c, const T val)
	{
		return FilterBase::bgra<T>(c.b * val, c.g * val, c.r * val, c.a * val);
	}

	template<typename T> inline FilterBase::bgra<T> operator * (FilterBase::bgra<T> const& c, const float val)
	{
		return FilterBase::bgra<T>(c.b * val, c.g * val, c.r * val, c.a * val);
	}

	template<typename T> inline FilterBase::bgra<T> operator / (FilterBase::bgra_ref const& c, const T val)
	{
		UNI_ENSURE_RETURN(val != 0, FilterBase::bgra<T>());
		return FilterBase::bgra<T>(c.b / val, c.g / val, c.r / val, c.a / val);
	}
}

#endif // IMAGEEDITOR_CORE_FILTERBASE_FILTERS_H
