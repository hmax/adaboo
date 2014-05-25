#pragma once
#include <cstddef>
#include <cstdint>

template <typename T> class Image
{
		T* data;
		size_t m_width, m_height;
	public:
		using value_type = T;
		
		Image() = delete;  // This constructor makes no sense for now

		template<typename F> explicit Image(const Image<F>& img);
		Image(Image&& other);
		
		Image<T>& operator= (const Image<T>& rhs);
		Image<T>& operator= (const Image<T>&& rhs);

		Image(size_t width, size_t height, T* data);
		
		T& at(size_t x, size_t y);
		T at(size_t x, size_t y) const;
		size_t width() const { return this->m_width; };
		size_t height() const { return this->m_height; };

		~Image(void);

};

#include "image_impl.hpp"
