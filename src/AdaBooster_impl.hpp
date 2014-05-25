#pragma once

#include "AdaBooster.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <limits>
#include <cmath>

template <typename T> AdaBooster<T>::AdaBooster() : classifiers(), errors(){
}

template <typename T> void AdaBooster<T>::train(vector<std::shared_ptr<AbstractWeakClassifier<T>>> weak_classifiers, TrainSet<T> train_set, int number_of_classifiers){
	vector<double> sample_weights(train_set.size());
	size_t female_samples = 0;
	size_t male_samples = 0;

	for(const auto sample : train_set){
		if(sample.second == 0)
			male_samples++;
		else
			female_samples++;
	}

	for (auto i = 0; i < sample_weights.size(); ++i){
		if(train_set.at(i).second == 0)
			sample_weights.at(i) = 0.5 / male_samples;
		else
			sample_weights.at(i) = 0.5 / female_samples;
	}


	//Actual AdaBoost adaptation from paper
	for(auto classifier_number = 0; classifier_number < number_of_classifiers; ++classifier_number){
		auto weight_norm = 0.0;

		weight_norm = std::accumulate(sample_weights.begin(), sample_weights.end(), 0.0);
		
		for (auto& weight : sample_weights){
			weight = weight / weight_norm;
		}

		// Find weak classifier with least error
		double error = std::numeric_limits<double>::max();
		auto classifier = *weak_classifiers.begin(); // We're copying a shared_ptr here, feels ewie
		for(auto weak_classifier_it = weak_classifiers.cbegin(); weak_classifier_it != weak_classifiers.cend(); ++weak_classifier_it){
			auto classifier_error = 0.0;
			auto sample = train_set.cbegin();
			auto sample_weight = sample_weights.cbegin();
			
			for (int classsification_result; sample != train_set.cend() && sample_weight != sample_weights.cend(); ++sample, ++sample_weight){
				classsification_result = (*weak_classifier_it)->classify(sample->first);
				classifier_error += *sample_weight * (classsification_result ^ sample->second);  // Since classes are 0 and 1 we can use xor and multiplication to not confuse branch prediction here
			}

			if(classifier_error < error){
				classifier = *weak_classifier_it;
				error = classifier_error;
			}
		}

		classifiers.push_back(classifier);
		errors.push_back(error);
		
		// Reweight samples
		auto b = error / (1 - error);
		auto sample_weight = sample_weights.begin();
		auto sample = train_set.cbegin();

		for (; sample != train_set.cend() && sample_weight != sample_weights.end();	++sample, ++sample_weight){
			if(classifier->classify(sample->first) == sample->second)
				*sample_weight = (*sample_weight) * b;
		}
	}
}

template <typename T> unsigned char AdaBooster<T>::classify(T object){
	auto error_it = this->errors.cbegin();
	auto classifier_it = this->classifiers.cbegin();
	
	auto sum = 0.0;
	for(; error_it != this->errors.end() && classifier_it != this->classifiers.end(); ++error_it, ++classifier_it){
		auto b = (*error_it) / (1 - *error_it);
		auto object_class = (*classifier_it)->classify(object);
		sum += (0.5 - object_class) * log(b);
	}

	if(sum >= 0.0)
		return 1;
	else
		return 0;

}

template <typename T> void AdaBooster<T>::forget(){
	this->classifiers.clear();
}
