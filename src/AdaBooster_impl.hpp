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
	vector<vector<double> > weights(number_of_classifiers, vector<double>(train_set.size()));
	size_t female_samples = 0;
	size_t male_samples = 0;

	for(const auto sample : train_set){
		if(sample.second == 0)
			male_samples++;
		else
			female_samples++;
	}

	weights.reserve(number_of_classifiers);
	for(auto w : weights)
		w.reserve(train_set.size());

	for(auto i = 0; i < weights.at(0).size(); ++i){
		if(train_set.at(i).second == 0)
			weights.at(0).at(i) = 0.5/male_samples;
		else
			weights.at(0).at(i) = 0.5/female_samples;
	}


	//Actual AdaBoost adaptation from paper
	for(auto classifier_number = 0; classifier_number < number_of_classifiers - 1; ++classifier_number){
		auto iteration_weights = weights.at(classifier_number);
		auto weight_norm = 0.0;

		weight_norm = std::accumulate(iteration_weights.begin(), iteration_weights.end(), 0.0);
		
		for(auto& weight : iteration_weights){
			weight = weight / weight_norm;
		}

		// Find weak classifier with least error
		double error = std::numeric_limits<double>::max();
		auto classifier = *weak_classifiers.begin(); // We're copying a shared_ptr here, feels ewie
		for(auto weak_classifier_it = weak_classifiers.cbegin(); weak_classifier_it != weak_classifiers.cend(); ++weak_classifier_it){
			auto classifier_error = 0.0;
			auto sample = train_set.cbegin();
			auto sample_weight = iteration_weights.cbegin();
			
			for(; sample != train_set.cend() && sample_weight != iteration_weights.cend(); ++sample, ++sample_weight){
				int classsification_result = (*weak_classifier_it)->classify(sample->first);
				if(classsification_result != sample->second)
					classifier_error += *sample_weight;
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
		auto iteration_weight = iteration_weights.cbegin();
		auto next_iteration_weight = weights.at(classifier_number + 1).begin();
		auto sample = train_set.cbegin();

		for (; sample != train_set.cend() && iteration_weight != iteration_weights.cend() && next_iteration_weight != weights.at(classifier_number + 1).end();
			++sample, ++iteration_weight, ++next_iteration_weight){
			if(classifier->classify(sample->first) == sample->second){
				*next_iteration_weight = (*iteration_weight) * b;
			}
			else{
				*next_iteration_weight = *iteration_weight;
			}
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
