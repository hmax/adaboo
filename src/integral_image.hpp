// This is some weak implementation that gives NO type-level safety guarantees :( I have no idea for now how to implement such a guarantee

#include "image.hpp"

template <typename T> Image<uint64_t> integral_image(const Image<T>& img){
	Image<uint64_t> resulting_image(img);

	for (size_t x = 1; x < img.width(); ++x)
		resulting_image.at(x, 0) = resulting_image.at(x - 1, 0);

	for (size_t y = 1; y < img.height(); ++y)
		resulting_image.at(0, y) = resulting_image.at(0, y - 1);

	for (size_t x = 1; x < img.width(); ++x)
		for (size_t y = 1; y < img.height(); ++y)
			resulting_image.at(x, y) = resulting_image.at(x, y) + resulting_image.at(x, y - 1) + resulting_image.at(x - 1, y) - resulting_image.at(x - 1, y - 1);
	
	return resulting_image;
}