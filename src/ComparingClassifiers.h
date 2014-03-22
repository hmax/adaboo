#pragma once
#include "image.hpp"
#include <ostream>
template<typename T> class AbstractWeakClassifier{
	public:
		virtual ~AbstractWeakClassifier() {};
		virtual unsigned char classify(const T& object) const = 0;
};

enum class COMPARISON_OPERATION{
	LESS, WITHIN_5, WITHIN_10, WITHIN_25, WITHIN_50
};

template<typename T> class ComparingWeakClassifier: public AbstractWeakClassifier<T>{
	private:
		size_t xi, xj, yi, yj;
		COMPARISON_OPERATION operation;
	public:
		~ComparingWeakClassifier() {};
		explicit ComparingWeakClassifier(const size_t xi, const size_t xj, const size_t yi, const size_t yj, COMPARISON_OPERATION operation);
		unsigned char classify(const T& object) const;
		bool operator==(const ComparingWeakClassifier<T> &rhs) const;
		friend std::ostream& operator<< (std::ostream& stream, const ComparingWeakClassifier<T>& wc){
				stream << "ComparingClassifier(" << wc.xi << ", " << wc.xj << ", " << wc.yi << ", " << wc.yj << ", " << static_cast<int>(wc.operation) << ")";
				return stream;
		};
};

typedef ComparingWeakClassifier<TImage> TWeakClassifier;
