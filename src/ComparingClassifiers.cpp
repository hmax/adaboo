#include "WeakClassifiers.h"
#include "image.hpp"

template<typename T> unsigned char ComparingWeakClassifier<T>::classify(const T& object) const{
	if(operation == COMPARISON_OPERATION::LESS){
		if(object.at(this->xi, this->yi) < object.at(this->xj, this->yj))
			return 1;
		else
			return 0;
	}else if(operation == COMPARISON_OPERATION::WITHIN_5){
		if(abs(object.at(this->xi, this->yi) - object.at(this->xj, this->yj)) < 5)
			return 1;
		else
			return 0;
	}else if(operation == COMPARISON_OPERATION::WITHIN_10){
		if(abs(object.at(this->xi, this->yi) - object.at(this->xj, this->yj)) < 10)
			return 1;
		else
			return 0;
	}else if(operation == COMPARISON_OPERATION::WITHIN_25){
		if(abs(object.at(this->xi, this->yi) - object.at(this->xj, this->yj)) < 25)
			return 1;
		else
			return 0;
	}else if(operation == COMPARISON_OPERATION::WITHIN_50){
		if(abs(object.at(this->xi, this->yi) - object.at(this->xj, this->yj)) < 50)
			return 1;
		else
			return 0;
	}else{
		exit(1);
	}
}

template<typename T> ComparingWeakClassifier<T>::ComparingWeakClassifier(const size_t xi, const size_t xj, const size_t yi, const size_t yj, COMPARISON_OPERATION operation){
	this->xi = xi;
	this->xj = xj;
	this->yi = yi;
	this->yj = yj;
	this->operation = operation;
};

template<typename T> bool ComparingWeakClassifier<T>::operator==(const ComparingWeakClassifier<T> &rhs) const{
	return (xi == rhs.xi) && (xj == rhs.xj) && (yi == rhs.yi) && (yj == rhs.yj) && (operation == rhs.operation);
};


template class ComparingWeakClassifier<TImage>;
