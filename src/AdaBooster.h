#include <vector>

using std::vector;

template <typename T> class AdaBooster{
	vector<T> classifiers;
public:
	void train(vector<T> weak_classifiers, vector<T> train_set);
	bool classify(T object);
	void forget();
};