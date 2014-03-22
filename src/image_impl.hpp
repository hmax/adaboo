#include "image.hpp"
#include <cstring>
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
	memcpy(this->data, data, width*height);
}

template <typename T> Image<T>::Image(const Image<T>& img)
{
	this->data = new T[img.width * img.height];
	this->width = img.width;
	this->height = img.height;
	memcpy(this->data, img.data, width*height);
}

template<typename T> Image<T>& Image<T>::operator=( const Image<T>& rhs ) {
	if (this != &rhs){
		T* new_data = new T[rhs.width * rhs.height];
		memcpy(this->data, rhs.data, rhs.width*rhs.height);

		delete[] this->data;

		this->width = rhs.width;
		this->height = rhs.height;
		this->data = new_data;
	};
	return *this;
}
template <typename T> T& Image<T>::at(size_t x, size_t y) const
{
	return this->data[this->width * y + x];
}

template <typename T> Image<T>::~Image(void)
{
	delete[] data;
}

template class Image<std::uint8_t>;
