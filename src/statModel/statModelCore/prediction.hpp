#ifndef STATMODELS_PREDICTION_HPP
#define STATMODELS_PREDICTION_HPP
#include<chaoWangCppUtil/chaoWangCppUtil.hpp>

namespace statModel{
class Prediction{
	public:
		Prediction()=default;
		Prediction(const double &f);
		Prediction(const double &f,const double &s);
		Prediction(const double &f,const double &l, const double &h);
		double value;
		double low;
		double high;
		double se;
};

using PredictionVec = std::vector<Prediction>;

};
#endif
