#pragma once
#include "Image.h"
template<typename T> class AbstractWeakClassifier{
	public:
		virtual ~AbstractWeakClassifier() {};
		virtual bool classify(const T& object) const = 0;
};

template<typename T> class ComparingWeakClassifier: public AbstractWeakClassifier<T>{
	private:
		size_t xi, xj, yi, yj;
	public:
		~ComparingWeakClassifier() {};
		explicit ComparingWeakClassifier(const size_t xi, const size_t xj, const size_t yi, const size_t yj);
		bool classify(const T& object) const;
};

typedef ComparingWeakClassifier<TImage> TWeakClassifier;
