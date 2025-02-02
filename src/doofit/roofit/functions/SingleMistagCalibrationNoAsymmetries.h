/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef SINGLEMISTAGCALIBRATIONNOASYMMETRIES
#define SINGLEMISTAGCALIBRATIONNOASYMMETRIES

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
namespace doofit {
namespace roofit {
namespace functions {

class SingleMistagCalibrationNoAsymmetries : public RooAbsReal {
public:
  SingleMistagCalibrationNoAsymmetries() {} ; 
  SingleMistagCalibrationNoAsymmetries(std::string name,
	      RooAbsReal& _eta_,
	      RooAbsReal& _p0_,
	      RooAbsReal& _p1_,
	      RooAbsReal& _avg_eta_);
  SingleMistagCalibrationNoAsymmetries(const SingleMistagCalibrationNoAsymmetries& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new SingleMistagCalibrationNoAsymmetries(*this,newname); }
  inline virtual ~SingleMistagCalibrationNoAsymmetries() { }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:

  RooRealProxy eta_ ;
  RooRealProxy p0_ ;
  RooRealProxy p1_ ;
  RooRealProxy avg_eta_ ;
  
  Double_t evaluate() const ;

private:

  ClassDef(SingleMistagCalibrationNoAsymmetries,1) // Your description goes here...
};

}
}
}

#endif
