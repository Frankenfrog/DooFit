/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef FUNCTIONATANINCLUDINGBETA
#define FUNCTIONATANINCLUDINGBETA

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TMath.h"

//#define FUNCTIONS_COUNT_CALLS

class FunctionAtanIncludingBeta : public RooAbsReal {
public:
  FunctionAtanIncludingBeta() {} ; 
  FunctionAtanIncludingBeta(const char *name, const char *title,
	      RooAbsReal& _par_x,
	      RooAbsReal& _par_slope_a,
	      RooAbsReal& _par_slope_b,
	      RooAbsReal& _par_beta);
  FunctionAtanIncludingBeta(const FunctionAtanIncludingBeta& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new FunctionAtanIncludingBeta(*this,newname); }
  inline virtual ~FunctionAtanIncludingBeta() {
    #ifdef FUNCTIONS_COUNT_CALLS
    std::cout << "FunctionAtanIncludingBeta::~FunctionAtanIncludingBeta(): # evaluate calls: " << num_calls_evaluate_ << std::endl;
    std::cout << "FunctionAtanIncludingBeta::~FunctionAtanIncludingBeta(): # integral calls: " << num_calls_integral_ << std::endl;
    #endif
  }

protected:

  RooRealProxy par_x ;
  RooRealProxy par_slope_a ;
  RooRealProxy par_slope_b ;
  RooRealProxy par_beta ;
  
  static long long num_calls_evaluate_;
  static long long num_calls_integral_;
  
  inline Double_t evaluate() const {
    #ifdef FUNCTIONS_COUNT_CALLS
    ++num_calls_evaluate_;
    #endif
    // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE
    
//    std::cout << (TMath::ATan(par_x*exp(par_slope_a*par_x+par_slope_b)))*(1-par_beta*par_x)/1.570796327 << std::endl;
    
    return (TMath::ATan(par_x*exp(par_slope_a*par_x+par_slope_b)))*(1-par_beta*par_x)/1.570796327;
  }
  
  virtual Int_t	getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars,
                                      const char* rangeName = 0) const;
  
  virtual Int_t	getAnalyticalIntegralWN(RooArgSet& allVars, RooArgSet& analVars, const RooArgSet* normSet, const char* rangeName = 0) const;

private:

  ClassDef(FunctionAtanIncludingBeta,1) // Your description goes here...
};
 
#endif
