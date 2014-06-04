#include "image.hpp"
#include <cstring>

template <typename T> Image<T>::Image(size_t width, size_t height, T* data) : m_data(new T[width * height]), m_width(width), m_height(height){
	std::copy(this->m_data, this->m_data + width*height, data);
}

template <typename T>
template <typename F> Image<T>::Image(const Image<F>& img) : m_data(new T[img.width() * img.height()]), m_width(img.width()), m_height(img.height()){
	// TODO: Add check for narrowing
	std::copy(this->m_data, this->m_data + m_width * m_height, img.data());
}

template <typename T> Image<T>::Image(const Image<T>& img) : m_data(new T[img.width() * img.height()]), m_width(img.width()), m_height(img.height()){
	std::copy(this->m_data, this->m_data + m_width * m_height, img.data());
}


template<typename T> Image<T>& Image<T>::operator=( const Image<T>& rhs ) {
	if (this != &rhs){
		T* new_data = new T[rhs.width * rhs.height];
		memcpy(this->data, rhs.data, rhs.width*rhs.height);
		delete[] this->data;

		this->m_width = rhs.m_width;
		this->m_height = rhs.m_height;
		this->m_data = new_data;
	};
	return *this;
}


template<typename T> Image<T>::Image(Image<T>&& other) : m_data(other.m_data), m_width(other.m_width), m_height(other.m_height){
	other.m_data = nullptr; 
	other.m_width = 0;
	other.m_height = 0;
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


template<typename T> T& Image<T>::at(size_t x, size_t y){
	return this->m_data[this->m_width * y + x];
}

template<typename T> T Image<T>::at(size_t x, size_t y) const{
	return this->m_data[this->m_width * y + x];
}

template <typename T> Image<T>::~Image(void){
	// Should I check for nullptr? Using default
	delete[] m_data;
}
