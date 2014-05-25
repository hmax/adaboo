#include "image.hpp"
#include <cstring>

template <typename T> Image<T>::Image(size_t width, size_t height, T* data) : data(new T[width * height]), m_width(width), m_height(height){
	memcpy(this->data, data, width*height);
}

template <typename T>
template <typename F> Image<T>::Image(const Image<F>& img) : data(new T[img.width() * img.height()]), m_width(img.width()), m_height(img.height()){
	memcpy(this->data, img.data, m_width*m_height);
}

template<typename T> Image<T>& Image<T>::operator=( const Image<T>& rhs ) {
	if (this != &rhs){
		T* new_data = new T[rhs.m_width * rhs.m_height];
		memcpy(this->data, rhs.data, rhs.m_width*rhs.m_height);
		delete[] this->data;

		this->m_width = rhs.m_width;
		this->m_height = rhs.m_height;
		this->data = new_data;
	};
	return *this;
}

template<typename T> Image<T>::Image(Image<T>&& other) : data(other.data), m_width(other.m_width), m_height(other.m_height){
	other.data = nullptr; 
	other.m_width = 0;
	other.m_height = 0;
}

template<typename T> Image<T>& Image<T>::operator= (const Image<T>&& rhs){
	if (this != &rhs){
		this->data = rhs.data;
		this->m_width = rhs.m_width;
		this->m_height = rhs.m_height;

		rhs.data = nullptr;
		rhs.m_width = 0;
		rhs.m_height = 0;
	}
	return *this;
}


template<typename T> T& Image<T>::at(size_t x, size_t y){
	return this->data[this->m_width * y + x];
}

template<typename T> T Image<T>::at(size_t x, size_t y) const{
	return this->data[this->m_width * y + x];
}

template <typename T> Image<T>::~Image(void){
	// Should I check for nullptr? Using default
	delete[] data;
}
