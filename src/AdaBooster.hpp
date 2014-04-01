#pragma once

#include <vector>
#include <utility>
#include <memory>
#include "image.hpp"
#include "weak_classifiers.hpp"

using std::pair;
using std::vector;

template <typename T> using TrainSample = pair<T, unsigned char>;
template <typename T> using TrainSet = vector<TrainSample<T>>;

template <typename T> class AdaBooster{
	vector<std::shared_ptr<AbstractWeakClassifier<T>>> classifiers;
	vector<double> errors;
public:
	AdaBooster();
	void train(vector<std::shared_ptr<AbstractWeakClassifier<T>>> weak_classifiers, TrainSet<T> train_set, int number_of_classifiers);
	unsigned char classify(T object);
	void forget();
};

#include "AdaBooster_impl.hpp"
