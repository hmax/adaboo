#include <vector>
#include <utility>
#include "Image.h"
#include "WeakClassifiers.h"

using std::pair;
using std::vector;

template <typename T> class AdaBooster{
	vector<TWeakClassifier> classifiers;
	vector<double> errors;
public:
	AdaBooster();
	void train(vector<TWeakClassifier> weak_classifiers, vector<pair<T, int> > train_set, int number_of_classifiers);
	bool classify(T object);
	void forget();
};

typedef AdaBooster<TImage> TAdaBooster;
