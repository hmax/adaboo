#pragma once
#include <cstddef>
#include <cstdint>

template <typename T> class Image
{
		T* data;
		size_t width, height;
	public:
		using value_type = T;
		explicit Image(void);
		Image(const Image<T>& img);
		Image<T>& operator= (const Image<T>& rhs);
		Image(size_t width, size_t height, T* data);
		T& at(size_t x, size_t y) const;
		~Image(void);
};

#include "image_impl.hpp"
