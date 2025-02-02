/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "RectangularPdf.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(doofit::roofit::pdfs::RectangularPdf) 

namespace doofit {
namespace roofit {
namespace pdfs {

 RectangularPdf::RectangularPdf(const std::string name, 
                        RooAbsReal& _x_,
                        double _range_min_,
                        double _range_max_) :
   RooAbsPdf(name.c_str(),name.c_str()), 
   x_("x_","x_",this,_x_),
   range_min_(_range_min_),
   range_max_(_range_max_)
 { 
 } 


 RectangularPdf::RectangularPdf(const RectangularPdf& other, const char* name) :  
   RooAbsPdf(other,name), 
   x_("x_",this,other.x_),
   range_min_(other.range_min_),
   range_max_(other.range_max_)
 { 
 } 



 Double_t RectangularPdf::evaluate() const 
 { 
   double val = 0;
   if ((x_ >= range_min_) && (x_ <= range_max_)){
      val = 1;
   }
   return val; 
 } 



 Int_t RectangularPdf::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
 { 
   // std::printf("In %s line %u (%s): allVars = ", __func__, __LINE__, __FILE__);
   if (matchArgs(allVars,analVars,x_)) return 1;
   // return 0 ; 
 } 



 Double_t RectangularPdf::analyticalIntegral(Int_t code, const char* rangeName) const  
 { 
   // assert(code==1);
   // double val = 0;
   // if (code==1){
   //    double max = x_.max();
   //    double min = x_.min();
   //    if (max > range_max_){
   //       max = range_max_;
   //    }
   //    if (min < range_min_){
   //       min = range_min_;
   //    }
   //    val =  max - min;
   // }
   // std::cout << val << std::endl;
   // return val;
   // return 0;
   return range_max_ - range_min_; 
 } 

}
}
}

