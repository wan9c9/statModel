#ifndef STATMODELS_GENERALDATA_HPP
#define STATMODELS_GENERALDATA_HPP

namespace statModel{
typedef std::map<std::string, arma::mat> GeneralData;

void deleteNotFiniteRows(GeneralData &gd, const unsigned &researchIndex=0);

}; //namespace statModel
#endif
