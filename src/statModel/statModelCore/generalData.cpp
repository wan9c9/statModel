#include "generalData.hpp"
#include<chaoWangCppUtil/chaoWangCppUtil.hpp>

namespace statModel{

void deleteNotFiniteRows(GeneralData &gd,const unsigned &researchIndex)
{
  if(gd.empty())
    return;
  LOGGER_TRACE << "Deleting not finite rows in general data";
  //need to check all has the same number of rows
  const auto b = gd.begin();
  const auto e = gd.end();
  const auto n = b->second.n_rows;
  //std::cout << b->first << ", nobs=" << n << std::endl;

  auto i = b;
  while(++i != e)
  {
    //std::cout << i->first << ", nobs=" << i->second.n_rows << std::endl;
    if(n != i->second.n_rows)
      throw(std::runtime_error("arguments provided to deleteNotFiniteRows doesn't have the same number of rows!"));
  }
  //std::cout << "detecting from index " << researchIndex << std::endl;

  for(std::size_t idx=researchIndex; idx<n; ++idx)
  {
    //LOGGER_TRACE << n << " " << idx;
    auto m = b;
    //std::cout << m->first << " shape " << m->second.n_rows << " , " << m->second.n_cols << std::endl;
    //std::cout << idx << std::endl;
    while( m != e )
    {
      //m->second.print("matrix:");
      if(!arma::is_finite(m->second.row(idx)))
      {
        LOGGER_DEBUG << "DeletingNotFiniteRows: nan values is found in " << m->first << " at row " << idx;
        for(auto j=b;j!=e;++j)
          j->second.shed_row(idx);
        deleteNotFiniteRows(gd,idx);
        return;
      }
      ++m;
    }
  }
  LOGGER_TRACE << "deleteNotFiniteRows. Done";
  return;
}

};

