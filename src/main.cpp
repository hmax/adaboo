#include <vector>
#include <istream>
#include <fstream>
#include <iostream>
#include <cassert>

#include "image.hpp"
#include "WeakClassifiers.h"
#include "AdaBooster.h"

extern template class ComparingWeakClassifier<TImage>;
extern template class AdaBooster<TImage>;

using std::vector;
using std::istream;
using std::ifstream;

TTrainSample read_image_from_stream(istream& images_stream, size_t width, size_t height);

int main(){
	TAdaBooster boostah;
	vector<TWeakClassifier> weak_classifiers;
	std::cout.sync_with_stdio(false);
	ifstream file("D:\\Projects\\CV\\sex_identification\\data\\20x20\\samples00.vec",  ifstream::binary);

	size_t width = 0, height = 0;
	char* read_tmp = new char;
	file.read(read_tmp, 1);
	width = *read_tmp;
	file.read(read_tmp, 1);
	height = *read_tmp;
	delete read_tmp;

	weak_classifiers.reserve(width*width*height*height*5);

	for (auto xi=0; xi < width; xi++)
		for (auto xj=0; xj < width; xj++)
			for (auto yi=0; yi < height; yi++)
				for (auto yj=0; yj < height; yj++)
					weak_classifiers.push_back(TWeakClassifier(xi, xj, yi, yj, COMPARISON_OPERATION::LESS));
	for (auto xi=0; xi < width; xi++)
		for (auto xj=0; xj < width; xj++)
			for (auto yi=0; yi < height; yi++)
				for (auto yj=0; yj < height; yj++)
					weak_classifiers.push_back(TWeakClassifier(xi, xj, yi, yj, COMPARISON_OPERATION::WITHIN_5));
	for (auto xi=0; xi < width; xi++)
		for (auto xj=0; xj < width; xj++)
			for (auto yi=0; yi < height; yi++)
				for (auto yj=0; yj < height; yj++)
					weak_classifiers.push_back(TWeakClassifier(xi, xj, yi, yj, COMPARISON_OPERATION::WITHIN_10));
	for (auto xi=0; xi < width; xi++)
		for (auto xj=0; xj < width; xj++)
			for (auto yi=0; yi < height; yi++)
				for (auto yj=0; yj < height; yj++)
					weak_classifiers.push_back(TWeakClassifier(xi, xj, yi, yj, COMPARISON_OPERATION::WITHIN_25));
	for (auto xi=0; xi < width; xi++)
		for (auto xj=0; xj < width; xj++)
			for (auto yi=0; yi < height; yi++)
				for (auto yj=0; yj < height; yj++)
					weak_classifiers.push_back(TWeakClassifier(xi, xj, yi, yj, COMPARISON_OPERATION::WITHIN_50));

	TTrainSet train_set;

	while(!file.eof()){
		TTrainSample tmp = read_image_from_stream(file, width, height);
		train_set.push_back(tmp);
	}
	/*for(auto& sample : train_set){
		if(sample.second == 0)
			std::cout << "Female" << "\n";
		else if(sample.second == 1)
			std::cout << "Male" << "\n";
	}*/

	size_t half_size = train_set.size() * 0.8;
	TTrainSet train_partial_set(train_set.begin(), train_set.begin() + half_size);
	TTrainSet check_set(train_set.begin() + half_size, train_set.end());
	
	boostah.train(weak_classifiers, train_partial_set, 300);
	auto right_classified = 0, wrong_classified = 0;
	for(auto& sample : check_set){
		if(boostah.classify(sample.first) == sample.second){
			++right_classified;
		}else{
			++wrong_classified;
		}
	}
	boostah.forget();
	std::cout << "Right classification: " << right_classified << std::endl << "Wrong classification: " << wrong_classified << std::endl;
	std::cout << "Total samples: " << train_set.size() << std::endl;

}

TTrainSample read_image_from_stream(istream& images_stream, size_t width, size_t height){
	char s = 0;
	char* image_data = new char[width * height];
	images_stream.read(image_data, width * height);
	images_stream.read(&s, 1);
	if(s == 255)
		s = 0;
	TImage read_image(width, height, (uint8_t*)image_data);
	auto result = std::make_pair(read_image, (unsigned char)s);
	return result;
}
// 1 byte: w
// 1 byte: h
// lots of fokken images
// w*h bytes: image
// 1 byte: sex (1 for male, 255 for female)
