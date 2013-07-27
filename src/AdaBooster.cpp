#include "AdaBooster.h"
#include <algorithm>
#include <numeric>

template <typename T> AdaBooster<T>::AdaBooster(){
}

template <typename T> void AdaBooster<T>::train(vector<TWeakClassifier> weak_classifiers, vector<pair<T, int> > train_set, int number_of_classifiers){
	vector<vector<double> > weights;
	size_t female_samples = 0;
	size_t male_samples = 0;

	for(const auto &sample : train_set){
		if(sample.second == 0)
			male_samples++;
		else
			female_samples++;
	}

	weights.reserve(number_of_classifiers);
	for(auto &w : weights)
		w.reserve(train_set.size());

	for(auto i = 0; i < weights.at(0).size(); ++i){
		if(train_set.at(i).second == 0)
			weights.at(0).at(i) = 0.5/male_samples;
		else
			weights.at(0).at(i) = 0.5/female_samples;
	}


	//Actual AdaBoost adaptation from paper
	for(auto classifier_number = 0; classifier_number < number_of_classifiers - 1; ++classifier_number){
		auto& iteration_weights = weights.at(classifier_number);
		auto weight_norm = 0.0;

		weight_norm = std::accumulate(iteration_weights.begin(), iteration_weights.end(), 0.0);
		
		for(auto& weight : iteration_weights){
			weight = weight / weight_norm;
		}

		// Find weak classifier with least error
		auto error = FLT_MAX;
		auto classifier = *(weak_classifiers.begin()); // TODO: There's a copy going on, check out ting about fixing
		for(auto& weak_classifier : weak_classifiers){
			auto classifier_error = 0.0;
			for(const auto& sample : train_set){
				classifier_error += abs(weak_classifier.classify(sample.first) - sample.second);
			}

			if(classifier_error < error){ // TODO: Check for floating point comparison handling
				classifier = weak_classifier;
			}
		}
		classifiers.push_back(classifier);
		errors.push_back(error);
		
		// Reweight samples
		auto b = error / (1 - error);

		auto& iteration_weight = iteration_weights.begin();
		auto& next_iteration_weight = weights.at(classifier_number + 1).begin();

		for (const auto& sample : train_set){
			if(classifier.classify(sample.first) == sample.second){
				*next_iteration_weight = *iteration_weight;
			}
			else{
				*next_iteration_weight = (*iteration_weight) * b;
			}
			iteration_weight++;
			next_iteration_weight++;
		}
	}

}

template <typename T> bool AdaBooster<T>::classify(T object){
	auto & error_it = this->errors.cbegin();
	auto & classifier_it = this->classifiers.cbegin();
	
	auto sum = 0.0;
	for(; error_it != this->errors.end() && classifier_it != this->classifiers.end(); ++error_it, ++classifier_it){
		auto b = (*error_it) / (1 - *error_it);
		sum = (0.5 - (*classifier_it).classify(object)) * log(b);
	}

	if(sum >= 0.0)
		return true;
	else
		return false;

}

template <typename T> void AdaBooster<T>::forget(){
	this->classifiers.clear();
}

template AdaBooster<TImage>;