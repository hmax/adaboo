#pragma once
#include <cstddef>
#include <cstdint>

template <typename T> class Image
{
		T* m_data;
		size_t m_width, m_height;
	public:
		using value_type = T;
		explicit Image(void) : m_data(nullptr), m_width(0), m_height(0) {};
		Image(Image&& other);

		Image(const Image<T>& img);
		template <typename F> explicit Image(const Image<F>& img);
		Image<T>& operator= (const Image<T>& rhs);
		Image<T>& operator= (const Image<T>&& rhs);
		Image(size_t width, size_t height, T* data);

		T& at(size_t x, size_t y);
		T at(size_t x, size_t y) const;
		size_t width() const { return this->m_width; };
		size_t height() const { return this->m_height; };
		T* data() const { T* tmp = new T[m_width * m_height]; std::copy(this->m_data, this->m_data + m_width*m_height, tmp); return tmp; };
		~Image(void);
};

#include "image_impl.hpp"
