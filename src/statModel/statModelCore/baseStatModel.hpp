#ifndef BASE_STAT_MODEL_HPP
#define BASE_STAT_MODEL_HPP

#include<chaoWangCppUtil/chaoWangCppUtil.hpp>
#include "prediction.hpp"
#include "generalData.hpp"

namespace statModel{
class BaseStatModel 
{
	friend std::ostream & operator<< (std::ostream &, const BaseStatModel &);
	friend std::istream & operator>> (std::istream &, BaseStatModel &);
public:
	BaseStatModel();
	BaseStatModel(const std::string & i);
	virtual ~BaseStatModel()=default;
  
	// add or delete data to estimate the models
	std::size_t addData(const GeneralData &); // add data to the model and update the parameters
	std::size_t deleteData(const GeneralData&); // delete data to the model and update the parameters
	std::size_t deleteData(const std::size_t&); //delete the first n data in the model
	
	PredictionVec predict(const GeneralData&gd=GeneralData()) const; // predict the values given by the data
	
	std::ostream & print(std::ostream &s=std::cout) const;
	std::istream & load(std::istream &s=std::cin);
	
	arma::vec	getParameters() const;
	void setParameters(const arma::vec &prmtrs);

	//clear (or reset) all data in the model.
	void clear();
	
	////simulate based on the current assigned parameters.
	GeneralData simulate(const std::size_t &n, const arma::vec &p, const unsigned &sd);

	std::string getID() const;
	std::size_t getNPrmtr() const;
	std::size_t getNObs() const;

	arma::mat getPrmtrCovMat() const; 
	arma::vec getPrmtrSD() const;

protected:
	virtual std::size_t doAddData(const GeneralData &) = 0;
	virtual std::size_t doDeleteData(const GeneralData&);
	virtual std::size_t doDeleteData(const std::size_t&);
	virtual PredictionVec doPredict(const GeneralData&gd=GeneralData()) const;
	virtual void doSetParameters(const arma::vec &prmtrs);
	
	virtual std::string doGetID() const;
	virtual std::size_t doGetNObs() const;
	virtual std::size_t doGetNPrmtr() const;

	virtual arma::vec doGetParameters() const;
	virtual arma::mat doGetPrmtrCovMat() const; 
	virtual arma::vec doGetPrmtrSD() const;

	virtual std::ostream & doPrint(std::ostream &s=std::cout) const;
	virtual std::istream & doLoad(std::istream &s=std::cin);
	void doClear();
	virtual GeneralData doSimulate(const std::size_t &n, const arma::vec &p, const unsigned &sd);
	
	std::string id;
	std::size_t nObs;
	std::size_t nPrmtr;

	std::map<std::string,arma::mat> data;

	arma::vec parameters;
	std::map<std::string,arma::vec> prmtrDict;
	arma::mat prmtrCovMat;
	private:
};

std::ostream & operator<< (std::ostream &, const BaseStatModel &);
std::istream & operator>> (std::istream &, BaseStatModel &);

}; //namespace statModel
#endif
