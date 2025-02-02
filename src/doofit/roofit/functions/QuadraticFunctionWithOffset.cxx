/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "QuadraticFunctionWithOffset.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(doofit::roofit::functions::QuadraticFunctionWithOffset)

namespace doofit {
namespace roofit {
namespace functions {

long long QuadraticFunctionWithOffset::num_calls_evaluate_ = 0;
long long QuadraticFunctionWithOffset::num_calls_integral_ = 0;

 QuadraticFunctionWithOffset::QuadraticFunctionWithOffset(std::string name, 
                        RooAbsReal& _par_x,
                        RooAbsReal& _par_quadratic_term,
                        RooAbsReal& _par_linear_term,
                        RooAbsReal& _par_offset) :
   RooAbsReal(name.c_str(),name.c_str()), 
   par_x("par_x","par_x",this,_par_x),
   par_quadratic_term("par_quadratic_term","par_quadratic_term",this,_par_quadratic_term),
   par_linear_term("par_linear_term","par_linear_term",this,_par_linear_term),
   par_offset("par_offset","par_offset",this,_par_offset)
 {
 } 


 QuadraticFunctionWithOffset::QuadraticFunctionWithOffset(const QuadraticFunctionWithOffset& other, const char* name) :  
   RooAbsReal(other,name), 
   par_x("par_x",this,other.par_x),
   par_quadratic_term("par_quadratic_term",this,other.par_quadratic_term),
   par_linear_term("par_linear_term",this,other.par_linear_term),
   par_offset("par_offset",this,other.par_offset)
 {
 } 

Int_t QuadraticFunctionWithOffset::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const
{
  #ifdef FUNCTIONS_COUNT_CALLS
  std::printf("QuadraticFunctionWithOffset::getAnalyticalIntegral(): In %s line %u (%s): allVars = ",
              __func__, __LINE__, __FILE__);
//  analVars.Print();
  allVars.Print();
  #endif
  
  //if (matchArgs(allVars, analVars, cat_tag)) return 1;
  
  return 0;
}

Int_t QuadraticFunctionWithOffset::getAnalyticalIntegralWN(RooArgSet& allVars, RooArgSet& analVars, const RooArgSet* normSet, const char* rangeName) const
{
  #ifdef FUNCTIONS_COUNT_CALLS
  std::printf("QuadraticFunctionWithOffset::getAnalyticalIntegralWN(): In %s line %u (%s): allVars = ",
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
