#include "image.hpp"
#include <cstring>

template <typename T> Image<T>::Image(size_t width, size_t height, T* data) : data(new T[width * height]), width(width), height(height){
	memcpy(this->data, data, width*height);
}

template <typename T> Image<T>::Image(const Image<T>& img) : data(new T[img.width * img.height]), width(img.width), height(img.height){
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

template<typename T> Image<T>::Image(Image<T>&& other) : data(other.data), width(other.width), height(other.height){ 
	other.data = nullptr; 
	other.width = 0;
	other.height = 0;
}

template<typename T> Image<T>& Image<T>::operator= (const Image<T>&& rhs){
	if (this != &rhs){
		this->data = rhs.data;
		this->width = rhs.width;
		this->height = rhs.height;

		rhs.data = nullptr;
		rhs.width = 0;
		rhs.height = 0;
	}
	return *this;
}


template<typename T> T& Image<T>::at(size_t x, size_t y) const{
	return this->data[this->width * y + x];
}

template <typename T> Image<T>::~Image(void){
	// Should I check for nullptr? Using default
	delete[] data;
}
