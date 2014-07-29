/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef DOOFIT_ROOFIT_FUNCTIONS_SINCOEFFWITHPRODASYMM
#define DOOFIT_ROOFIT_FUNCTIONS_SINCOEFFWITHPRODASYMM

// from STL
#include <string>

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

//#define FUNCTIONS_COUNT_CALLS

namespace doofit {
namespace roofit {
namespace functions {

class SinCoeffWithProdAsymm : public RooAbsReal {
public:
  enum CoeffType {
    kSType = -1,
    kCType = +1
  };
  
  SinCoeffWithProdAsymm();
  
  SinCoeffWithProdAsymm(std::string name,
                   RooAbsReal& _par_S,
                   RooAbsReal& _par_omega_Bd,
                   RooAbsReal& _par_omega_Bdb,
                   RooAbsCategory& _cat_tag,
                   RooAbsReal& _par_prod_asym,
                   CoeffType type_coeff);
  
  SinCoeffWithProdAsymm(const SinCoeffWithProdAsymm& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new SinCoeffWithProdAsymm(*this,newname); }
  inline virtual ~SinCoeffWithProdAsymm() {
    #ifdef FUNCTIONS_COUNT_CALLS
    std::cout << "SinCoeffWithProdAsymm::~SinCoeffWithProdAsymm(): # evaluate calls: " << num_calls_evaluate_ << std::endl;
    std::cout << "SinCoeffWithProdAsymm::~SinCoeffWithProdAsymm(): # integral calls: " << num_calls_integral_ << std::endl;
    #endif
  }
  
protected:

  RooRealProxy par_S_ ;
  RooRealProxy par_omega_Bd_ ;
  RooRealProxy par_omega_Bdb_ ;
  RooRealProxy par_prod_asym_ ;

  RooCategoryProxy cat_tag_ ;
  
  const CoeffType type_coeff_ ;
  
  static long long num_calls_evaluate_ ;
  static long long num_calls_integral_ ;
  
  inline Double_t evaluate() const {
    #ifdef FUNCTIONS_COUNT_CALLS
    ++num_calls_evaluate_;
    #endif
    
    // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE
//    ++n_calls;
    return par_S_*type_coeff_*(cat_tag_*(1.0 - par_omega_Bd_ - par_omega_Bdb_) - par_prod_asym_*(1.0 - cat_tag_*(par_omega_Bd_ - par_omega_Bdb_))) ;
  }

  virtual Int_t	getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars,
                                      const char* rangeName = 0) const;
  
  virtual Int_t	getAnalyticalIntegralWN(RooArgSet& allVars, RooArgSet& analVars, const RooArgSet* normSet, const char* rangeName = 0) const;
  
  virtual Double_t analyticalIntegral(Int_t code, const char* rangeName = 0) const {
    #ifdef FUNCTIONS_COUNT_CALLS
    ++num_calls_integral_;
    #endif
    
    //++n_calls;
    //assert(0 != code);
    // if (1 == code) {
      //std::cout << "SinCoeffWithProdAsymm::analyticalIntegral(" << code << ", ...): Called." << std::endl;
      // return 0.0;
    // }
    // must not get here
    //assert(1 == 0);
  }
  
//  virtual Double_t getValV(const RooArgSet* nset=0) const {
//    if (nset!=NULL) {
//      nset->Print();
//      return RooAbsReal::getValV(nset);
//    }
//  }

private:

  ClassDef(SinCoeffWithProdAsymm,1) // Your description goes here...
};
} // namespace functions
} // namespace roofit
} // namespace doofit

#endif
