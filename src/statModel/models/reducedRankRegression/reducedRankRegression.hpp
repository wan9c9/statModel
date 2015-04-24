#ifndef REDUCED_RANK_REGRESSION_HPP
#define REDUCED_RANK_REGRESSION_HPP

#include<chaoWangCppUtil/chaoWangCppUtil.hpp>

namespace statModel{
template<typename T> arma::vec softTresholdingOp(const arma::vec &x, T lambda);

arma::mat simpleReducedRankRegression(
		const arma::mat &Y,
		const arma::mat &X,
		const unsigned &nRank
		);


class ReducedRankRegression::BaseStatModel
{
public:
	ReducedRankRegression(const std::size_t &maxRank=0, 
			const bool sparseSVD=false);
	virtual ~ReducedRankModel()=default;
protected:
	virtual std::size_t doAddData(const GeneralData &);
	virtual std::size_t doDeleteData(const GeneralData&);
	virtual std::size_t doDeleteData(const std::size_t&);
	virtual PredictionVec doPredict(const GeneralData&gd=GeneralData()) const = 0;

	virtual arma::vec doGetParameters() const;
	virtual std::size_t doGetNPrmtr() const;
	virtual std::ostream & doPrint(std::ostream &s=std::cout) const;
	
	virtual void doSetParameters(const arma::vec &prmtrs);
	virtual std::istream & doLoad(std::istream &s=std::cin);
	virtual void clear();
	virtual GeneralData doSimulate(const std::size_t &n, 
																	const arma::vec &p,
																	const unsigned &sd);


  arma::mat getCoefLayer(const unsigned &group, const unsigned &layer);
	void initialize();
	void estimate();
  void computeResiduals(const unsigned &layer);
  void recordLastCoef();
	void updateLayer(const unsigned &);
	void updateU(const unsigned &);
  
	std::double lambda, alpha, tol;
	std::size_t maxIter;
	std::size_t nRank, maxRank;
	std::size_t q, p, nGroup;
	arma::uvec nObsGroup;
	arma::field<arma::mat> Y, X, U, V, C, R, wgtU, wgtV;
	arma::field<arma::vec> d, wgtD;
};

}
#endif // REDUCED_RANK_REGRESSION_HPP
