#include "WeakClassifiers.h"
#include "image.hpp"

template<typename T> bool ComparingWeakClassifier<T>::operator==(const ComparingWeakClassifier<T> &rhs) const{
	return (xi == rhs.xi) && (xj == rhs.xj) && (yi == rhs.yi) && (yj == rhs.yj) && (operation == rhs.operation);
};


template class ComparingWeakClassifier<TImage>;
