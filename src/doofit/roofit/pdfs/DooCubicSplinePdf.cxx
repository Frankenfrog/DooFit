/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "DooCubicSplinePdf.h" 

// STD & STL
#include <cmath>
#include <complex>
#include <iterator>
#include <algorithm>
#include <sstream>

// ROOT
#include <TMath.h>
#include <TH1.h>
#include <TGraph.h>
#include <TGraphErrors.h>

// RooFit
#include <RooFit.h>
#include <Riostream.h>
#include <RooMath.h>
#include <RooAbsReal.h>
#include <RooRealVar.h>
#include <RooConstVar.h>
#include <RooArgList.h>

using namespace std;

ClassImp(doofit::roofit::pdfs::DooCubicSplinePdf) 

namespace doofit {
namespace roofit {
namespace pdfs {

  DooCubicSplinePdf::DooCubicSplinePdf()
      : _aux(0,0)
  {
  }

  DooCubicSplinePdf::DooCubicSplinePdf(const std::string name,
                                       RooRealVar& x, 
                                       const vector<double>& knots,
                                       const RooArgList& coefList,
                                       double range_min,
                                       double range_max):
    RooAbsPdf(name.c_str(), name.c_str()),
    _x("x", "Dependent", this, x),
    _coefList("coefficients", "List of coefficients", this),
    _aux(knots.begin(), knots.end()),
    _range_min(range_min),
    _range_max(range_max)
  {
    assert(size_t(coefList.getSize()) == 2 + knots.size());
    _coefList.add(coefList);
    if ((_range_min!=0) || (_range_max!=0)){
      std::cout << "DooCubicSplinePdf: using limited range " << _range_min << "-" << _range_max << std::endl;
      _aux.set_range(_range_min, _range_max);
    }
  }

  DooCubicSplinePdf::DooCubicSplinePdf(const std::string name,
                                       RooRealVar& x, 
                                       const vector<double>& knots,
                                       const RooArgList& coefList):
    DooCubicSplinePdf(name, x, knots, coefList, 0, 0)
  {
  }

  DooCubicSplinePdf::DooCubicSplinePdf(const DooCubicSplinePdf& other, const char* name) :
    RooAbsPdf(other, name),
    _x("x", this, other._x),
    _coefList("coefList", this, other._coefList),
    _aux(other._aux)
  {
  }

  DooCubicSplinePdf::~DooCubicSplinePdf()
  {
  }

  Double_t DooCubicSplinePdf::evaluate() const
  {
    return _aux.evaluate(_x,_coefList);
  }

  Int_t DooCubicSplinePdf::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName) const
  {
    // No analytical calculation available (yet) of integrals over subranges
    // // 2014-11-07 ccauet
    // just trust me, everything is alright as long as the PDF is zero before first and after last knot
    // if (_x.min(rangeName)!=_aux.knots().front() || _x.max(rangeName)!=_aux.knots().back() ) return 0;
    // //
    if (matchArgs(allVars, analVars, _x)) return 1;
    return 0;
  }

  Double_t DooCubicSplinePdf::analyticalIntegral(Int_t code, const char* /* rangeName */) const
  {
    assert(code==1) ;
    return _aux.analyticalIntegral(_coefList);
  }
}
}
}

