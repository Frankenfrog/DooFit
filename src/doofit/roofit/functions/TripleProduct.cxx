/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "TripleProduct.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(doofit::roofit::functions::TripleProduct) 

namespace doofit {
namespace roofit {
namespace functions {

TripleProduct::TripleProduct(std::string name,
                                 RooAbsReal& _par_factor1,
                                 RooAbsReal& _par_factor2,
                                 RooAbsReal& _par_factor3) :
  RooAbsReal(name.c_str(),name.c_str()),
  par_factor1("par_factor1","par_factor1",this,_par_factor1),
  par_factor2("par_factor2","par_factor2",this,_par_factor2),
  par_factor3("par_factor3","par_factor3",this,_par_factor3),
  num_calls_(0)
  {
  }

TripleProduct::TripleProduct(const TripleProduct& other, const char* name) :
  RooAbsReal(other,name),
  par_factor1("par_factor1",this,other.par_factor1),
  par_factor2("par_factor2",this,other.par_factor2),
  par_factor3("par_factor3",this,other.par_factor3),
  num_calls_(other.num_calls_)
  {
  } 

Int_t TripleProduct::getAnalyticalIntegral(RooArgSet& allVars,RooArgSet& analVars, const char* rangeName) const
{
  std::printf("TripleProduct::getAnalyticalIntegral(): In %s line %u (%s): allVars = ",
              __func__, __LINE__, __FILE__);
  analVars.Print();
  allVars.Print();
  
  return 0;
}
} // namespace functions
} // namespace roofit
} // namespace doofit
