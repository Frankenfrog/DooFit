/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef DOOFIT_ROOFIT_FUNCTIONS_CoshCoeffCombo
#define DOOFIT_ROOFIT_FUNCTIONS_CoshCoeffCombo

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

namespace doofit {
namespace roofit {
namespace functions {

class CoshCoeffCombo : public RooAbsReal {
public:
  CoshCoeffCombo() {};
  
  CoshCoeffCombo(std::string name,
                 RooAbsCategory& _cat_tag_OS,
                 RooAbsReal& _par_p0_OS,
                 RooAbsReal& _par_p1_OS,
                 RooAbsReal& _par_meaneta_OS,
                 RooAbsReal& _par_eta_OS,
                 RooAbsReal& _par_delta_p0_OS,
                 RooAbsReal& _par_delta_p1_OS,
                 RooAbsCategory& _cat_tag_SS,
                 RooAbsReal& _par_p0_SS,
                 RooAbsReal& _par_p1_SS,
                 RooAbsReal& _par_meaneta_SS,
                 RooAbsReal& _par_eta_SS,
                 RooAbsReal& _par_delta_p0_SS,
                 RooAbsReal& _par_delta_p1_SS,
                 RooAbsReal& _par_prod_asym);
  
  CoshCoeffCombo(const CoshCoeffCombo& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new CoshCoeffCombo(*this,newname); }
  inline virtual ~CoshCoeffCombo() {
    #ifdef FUNCTIONS_COUNT_CALLS
    std::cout << "CoshCoeffCombo::~CoshCoeffCombo(): # evaluate calls: " << num_calls_evaluate_ << std::endl;
    std::cout << "CoshCoeffCombo::~CoshCoeffCombo(): # integral calls: " << num_calls_integral_ << std::endl;
    #endif
  }

protected:

  RooCategoryProxy cat_tag_OS ;
  RooRealProxy par_p0_OS ;
  RooRealProxy par_p1_OS ;
  RooRealProxy par_meaneta_OS ;
  RooRealProxy par_eta_OS ;
  RooRealProxy par_delta_p0_OS ;
  RooRealProxy par_delta_p1_OS ;
  RooCategoryProxy cat_tag_SS ;
  RooRealProxy par_p0_SS ;
  RooRealProxy par_p1_SS ;
  RooRealProxy par_meaneta_SS ;
  RooRealProxy par_eta_SS ;
  RooRealProxy par_delta_p0_SS ;
  RooRealProxy par_delta_p1_SS ;
  RooRealProxy par_prod_asym ;
  
  static long long num_calls_evaluate_;
  static long long num_calls_integral_;
  
  inline Double_t evaluate() const {
    #ifdef FUNCTIONS_COUNT_CALLS
    ++num_calls_evaluate_;
    #endif
    Double_t  omega_OS_Bd  = par_eta_OS;
    Double_t  omega_OS_Bdb = par_eta_OS;
    Double_t  omega_SS_Bd  = par_eta_SS;
    Double_t  omega_SS_Bdb = par_eta_SS;
    Double_t  omega_Bd = par_eta_SS;
    Double_t  omega_Bdb = par_eta_SS;
    Int_t     tag = cat_tag_SS;

    if (par_eta_OS < 0.5)
    {
      if ((par_p0_OS + par_p1_OS*(par_eta_OS - par_meaneta_OS)) > 0.5)
      {
        omega_OS_Bd  = 0.5;
        omega_OS_Bdb = 0.5;
      }
      else {
        omega_OS_Bd  = par_p0_OS + 0.5*par_delta_p0_OS + (par_p1_OS + 0.5*par_delta_p1_OS)*(par_eta_OS - par_meaneta_OS);
        omega_OS_Bdb = par_p0_OS - 0.5*par_delta_p0_OS + (par_p1_OS - 0.5*par_delta_p1_OS)*(par_eta_OS - par_meaneta_OS);
      }
    }

    if (par_eta_SS < 0.5)
    {
      if ((par_p0_SS + par_p1_SS*(par_eta_SS - par_meaneta_SS)) > 0.5)
      {
        omega_SS_Bd  = 0.5;
        omega_SS_Bdb = 0.5;
      }
      else{
        omega_SS_Bd  = par_p0_SS + 0.5*par_delta_p0_SS + (par_p1_SS + 0.5*par_delta_p1_SS)*(par_eta_SS - par_meaneta_SS);
        omega_SS_Bdb = par_p0_SS - 0.5*par_delta_p0_SS + (par_p1_SS - 0.5*par_delta_p1_SS)*(par_eta_SS - par_meaneta_SS);
      }
    }
    
    if (cat_tag_OS == cat_tag_SS) {
      omega_Bd  = omega_OS_Bd*omega_SS_Bd/(omega_OS_Bd*omega_SS_Bd + (1.0 - omega_OS_Bd)*(1.0 - omega_SS_Bd));
      omega_Bdb = omega_OS_Bdb*omega_SS_Bdb/(omega_OS_Bdb*omega_SS_Bdb + (1.0 - omega_OS_Bdb)*(1.0 - omega_SS_Bdb));
    }
    else {
      if ((omega_SS_Bd + omega_SS_Bdb) >= (omega_OS_Bd + omega_OS_Bdb)) {
        omega_Bd = omega_OS_Bd*(1.0 - omega_SS_Bd)/(omega_OS_Bd*(1.0 - omega_SS_Bd) + (1.0 - omega_OS_Bd)*omega_SS_Bd);
        omega_Bdb = omega_OS_Bdb*(1.0 - omega_SS_Bdb)/(omega_OS_Bdb*(1.0 - omega_SS_Bdb) + (1.0 - omega_OS_Bdb)*omega_SS_Bdb);
        tag = cat_tag_OS;
      }
      else {
        omega_Bd = (1.0 - omega_OS_Bd)*omega_SS_Bd/(omega_OS_Bd*(1.0 - omega_SS_Bd) + (1.0 - omega_OS_Bd)*omega_SS_Bd);
        omega_Bdb = (1.0 - omega_OS_Bdb)*omega_SS_Bdb/(omega_OS_Bdb*(1.0 - omega_SS_Bdb) + (1.0 - omega_OS_Bdb)*omega_SS_Bdb);
      }
    }

    return 1.0 - tag*(omega_Bd - omega_Bdb) - tag*par_prod_asym*(1.0 - omega_Bd - omega_Bdb);
  }

  virtual Int_t	getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName = 0) const;
  
  virtual Int_t	getAnalyticalIntegralWN(RooArgSet& allVars, RooArgSet& analVars, const RooArgSet* normSet, const char* rangeName = 0) const;
  
  virtual Double_t analyticalIntegral(Int_t code, const char* rangeName = 0) const {
   
   // std::cout << "CoshCoeffCombo::analyticalIntegral(" << code << ", ...): Called." << std::endl;
    switch(code){
      case 0: return evaluate() ;

      case 3: return  2.0;

      case 2: return  2.0;

      case 1: return  4.0;

      default: assert(0);
    }

    return 0 ;
 }
  
private:

  ClassDef(CoshCoeffCombo,1) // Your description goes here...
};
} // namespace functions
} // namespace roofit
} // namespace doofit

#endif
