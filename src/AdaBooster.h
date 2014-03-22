#include <vector>
#include <utility>
#include "image.hpp"
#include "WeakClassifiers.h"

using std::pair;
using std::vector;


typedef pair<TImage, unsigned char> TTrainSample;
typedef vector<TTrainSample> TTrainSet;

template <typename T> class AdaBooster{
	vector<TWeakClassifier> classifiers;
	vector<double> errors;
public:
	AdaBooster();
	void train(vector<TWeakClassifier> weak_classifiers, TTrainSet train_set, int number_of_classifiers);
	unsigned char classify(T object);
	void forget();
};

typedef AdaBooster<TImage> TAdaBooster;