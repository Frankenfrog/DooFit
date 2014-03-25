/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef DOOFIT_ROOFIT_FUNCTIONS_SINCOEFFWITHTAGGINGCALIB
#define DOOFIT_ROOFIT_FUNCTIONS_SINCOEFFWITHTAGGINGCALIB

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

class SinCoeffWithTaggingCalib : public RooAbsReal {
public:
  enum CoeffType {
    kSType = -1,
    kCType = +1
  };
  
  SinCoeffWithTaggingCalib();
  
  SinCoeffWithTaggingCalib(std::string name,
                   RooAbsReal& _par_S,
                   RooAbsReal& _par_tag_p0,
                   RooAbsReal& _par_tag_p1,
                   RooAbsReal& _par_tag_meaneta,
                   RooAbsReal& _par_tag_eta,
                   RooAbsCategory& _cat_tag,
                   CoeffType type_coeff);
  
  SinCoeffWithTaggingCalib(const SinCoeffWithTaggingCalib& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new SinCoeffWithTaggingCalib(*this,newname); }
  inline virtual ~SinCoeffWithTaggingCalib() {
    #ifdef FUNCTIONS_COUNT_CALLS
    std::cout << "SinCoeffWithTaggingCalib::~SinCoeffWithTaggingCalib(): # evaluate calls: " << num_calls_evaluate_ << std::endl;
    std::cout << "SinCoeffWithTaggingCalib::~SinCoeffWithTaggingCalib(): # integral calls: " << num_calls_integral_ << std::endl;
    #endif
  }
  
protected:

  RooRealProxy par_S_ ;
  RooRealProxy par_tag_p1_ ;
  RooRealProxy par_tag_p0_ ;
  RooRealProxy par_tag_meaneta_ ;
  RooRealProxy par_tag_eta_ ;
  
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
    return type_coeff_*cat_tag_*(1.0 - 2.0*(par_tag_p1_*(par_tag_eta_-par_tag_meaneta_) + par_tag_p0_))*par_S_ ;
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
    if (1 == code) {
      //std::cout << "SinCoeffWithTaggingCalib::analyticalIntegral(" << code << ", ...): Called." << std::endl;
      return 0.0;
    }
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

  ClassDef(SinCoeffWithTaggingCalib,1) // Your description goes here...
};
} // namespace functions
} // namespace roofit
} // namespace doofit

#endif
