#pragma once
#include "image.hpp"
#include <ostream>
#include <functional>

template<typename T> class AbstractWeakClassifier{
	public:
		virtual ~AbstractWeakClassifier() {};
		virtual unsigned char classify(const T& object) const = 0;
};

enum class COMPARISON_OPERATION{
	LESS, WITHIN_5, WITHIN_10, WITHIN_25, WITHIN_50
};

template<class T> class ComparingWeakClassifier : public AbstractWeakClassifier<T>{
	public:
		~ComparingWeakClassifier() {};

		explicit ComparingWeakClassifier(const size_t xi, const size_t xj, const size_t yi, const size_t yj) : xi(xi), xj(xj), yi(yi), yj(yj) {};

		bool operator==(const ComparingWeakClassifier<T> &rhs) const;
		friend std::ostream& operator<< (std::ostream& stream, const ComparingWeakClassifier<T>& wc){
				stream << "ComparingClassifier(" << wc.xi << ", " << wc.xj << ", " << wc.yi << ", " << wc.yj << ", " << static_cast<int>(wc.operation) << ")";
				return stream;
		};
	protected:
		size_t xi, xj, yi, yj;
};

template<class T> class LessComparingWeakClassifier : public ComparingWeakClassifier<T>{
	public:
		explicit LessComparingWeakClassifier(const size_t xi, const size_t xj, const size_t yi, const size_t yj) : ComparingWeakClassifier<T>(xi, xj, yi, yj) {};
		unsigned char classify(const T& object) const{
			return object.at(this->xi, this->yi) < object.at(this->xj, this->yj);
		};
	};

template<class T> class RangeComparingWeakClassifier : public ComparingWeakClassifier<T>{
	public:
		explicit RangeComparingWeakClassifier(const size_t xi, const size_t xj, const size_t yi, const size_t yj, const typename T::value_type range) : range(range), ComparingWeakClassifier<T>(xi, xj, yi, yj) {};
		unsigned char classify(const T& object) const{
			return abs(object.at(this->xi, this->yi) - object.at(this->xj, this->yj)) < this->range;
		};
	private:
		typename T::value_type range;
	};

typedef AbstractWeakClassifier<TImage> TAbstractWeakClassifier;
typedef ComparingWeakClassifier<TImage> TWeakClassifier;
typedef LessComparingWeakClassifier<TImage> TLessClassifier;
typedef RangeComparingWeakClassifier<TImage> TWithinRangeClassifier;