#include"reducedRankRegression.hpp"
#include<mlpack/methods/lars/lars.hpp>


using mlpack::regression::LARS;

template<typename T>
arma::vec softTresholdingOp(const arma::vec &x, T lambda)
{
	arma::vec val = arma::abs(x)-lambda;
	val.elem(arma::find(val <0)).zeros();
	val *= sign(x);
	return val;
}


arma::mat simpleReducedRankRegression(const arma::mat &Y,
		const arma::mat &X,
		const unsigned &nRank
		){
	arma::mat xtx = X.t()*X;
	arma::mat xty = X.t()*Y;
	arma::mat beta = arma::solve(xtx,xty);
	arma::mat tmp = xty.t()*beta;
	arma::mat U,V;
	arma::vec s;
	arma::svd(U,s,V,tmp);
	arma::mat C = U.cols(0,nRank-1)*U.cols(0,nRank-1).t();
	C = beta*C;
	return C;
}

void ReducedRankRegression:: initialize()
{
	for(unsigned i=0;i<nGroup;++i)
	{
		C(i) = simpleReducedRankRegression(Y(i),X(i),nRank);
	  arma::svd(U(i),d(i),V(i),C(i));
	}
}


void ReducedRankRegression:: estimate()
{
	initialize();
	double dif = 1000;
	std::size_t counter=0;
	while(dif > tol &&  counter < maxIter)
	{                    
		auto lastC = C;
		for(unsigned r = 0; i<nRank;++i)
		{
			updateLayer(r);
		}
	
		double dif1 = 0;
		double dif2 = 0;

		for(unsigned g=0; g<nGroup;++g)
		{
			dif1 += arma::norm(C(i)-lastC(i),"fro");
			dif2 += arma::norm(lastC(i),"fro");
		}
		dif = dif1/dif2;
	}
}


//void ReducedRankRegression::setCoef()
//{
//	C(i) = arma::zeros<arma::mat>(p,q);
// for(unsigned i=0;i<nGroup;++i)
	
//	for(unsigned j=0;j<nRank;++j)
//			C(i) += d(i)(j)*U(i).col(j)*V(i).col(j).t();
//	}
//}
		


void ReducedRankRegression::computeResiduals(const unsigned &layer)
{
  for(unsigned i=0;i<nGroup;++i)
	{
		R(i) = Y(i) - X(i)*C(i);
	}
}

arma::mat ReducedRankRegression::getCoefLayer(const unsigned &group, const unsigned &layer)
{
	return d(group)(layer)*U(group).col(layer)*V(group).col(layer).t();
}

void ReducedRankRegression::updateCoef(
		const bool &left,
		const unsigned &g,
		const unsigned &l,
		const double &newd,
		const arma::vec &beta)
{
	if(left) //update left singular vector: U
	{
		C(g) += (newd*beta - d(g)(layer)*U(g).col(l))*V(g).col(l).t();
		d(g)(l) = newd;
		U(g).col(l) = beta;
	}
	else //update right singular vector: V
	{
		C(g) += U(g).col(l)*(newd*beta - d(g)(layer)*V(g).col(l)).t();
		d(g)(l) = newd;
		V(g).col(l) = beta;
	}
}


void ReducedRankRegression::updateLayer(const unsigned &layer)
{
	updateU(layer);
	updateV(layer);
}


void ReducedRankRegression::updateU(const unsigned &layer)
{
	for(unsigned g=0;g<nGroup;++g)
	{
		updateU(g,layer);
	}
}
	

void ReducedRankRegression::updateV(const unsigned &layer)
{	
  for(unsigned g=0;g<nGroup;++g)
	{
		updateV(g,layer);
	}
}
	



void ReducedRankRegression::updateLayer(const unsigned &layer)
{
	updateU(layer);
	updateV(layer);
}

void ReducedRankRegression::updateU(const unsigned &g, const unsigned &layer)
{
		auto partialR = R(g) + X(g)*getCoefLayer(g,layer);
		arma::vec tmpY = vectorise(partialR);
		arma::mat tmpX = arma::kron(V(g).col(layer),X(g)*arma::diagmat(1.0/wgtU(g,layer));
		tmpY /= sqrt(nObsGroup(g));
		tmpX /= sqrt(nObsGroup(g));
    auto tmpLambda = lambda*wgtD(g)(layer)
			               *arma::norm(wgtV(g).col(layer)%V(g).col(layer),1);
		LARS lars(true,tmpLambda,0);
		arma::vec tmpBeta = d(g)(layer)*wgtU(g).col(layer)%U(g).col(layer);
		lars.Regress(tmpX, tmpY, tmpBeta);

		auto beta = lars.BetaPath().back();
		beta /= wgtU(g).col(layer);

		auto newd = arma::norm(beta,2);
		beta /= newd;
		updateCoef(true, g,l,newd,beta);
}

void ReducedRankRegression::updateV(const unsigned &g, const unsigned &layer)
{
    auto partialR = R(g) + X(g)*getCoefLayer(g,layer);
		arma::vec tmpY = vectorise(partialR);
		arma::mat tmpX = arma::kron(arma::eye(q),X(g)*U(g).col(layer));
		tmpY /= sqrt(nObsGroup(g));
		tmpX /= sqrt(nObsGroup(g));

    double tmpLambda1 =lambda*wgtD(g)(layer)
			               *arma::norm(wgtU(g).col(layer)%U(g).col(layer),1);
    double tmpLambda2 = alpha;
		arma::vec tmpBeta0 = V(1-g).col(layer);
		arma::mat tmpD = d(g)(layer)*wgtV(g).col(layer);

    //check if $tmpBeta0 is a solution.
		auto tmpV = tmpX.t()*tmpY - tmpX.t()*(tmpX*tmpBeta0);
	  auto idxI = arma::find(tmpBeta0 == 0);
	  auto idxIc = arma::find(tmpBeta0 != 0);

		auto criterion = arma::sum(
				arma::square(tmpD.elem(idxI)%
					           softTresholdingOp(tmpV.elem(idxI),tmpLambda1)
										 )
				);
		criterion += arma::sum(
				arma::square(tmpD.elem(idxI)%
					(tmpV.elem(idxIc) - tmpLambda1*sign(tmpBeta(idxIc)))
					)
				);
		if(criterion < tmpLambda2*tmpLambda2)
		{
			auto newV = V(1-g).col(layer)%tmpD;
			auto newD = arma::norm(newV,2);
			newV /= newD;
			updateCoef(false,g,l,newD,newV);
		}
		else
		{
			auto difV = arma::norm(V(g).col(g) - V(g).col(1-g),2);
			auto c = sqrt(2*tmpLambda2/difV);

			tmpY = arma::join_cols(tmpY, c*tmpBeta0);
			tmpX = arma::join_cols(tmpX, c*arma::diagmat(1/tmpD));
			
			LARS lars(true,tmpLambda1,0);
			arma::vec tmpBeta = d(g)(layer)*wgtV(g).col(layer)%V(g).col(layer);
			lars.Regress(tmpX, tmpY, tmpBeta);
			
			auto newV = lars.BetaPath().back();
			newV %= tmpD;
			auto newD = arma::norm(newD,2);
			newV /= newD;
			updateCoef(true, g,l,newD,newV);
		}
}











	


	


		
		
	
	








