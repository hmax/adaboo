#include "WeakClassifiers.h"
#include "Image.h"

template<typename T> bool ComparingWeakClassifier<T>::classify(const T& object) const{
	return object.at(this->xi, this->yi) > object.at(this->xj, this->yj);
}

template<typename T> ComparingWeakClassifier<T>::ComparingWeakClassifier(const size_t xi, const size_t xj, const size_t yi, const size_t yj){
	this->xi = xi;
	this->xj = xj;
	this->yi = yi;
	this->yj = yj;
}

template ComparingWeakClassifier<TImage>;