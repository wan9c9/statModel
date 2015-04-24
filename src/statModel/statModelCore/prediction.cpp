#include "prediction.hpp"

namespace statModel{

Prediction::Prediction(const double &f):
  value(f),low(setNan()),high(setNan()),se(setNan())
{
}

Prediction::Prediction(const double &f,const double &s):
  value(f),low(setNan()),high(setNan()),se(s)
{
}

Prediction::Prediction(const double &f,const double &l, const double &h):
  value(f),low(l),high(h),se(setNan())
{
}

};
