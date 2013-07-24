#pragma once
#include <cstdint>

template <typename T> class Image
{
	T* data;
	size_t width, height;
public:
	explicit Image(void);
	Image(size_t width, size_t height, T* data);
	T& at(size_t x, size_t y) const;
	~Image(void);
};

typedef Image<std::uint8_t> TImage;
