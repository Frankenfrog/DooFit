/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef DOOFIT_ROOFIT_FUNCTIONS_FUNCTIONCOEFFSIN2
#define DOOFIT_ROOFIT_FUNCTIONS_FUNCTIONCOEFFSIN2

// from STL
#include <string>

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

namespace doofit {
namespace roofit {
namespace functions {

class FunctionCoeffSin2 : public RooAbsReal {
public:
  enum CoeffType {
    kSType = -1,
    kCType = +1
  };
  
  FunctionCoeffSin2();
  FunctionCoeffSin2(const char *name, const char *title,
//                    RooAbsReal& _par_S,
                    RooAbsReal& _par_tag_p0,
                    RooAbsReal& _par_tag_p1,
                    RooAbsReal& _par_tag_meaneta,
                    RooAbsReal& _par_tag_delta_p0,
                    RooAbsReal& _par_tag_delta_p1,
                    RooAbsReal& _par_tag_eta,
                    RooAbsReal& _par_prod_asym,
                    RooAbsCategory& _cat_tag,
                    CoeffType type_coeff);
  FunctionCoeffSin2(const FunctionCoeffSin2& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new FunctionCoeffSin2(*this,newname); }
  inline virtual ~FunctionCoeffSin2() {
    #ifdef FUNCTIONS_COUNT_CALLS
    std::cout << "FunctionCoeffSin2::~FunctionCoeffSin2(): # evaluate calls: " << num_calls_evaluate_ << std::endl;
    std::cout << "FunctionCoeffSin2::~FunctionCoeffSin2(): # integral calls: " << num_calls_integral_ << std::endl;
    #endif
  }

protected:

//  RooRealProxy par_S ;
  RooRealProxy par_tag_p0 ;
  RooRealProxy par_tag_p1 ;
  RooRealProxy par_tag_meaneta ;
  RooRealProxy par_tag_delta_p0 ;
  RooRealProxy par_tag_delta_p1 ;
  RooRealProxy par_tag_eta ;
  RooRealProxy par_prod_asym ;
  RooCategoryProxy cat_tag ;
  const CoeffType type_coeff_ ;
  
  static long long num_calls_evaluate_;
  static long long num_calls_integral_;
  
  inline Double_t evaluate() const {
    #ifdef FUNCTIONS_COUNT_CALLS
    ++num_calls_evaluate_;
    #endif
    // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE
    
    //std::cout << -1.0*(cat_tag*(1.0 - 2.0*(par_tag_meaneta+par_tag_p0 + par_tag_p1*(par_tag_eta-par_tag_meaneta))) - par_prod_asym*(1.0 - cat_tag*(par_tag_delta_p0 + par_tag_delta_p1*(par_tag_eta-par_tag_meaneta))))*par_S << std::endl;
    
    return type_coeff_*(cat_tag*(1.0 - 2.0*(par_tag_meaneta+par_tag_p0 + par_tag_p1*(par_tag_eta-par_tag_meaneta))) - par_prod_asym*(1.0 - cat_tag*(par_tag_delta_p0 + par_tag_delta_p1*(par_tag_eta-par_tag_meaneta))));

  }

  virtual Int_t	getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars,
                                      const char* rangeName = 0) const;
  
  virtual Int_t	getAnalyticalIntegralWN(RooArgSet& allVars, RooArgSet& analVars, const RooArgSet* normSet, const char* rangeName = 0) const;
  
//  virtual Double_t analyticalIntegral(Int_t code, const char* rangeName = 0) const {
//    
//    if (1 == code) {
//      //std::cout << "FunctionCoeffSin2::analyticalIntegral(" << code << ", ...): Called." << std::endl;
//      return 0.0;
//    }
//    // must not get here
//    //assert(1 == 0);
//  }
  
private:

  ClassDef(FunctionCoeffSin2,1) // Your description goes here...
};
} // namespace functions
} // namespace roofit
} // namespace doofit

#endif
