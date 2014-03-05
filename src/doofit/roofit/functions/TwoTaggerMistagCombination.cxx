/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "TwoTaggerMistagCombination.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(doofit::roofit::functions::TwoTaggerMistagCombination) 

namespace doofit {
namespace roofit {
namespace functions {

 TwoTaggerMistagCombination::TwoTaggerMistagCombination(const char *name, const char *title, 
                        RooAbsReal& _eta_one_,
                        RooAbsReal& _eta_two_,
                        RooAbsCategory& _tag_one_,
                        RooAbsCategory& _tag_two_) :
   RooAbsReal(name,title), 
   eta_one_("eta_one_","eta_one_",this,_eta_one_),
   eta_two_("eta_two_","eta_two_",this,_eta_two_),
   tag_one_("tag_one_","tag_one_",this,_tag_one_),
   tag_two_("tag_two_","tag_two_",this,_tag_two_)
 { 
 } 


 TwoTaggerMistagCombination::TwoTaggerMistagCombination(const TwoTaggerMistagCombination& other, const char* name) :  
   RooAbsReal(other,name), 
   eta_one_("eta_one_",this,other.eta_one_),
   eta_two_("eta_two_",this,other.eta_two_),
   tag_one_("tag_one_",this,other.tag_one_),
   tag_two_("tag_two_",this,other.tag_two_)
 { 
 } 



 Double_t TwoTaggerMistagCombination::evaluate() const 
 { 
   // mistag combination: the Grabalosa way 
   // https://cds.cern.ch/record/1456804/files/CERN-THESIS-2012-075.pdf
   // note that the probability e.g. to have a b-tagged meson corresponds to a Bbar-Meson, so tag=-1

   // probability to have a b-tagged meson
   double p_b = ( ( ( 1 + tag_one_ ) / 2 ) - tag_one_ * ( 1 - eta_one_ ) ) * ( ( ( 1 + tag_two_ ) / 2 ) - tag_two_ * ( 1 - eta_two_ ) );
   // probability to have a bbar-tagged meson
   double p_bbar = ( ( ( 1 - tag_one_ ) / 2 ) + tag_one_ * ( 1 - eta_one_ ) ) * ( ( ( 1 - tag_two_ ) / 2 ) + tag_two_ * ( 1 - eta_two_ ) );

   // as the combined eta will be the one associated with the larger probability for a b / bbar quark:
   double eta_combined = 1. - ( std::max(p_b, p_bbar) / (p_b + p_bbar) );

   return eta_combined; 
 } 



 Int_t TwoTaggerMistagCombination::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
 { 
   // LIST HERE OVER WHICH VARIABLES ANALYTICAL INTEGRATION IS SUPPORTED, 
   // ASSIGN A NUMERIC CODE FOR EACH SUPPORTED (SET OF) PARAMETERS 
   // THE EXAMPLE BELOW ASSIGNS CODE 1 TO INTEGRATION OVER VARIABLE X
   // YOU CAN ALSO IMPLEMENT MORE THAN ONE ANALYTICAL INTEGRAL BY REPEATING THE matchArgs 
   // EXPRESSION MULTIPLE TIMES

   // if (matchArgs(allVars,analVars,x)) return 1 ; 
   return 0 ; 
 } 



 Double_t TwoTaggerMistagCombination::analyticalIntegral(Int_t code, const char* rangeName) const  
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


