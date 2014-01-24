/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "FunctionTaggingCalib.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(doofit::roofit::functions::FunctionTaggingCalib)

namespace doofit {
namespace roofit {
namespace functions {

FunctionTaggingCalib::FunctionTaggingCalib() :
  tagging_asymmetries(false),
  tagging_combination(false),
  type_tag(kBdType)
  {
  }
  
FunctionTaggingCalib::FunctionTaggingCalib(const char *name, const char *title,
                                           RooAbsCategory& _cat_tag,
                                           RooAbsReal& _par_tag_eta,
                                           RooAbsReal& _par_tag_p0,
                                           RooAbsReal& _par_tag_p1,
                                           RooAbsReal& _par_tag_meaneta) :
  RooAbsReal(name,title),
  cat_tag("cat_tag","cat_tag",this,_cat_tag),
  par_tag_eta("par_tag_eta","par_tag_eta",this,_par_tag_eta),
  par_tag_p0("par_tag_p0","par_tag_p0",this,_par_tag_p0),
  par_tag_p1("par_tag_p1","par_tag_p1",this,_par_tag_p1),
  par_tag_meaneta("par_tag_meaneta","par_tag_meaneta",this,_par_tag_meaneta),
  tagging_asymmetries(false),
  tagging_combination(false),
  type_tag(kBdType)
  {
  }

FunctionTaggingCalib::FunctionTaggingCalib(const char *name, const char *title,
                                           RooAbsCategory& _cat_tag,
                                           RooAbsReal& _par_tag_eta,
                                           RooAbsReal& _par_tag_p0,
                                           RooAbsReal& _par_tag_p1,
                                           RooAbsReal& _par_tag_delta_p0,
                                           RooAbsReal& _par_tag_delta_p1,
                                           RooAbsReal& _par_tag_meaneta) :
  RooAbsReal(name,title),
  cat_tag("cat_tag","cat_tag",this,_cat_tag),
  par_tag_eta("par_tag_eta","par_tag_eta",this,_par_tag_eta),
  par_tag_p0("par_tag_p0","par_tag_p0",this,_par_tag_p0),
  par_tag_p1("par_tag_p1","par_tag_p1",this,_par_tag_p1),
  par_tag_delta_p0("par_tag_delta_p0","par_tag_delta_p0",this,_par_tag_delta_p0),
  par_tag_delta_p1("par_tag_delta_p1","par_tag_delta_p1",this,_par_tag_delta_p1),
  par_tag_meaneta("par_tag_meaneta","par_tag_meaneta",this,_par_tag_meaneta),
  tagging_asymmetries(true),
  tagging_combination(false),
  type_tag(kBdType)
  {
  }
  
FunctionTaggingCalib::FunctionTaggingCalib(const char *name, const char *title,
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
  par_tag_eta_SS("par_tag_eta_SS","par_tag_eta_SS",this,_par_tag_eta_SS),
  tagging_asymmetries(false),
  tagging_combination(true),
  type_tag(kBdType)
  {
  }

FunctionTaggingCalib::FunctionTaggingCalib(const char *name, const char *title,
                                           RooAbsCategory& _cat_tag_OS,
                                           RooAbsReal& _par_tag_p0_OS,
                                           RooAbsReal& _par_tag_p1_OS,
                                           RooAbsReal& _par_tag_meaneta_OS,
                                           RooAbsReal& _par_tag_eta_OS,
                                           RooAbsReal& _par_tag_delta_p0_OS,
                                           RooAbsReal& _par_tag_delta_p1_OS,
                                           RooAbsCategory& _cat_tag_SS,
                                           RooAbsReal& _par_tag_p0_SS,
                                           RooAbsReal& _par_tag_p1_SS,
                                           RooAbsReal& _par_tag_meaneta_SS,
                                           RooAbsReal& _par_tag_eta_SS,
                                           RooAbsReal& _par_tag_delta_p0_SS,
                                           RooAbsReal& _par_tag_delta_p1_SS,
                                           TagType _type_tag) :
  RooAbsReal(name,title),
  cat_tag_OS("cat_tag_OS","cat_tag_OS",this,_cat_tag_OS),
  par_tag_p0_OS("par_tag_p0_OS","par_tag_p0_OS",this,_par_tag_p0_OS),
  par_tag_p1_OS("par_tag_p1_OS","par_tag_p1_OS",this,_par_tag_p1_OS),
  par_tag_meaneta_OS("par_tag_meaneta_OS","par_tag_meaneta_OS",this,_par_tag_meaneta_OS),
  par_tag_eta_OS("par_tag_eta_OS","par_tag_eta_OS",this,_par_tag_eta_OS),
  par_tag_delta_p0_OS("par_tag_delta_p0_OS","par_tag_delta_p0_OS",this,_par_tag_delta_p0_OS),
  par_tag_delta_p1_OS("par_tag_delta_p1_OS","par_tag_delta_p1_OS",this,_par_tag_delta_p1_OS),
  cat_tag_SS("cat_tag_SS","cat_tag_SS",this,_cat_tag_SS),
  par_tag_p0_SS("par_tag_p0_SS","par_tag_p0_SS",this,_par_tag_p0_SS),
  par_tag_p1_SS("par_tag_p1_SS","par_tag_p1_SS",this,_par_tag_p1_SS),
  par_tag_meaneta_SS("par_tag_meaneta_SS","par_tag_meaneta_SS",this,_par_tag_meaneta_SS),
  par_tag_eta_SS("par_tag_eta_SS","par_tag_eta_SS",this,_par_tag_eta_SS),
  par_tag_delta_p0_SS("par_tag_delta_p0_SS","par_tag_delta_p0_SS",this,_par_tag_delta_p0_SS),
  par_tag_delta_p1_SS("par_tag_delta_p1_SS","par_tag_delta_p1_SS",this,_par_tag_delta_p1_SS),
  type_tag(_type_tag),
  tagging_asymmetries(true),
  tagging_combination(true)
  {
  }
  
FunctionTaggingCalib::FunctionTaggingCalib(const FunctionTaggingCalib& other, const char* name) :
  RooAbsReal(other,name),
  cat_tag_OS("cat_tag_OS",this,other.cat_tag_OS),
  par_tag_p0_OS("par_tag_p0_OS",this,other.par_tag_p0_OS),
  par_tag_p1_OS("par_tag_p1_OS",this,other.par_tag_p1_OS),
  par_tag_meaneta_OS("par_tag_meaneta_OS",this,other.par_tag_meaneta_OS),
  par_tag_eta_OS("par_tag_eta_OS",this,other.par_tag_eta_OS),
  par_tag_delta_p0_OS("par_tag_delta_p0_OS",this,other.par_tag_delta_p0_OS),
  par_tag_delta_p1_OS("par_tag_delta_p1_OS",this,other.par_tag_delta_p1_OS),
  cat_tag_SS("cat_tag_SS",this,other.cat_tag_SS),
  par_tag_p0_SS("par_tag_p0_SS",this,other.par_tag_p0_SS),
  par_tag_p1_SS("par_tag_p1_SS",this,other.par_tag_p1_SS),
  par_tag_meaneta_SS("par_tag_meaneta_SS",this,other.par_tag_meaneta_SS),
  par_tag_eta_SS("par_tag_eta_SS",this,other.par_tag_eta_SS),
  par_tag_delta_p0_SS("par_tag_delta_p0_SS",this,other.par_tag_delta_p0_SS),
  par_tag_delta_p1_SS("par_tag_delta_p1_SS",this,other.par_tag_delta_p1_SS),
  cat_tag("cat_tag",this,other.cat_tag),
  par_tag_eta("par_tag_eta",this,other.par_tag_eta),
  par_tag_p0("par_tag_p0",this,other.par_tag_p0),
  par_tag_p1("par_tag_p1",this,other.par_tag_p1),
  par_tag_delta_p0("par_tag_delta_p0",this,other.par_tag_delta_p0),
  par_tag_delta_p1("par_tag_delta_p1",this,other.par_tag_delta_p1),
  par_tag_meaneta("par_tag_meaneta",this,other.par_tag_meaneta),
  type_tag(other.type_tag),
  tagging_asymmetries(other.tagging_asymmetries),
  tagging_combination(other.tagging_combination)
 {
 } 

Int_t FunctionTaggingCalib::getAnalyticalIntegral(RooArgSet& allVars,
                                                     RooArgSet& analVars, const char* rangeName) const
{
#ifdef FUNCTIONS_COUNT_CALLS
    std::printf("FunctionTaggingCalib::getAnalyticalIntegral(): In %s line %u (%s): allVars = ",
                __func__, __LINE__, __FILE__);
    //  analVars.Print();
    allVars.Print();
#endif
    
    //if (matchArgs(allVars, analVars, cat_tag)) return 1;
    
    return 0;
}
  
  Int_t FunctionTaggingCalib::getAnalyticalIntegralWN(RooArgSet& allVars, RooArgSet& analVars, const RooArgSet* normSet, const char* rangeName) const
{
#ifdef FUNCTIONS_COUNT_CALLS
    std::printf("FunctionTaggingCalib::getAnalyticalIntegralWN(): In %s line %u (%s): allVars = ",
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
