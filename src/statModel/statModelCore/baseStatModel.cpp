#include "baseStatModel.hpp"

namespace statModel{

BaseStatModel::BaseStatModel():id("UNKNOWN"),nObs(0){}

BaseStatModel::BaseStatModel(const std::string & i):id(i), nObs(0){}

//void BaseStatModel::setParameters(const arma::vec &init){parameters = init;}


std::string BaseStatModel::getID() const
{
    return doGetID();
}

std::size_t BaseStatModel::getNPrmtr() const
{
    return doGetNPrmtr();
}

std::size_t BaseStatModel::getNObs() const 
{
	return doGetNObs();
}

std::size_t BaseStatModel::doGetNObs() const 
{
	return nObs;
}

arma::mat BaseStatModel::getPrmtrCovMat() const
{
  return doGetPrmtrCovMat();
}

arma::vec BaseStatModel::getPrmtrSD() const
{
  return doGetPrmtrSD();
}

arma::vec BaseStatModel::getParameters() const
{
    return doGetParameters();
}

std::size_t BaseStatModel::addData(const GeneralData&gd)
{
    doAddData(gd);
}

std::size_t BaseStatModel::doAddData(const GeneralData&gd)
{
	notImplementedError(getID()+__func__);
	return 0;
}

std::size_t BaseStatModel::deleteData(const GeneralData&gd)
{
    doDeleteData(gd);
}

std::size_t BaseStatModel::deleteData(const std::size_t & n)
{
    doDeleteData(n);
}

void BaseStatModel::setParameters(const arma::vec &prmtrs){
    doSetParameters(prmtrs);
}

PredictionVec BaseStatModel::predict(const GeneralData&gd) const
{
	return doPredict(gd);
}

GeneralData BaseStatModel::simulate(const std::size_t &n, const arma::vec &p, const unsigned &sd)
{
    doSimulate(n,p,sd);
}

void BaseStatModel::clear()
{
    doClear();
}

std::ostream & BaseStatModel::print(std::ostream &s) const
{
  return doPrint(s);
}

std::istream & BaseStatModel::load(std::istream &s)
{
    return doLoad(s);
}

std::string BaseStatModel::doGetID() const
{
  return id;
}


std::size_t BaseStatModel::doGetNPrmtr() const
{
  return nPrmtr;
}


arma::mat BaseStatModel::doGetPrmtrCovMat() const
{ 
  return prmtrCovMat;
}


arma::vec BaseStatModel::doGetParameters() const
{
  return parameters;
}

arma::vec BaseStatModel::doGetPrmtrSD() const
{
  return arma::sqrt(prmtrCovMat.diag());
}

std::size_t BaseStatModel::doDeleteData(const GeneralData&)
{
  std::stringstream ss;
  ss << "Method " << __func__ << " is not implemeted for " << getID();
  throw std::runtime_error(ss.str());  
}// delete data to the model and update the parameters



std::size_t BaseStatModel::doDeleteData(const std::size_t & n)
{
  std::stringstream ss;
  ss << "Method " << __func__ << " is not implemeted for " << getID();
  throw std::runtime_error(ss.str());  
}// delete data to the model and update the parameters




void BaseStatModel::doSetParameters(const arma::vec &prmtrs){
  parameters = prmtrs;
}

PredictionVec BaseStatModel::doPredict(const GeneralData&gd) const
{
	notImplementedError(__func__);
	return PredictionVec();
}


GeneralData BaseStatModel::doSimulate(const std::size_t &n, const arma::vec &p, const unsigned &sd)
{
  notImplementedError(__func__);
  return GeneralData();
}


void BaseStatModel::doClear(){
  nObs=0;
  parameters.clear();
  prmtrCovMat.clear();
}


std::ostream & operator<< (std::ostream &s, const BaseStatModel &m)
{
  m.print(s);
  return s;
}

std::istream & operator>> (std::istream &s, BaseStatModel &m)
{
  m.load(s);
  return s;
}

std::ostream & BaseStatModel::doPrint(std::ostream &s) const{
  s << id << std::endl;
  s << parameters << std::endl;
  return s;
}

std::istream & BaseStatModel::doLoad(std::istream &s){
  s >> id;
  for(auto &i: parameters)
    s >> i;
  return s;
}

}; //namespace statModel
