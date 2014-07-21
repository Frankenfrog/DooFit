/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "PowerLaw.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(doofit::roofit::functions::PowerLaw) 

namespace doofit {
namespace roofit {
namespace functions {

 PowerLaw::PowerLaw(const std::string name, 
                        RooAbsReal& _x_,
                        RooAbsReal& _alpha_,
                        RooAbsReal& _gamma_) :
   RooAbsReal(name.c_str(),name.c_str()), 
   x_("x_","x_",this,_x_),
   alpha_("alpha_","alpha_",this,_alpha_),
   gamma_("gamma_","gamma_",this,_gamma_)
 { 
 } 


 PowerLaw::PowerLaw(const PowerLaw& other, const char* name) :  
   RooAbsReal(other,name), 
   x_("x_",this,other.x_),
   alpha_("alpha_",this,other.alpha_),
   gamma_("gamma_",this,other.gamma_)
 { 
 } 



 Double_t PowerLaw::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   return alpha_ * TMath::Power(x_, gamma_) ; 
 } 



 Int_t PowerLaw::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
 { 
   // LIST HERE OVER WHICH VARIABLES ANALYTICAL INTEGRATION IS SUPPORTED, 
   // ASSIGN A NUMERIC CODE FOR EACH SUPPORTED (SET OF) PARAMETERS 
   // THE EXAMPLE BELOW ASSIGNS CODE 1 TO INTEGRATION OVER VARIABLE X
   // YOU CAN ALSO IMPLEMENT MORE THAN ONE ANALYTICAL INTEGRAL BY REPEATING THE matchArgs 
   // EXPRESSION MULTIPLE TIMES

   // if (matchArgs(allVars,analVars,x)) return 1 ; 
   return 0 ; 
 } 



 Double_t PowerLaw::analyticalIntegral(Int_t code, const char* rangeName) const  
 { 
   // RETURN ANALYTICAL INTEGRAL DEFINED BY RETURN CODE ASSIGNED BY getAnalyticalIntegral
   // THE MEMBER FUNCTION x.min(rangeName) AND x.max(rangeName) WILL RETURN THE INTEGRATION
   // BOUNDARIES FOR EACH OBSERVABLE x

   // assert(code==1) ; 
   // return (x.max(rangeName)-x.min(rangeName)) ; 
   return 0 ; 
 } 

}
}
}

