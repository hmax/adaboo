#include <vector>
#include <istream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <memory>

#include "image.hpp"
#include "weak_classifiers.hpp"
#include "AdaBooster.hpp"

using std::vector;
using std::istream;
using std::ifstream;



using TImage = Image<std::uint8_t>;

typedef AbstractWeakClassifier<TImage> TAbstractWeakClassifier;
typedef ComparingWeakClassifier<TImage> TWeakClassifier;
typedef LessComparingWeakClassifier<TImage> TLessClassifier;
typedef RangeComparingWeakClassifier<TImage> TWithinRangeClassifier;
typedef AdaBooster<TImage> TAdaBooster;
typedef TrainSample<TImage> TTrainSample;
typedef TrainSet<TImage> TTrainSet;

TTrainSample read_image_from_stream(istream& images_stream, size_t width, size_t height);

int main(int argc, char * argv[]){
	std::cout.sync_with_stdio(false);

	if (argc != 3) {
		std::cout << "Usage: sex_identification number_of_weak_classifiers path_to_sample_data" << std::endl;
		return 1;
	}

	std::stringstream converter;
	int number_of_weak_classifiers;
	std::string samples_path(argv[2]);

	converter << argv[1];
	converter >> number_of_weak_classifiers;
	

	TAdaBooster boostah;
	vector<std::shared_ptr<TAbstractWeakClassifier>> weak_classifiers;

	// It does not care if there's no such path
	ifstream train_data_file(samples_path,  ifstream::binary);
	if(!train_data_file){
		std::cerr << "Can't open file " << samples_path << std::endl;
		exit(1);
	}

	size_t width = 0, height = 0;
	char* read_tmp = new char;
	train_data_file.read(read_tmp, 1);
	width = *read_tmp;
	train_data_file.read(read_tmp, 1);
	height = *read_tmp;
	delete read_tmp;

	weak_classifiers.reserve(width*width*height*height*5);

	for (size_t xi=0; xi < width; xi++)
		for (size_t xj = 0; xj < width; xj++)
			for (size_t yi = 0; yi < height; yi++)
				for (size_t yj = 0; yj < height; yj++){
					weak_classifiers.push_back(std::make_shared<TLessClassifier>(xi, xj, yi, yj));
					weak_classifiers.push_back(std::make_shared<TWithinRangeClassifier>(xi, xj, yi, yj, 5));
					weak_classifiers.push_back(std::make_shared<TWithinRangeClassifier>(xi, xj, yi, yj, 10));
					weak_classifiers.push_back(std::make_shared<TWithinRangeClassifier>(xi, xj, yi, yj, 25));
					weak_classifiers.push_back(std::make_shared<TWithinRangeClassifier>(xi, xj, yi, yj, 50));
				}

	TTrainSet train_set;

	while(!train_data_file.eof()){
		TTrainSample tmp = read_image_from_stream(train_data_file, width, height);
		train_set.push_back(tmp);
	}

	size_t half_size = train_set.size() * 0.8;
	TTrainSet train_partial_set(train_set.begin(), train_set.begin() + half_size);
	TTrainSet check_set(train_set.begin() + half_size, train_set.end());
	
	boostah.train(weak_classifiers, train_partial_set, number_of_weak_classifiers);
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
	unsigned char s = 0;
	char* image_data = new char[width * height];
	images_stream.read(image_data, width * height);
	images_stream.read((char*)&s, 1);
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
