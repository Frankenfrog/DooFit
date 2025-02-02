/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "CombinationOfUncalibratedMistags.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(doofit::roofit::functions::CombinationOfUncalibratedMistags)

namespace doofit {
namespace roofit {
namespace functions {
 
CombinationOfUncalibratedMistags::CombinationOfUncalibratedMistags(const char *name, const char *title,
                                           RooAbsCategory& _cat_tag_OS,
                                           RooAbsReal& _par_tag_p0_OS,
                                           RooAbsReal& _par_tag_p1_OS,
                                           RooAbsReal& _par_tag_meaneta_OS,
                                           RooAbsReal& _par_tag_eta_OS,
                                           RooAbsCategory& _cat_tag_SS,
                                           RooAbsReal& _par_tag_p0_SS,
                                           RooAbsReal& _par_tag_p1_SS,
                                           RooAbsReal& _par_tag_meaneta_SS,
                                           RooAbsReal& _par_tag_eta_SS) :
  RooAbsReal(name,title),
  cat_tag_OS("cat_tag_OS","cat_tag_OS",this,_cat_tag_OS),
  par_tag_p0_OS("par_tag_p0_OS","par_tag_p0_OS",this,_par_tag_p0_OS),
  par_tag_p1_OS("par_tag_p1_OS","par_tag_p1_OS",this,_par_tag_p1_OS),
  par_tag_meaneta_OS("par_tag_meaneta_OS","par_tag_meaneta_OS",this,_par_tag_meaneta_OS),
  par_tag_eta_OS("par_tag_eta_OS","par_tag_eta_OS",this,_par_tag_eta_OS),
  cat_tag_SS("cat_tag_SS","cat_tag_SS",this,_cat_tag_SS),
  par_tag_p0_SS("par_tag_p0_SS","par_tag_p0_SS",this,_par_tag_p0_SS),
  par_tag_p1_SS("par_tag_p1_SS","par_tag_p1_SS",this,_par_tag_p1_SS),
  par_tag_meaneta_SS("par_tag_meaneta_SS","par_tag_meaneta_SS",this,_par_tag_meaneta_SS),
  par_tag_eta_SS("par_tag_eta_SS","par_tag_eta_SS",this,_par_tag_eta_SS)
  {
  }
  
CombinationOfUncalibratedMistags::CombinationOfUncalibratedMistags(const CombinationOfUncalibratedMistags& other, const char* name) :
  RooAbsReal(other,name),
  cat_tag_OS("cat_tag_OS",this,other.cat_tag_OS),
  par_tag_p0_OS("par_tag_p0_OS",this,other.par_tag_p0_OS),
  par_tag_p1_OS("par_tag_p1_OS",this,other.par_tag_p1_OS),
  par_tag_meaneta_OS("par_tag_meaneta_OS",this,other.par_tag_meaneta_OS),
  par_tag_eta_OS("par_tag_eta_OS",this,other.par_tag_eta_OS),
  cat_tag_SS("cat_tag_SS",this,other.cat_tag_SS),
  par_tag_p0_SS("par_tag_p0_SS",this,other.par_tag_p0_SS),
  par_tag_p1_SS("par_tag_p1_SS",this,other.par_tag_p1_SS),
  par_tag_meaneta_SS("par_tag_meaneta_SS",this,other.par_tag_meaneta_SS),
  par_tag_eta_SS("par_tag_eta_SS",this,other.par_tag_eta_SS)
 {
 } 

Int_t CombinationOfUncalibratedMistags::getAnalyticalIntegral(RooArgSet& allVars,
                                                     RooArgSet& analVars, const char* rangeName) const
{
#ifdef FUNCTIONS_COUNT_CALLS
    std::printf("CombinationOfUncalibratedMistags::getAnalyticalIntegral(): In %s line %u (%s): allVars = ",
                __func__, __LINE__, __FILE__);
    //  analVars.Print();
    allVars.Print();
#endif
    
    //if (matchArgs(allVars, analVars, cat_tag)) return 1;
    
    return 0;
}
  
  Int_t CombinationOfUncalibratedMistags::getAnalyticalIntegralWN(RooArgSet& allVars, RooArgSet& analVars, const RooArgSet* normSet, const char* rangeName) const
{
#ifdef FUNCTIONS_COUNT_CALLS
    std::printf("CombinationOfUncalibratedMistags::getAnalyticalIntegralWN(): In %s line %u (%s): allVars = ",
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
