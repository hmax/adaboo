#pragma once

#include <vector>
#include <utility>
#include <memory>
#include "image.hpp"
#include "weak_classifiers.hpp"

using std::pair;
using std::vector;


typedef pair<TImage, unsigned char> TTrainSample;
typedef vector<TTrainSample> TTrainSet;

template <typename T> class AdaBooster{
	vector<std::shared_ptr<AbstractWeakClassifier<T>>> classifiers;
	vector<double> errors;
public:
	AdaBooster();
	void train(vector<std::shared_ptr<AbstractWeakClassifier<T>>> weak_classifiers, TTrainSet train_set, int number_of_classifiers);
	unsigned char classify(T object);
	void forget();
};

#include "AdaBooster_impl.hpp"

typedef AdaBooster<TImage> TAdaBooster;