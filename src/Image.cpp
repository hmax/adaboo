#include "Image.h"

template <typename T> Image<T>::Image(void)
{
	this->data = nullptr;
	this->width = 0;
	this->height = 0;
}

template <typename T> Image<T>::Image(size_t width, size_t height, T* data)
{
	this->data = new T[width * height];
	this->width = width;
	this->height = height;
}

template <typename T> T& Image<T>::at(size_t x, size_t y) const
{
	return this->data[this->width * y + x];
}

template <typename T> Image<T>::~Image(void)
{
	delete[] data;
}

template Image<std::uint8_t>;