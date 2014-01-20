/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "FunctionCoeffCosh.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(doofit::roofit::functions::FunctionCoeffCosh)

namespace doofit {
namespace roofit {
namespace functions {

FunctionCoeffCosh::FunctionCoeffCosh(const char *name, const char *title,
                                     RooAbsReal& _par_tag_omega,
                                     RooAbsReal& _par_tag_meaneta,
                                     RooAbsReal& _par_tag_delta_p0,
                                     RooAbsReal& _par_tag_delta_p1,
                                     RooAbsReal& _par_tag_eta,
                                     RooAbsReal& _par_prod_asym,
                                     RooAbsCategory& _cat_tag) :
  RooAbsReal(name,title),
  par_tag_omega("par_tag_omega","par_tag_omega",this,_par_tag_omega),
  par_tag_meaneta("par_tag_meaneta","par_tag_meaneta",this,_par_tag_meaneta),
  par_tag_delta_p0("par_tag_delta_p0","par_tag_delta_p0",this,_par_tag_delta_p0),
  par_tag_delta_p1("par_tag_delta_p1","par_tag_delta_p1",this,_par_tag_delta_p1),
  par_tag_eta("par_tag_eta","par_tag_eta",this,_par_tag_eta),
  par_prod_asym("par_prod_asym","par_prod_asym",this,_par_prod_asym),
  cat_tag("cat_tag","cat_tag",this,_cat_tag)
  {
  }

  
FunctionCoeffCosh::FunctionCoeffCosh(const FunctionCoeffCosh& other, const char* name) :
  RooAbsReal(other,name),
  par_tag_omega("par_tag_omega",this,other.par_tag_omega),
  par_tag_meaneta("par_tag_meaneta",this,other.par_tag_meaneta),
  par_tag_delta_p0("par_tag_delta_p0",this,other.par_tag_delta_p0),
  par_tag_delta_p1("par_tag_delta_p1",this,other.par_tag_delta_p1),
  par_tag_eta("par_tag_eta",this,other.par_tag_eta),
  par_prod_asym("par_prod_asym",this,other.par_prod_asym),
  cat_tag("cat_tag",this,other.cat_tag)
 {
 } 

Int_t FunctionCoeffCosh::getAnalyticalIntegral(RooArgSet& allVars,
                                                     RooArgSet& analVars, const char* rangeName) const
{
#ifdef FUNCTIONS_COUNT_CALLS
    std::printf("FunctionCoeffCosh::getAnalyticalIntegral(): In %s line %u (%s): allVars = ",
                __func__, __LINE__, __FILE__);
    //  analVars.Print();
    allVars.Print();
#endif
    
    //if (matchArgs(allVars, analVars, cat_tag)) return 1;
    
    return 0;
}
  
  Int_t FunctionCoeffCosh::getAnalyticalIntegralWN(RooArgSet& allVars, RooArgSet& analVars, const RooArgSet* normSet, const char* rangeName) const
{
#ifdef FUNCTIONS_COUNT_CALLS
    std::printf("FunctionCoeffCosh::getAnalyticalIntegralWN(): In %s line %u (%s): allVars = ",
                __func__, __LINE__, __FILE__);
    //analVars.Print();
    allVars.Print();
    if (normSet) normSet->Print();
    if (rangeName) std::cout << "rangeName: " << rangeName << std::endl;
#endif
    
    //if (matchArgs(allVars, analVars, cat_tag)) return 1;
    
    return 0;
}
} // namespace functions
} // namespace roofit
} // namespace doofit
