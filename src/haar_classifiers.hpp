#include "weak_classifiers.hpp"

template<class T> class HaarLikeClassifier : public AbstractWeakClassifier<T>{
public:
	~ComparingWeakClassifier() {};

	explicit ComparingWeakClassifier(const size_t A, const size_t B, const size_t C, const size_t D) : A(A), B(B), C(C), D(D) {};
	unsigned char classify(const T& object) const{
		return object.at(this->xi, this->yi) < object.at(this->xj, this->yj);
	};
protected:
	size_t A, B, C, D;
};
