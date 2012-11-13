#include "doofit/builder/EasyPdf/EasyPdf.h"

// from STL
#include <map>
#include <string>

// from RooFit
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooArgList.h"
#include "RooProdPdf.h"
#include "RooWorkspace.h"
#include "RooExtendPdf.h"
#include "RooAddPdf.h"
#include "RooFormulaVar.h"
#include "RooCategory.h"
#include "RooGaussModel.h"
#include "RooAddModel.h"

// from DooCore
#include "doocore/io/MsgStream.h"

// from project
#include "doofit/Config/CommaSeparatedList.h"

using namespace ROOT;
using namespace RooFit;
using namespace doocore::io;

doofit::builder::EasyPdf::EasyPdf(RooWorkspace* ws)
: ws_(ws)
{}

doofit::builder::EasyPdf::~EasyPdf() {
  if (ws_ == NULL) {
    // if no workspace is to be used, delete all elements
    for (std::map<std::string,RooAbsPdf*>::iterator it = pdfs_.begin();
         it != pdfs_.end(); ++it) {
      delete it->second;
    }
    for (std::map<std::string,RooRealVar*>::iterator it = vars_.begin();
         it != vars_.end(); ++it) {
      delete it->second;
    }
  }
}

RooAbsReal& doofit::builder::EasyPdf::Real(const std::string &name) {
  if (vars_.count(name) == 1) {
    return *vars_[name];
  } else if (formulas_.count(name) == 1) {
    return *formulas_[name];
  } else {
    return Var(name);
  }
}

RooRealVar& doofit::builder::EasyPdf::Var(const std::string &name) {
  if (vars_.count(name) == 1) {
    return *vars_[name];
  } else {
    RooRealVar* temp_var = new RooRealVar(name.c_str(), name.c_str(), 0.0);
    if (ws_ == NULL) {
      vars_[name] = temp_var;
    } else {
      ws_->import(*temp_var, Silence());
      delete temp_var;
      vars_[name] = temp_var = ws_->var(name.c_str());
    }
    return *temp_var;
  }
}

RooCategory& doofit::builder::EasyPdf::Cat(const std::string &name) {
  if (cats_.count(name) == 1) {
    return *cats_[name];
  } else {
    RooCategory* temp_cat = new RooCategory(name.c_str(), name.c_str());
    if (ws_ == NULL) {
      cats_[name] = temp_cat;
    } else {
      ws_->import(*temp_cat, Silence());
      delete temp_cat;
      cats_[name] = temp_cat = ws_->cat(name.c_str());
    }
    return *temp_cat;
  }
}

RooFormulaVar& doofit::builder::EasyPdf::Formula(const std::string& name, const std::string& formula,
                                                 const RooArgList& dependents) {
  if (formulas_.count(name) == 1) {
    throw ObjectExistsException();
  } else {
    RooFormulaVar* temp_formula = new RooFormulaVar(name.c_str(), name.c_str(),
                                                    formula.c_str(), dependents);
    if (ws_ == NULL) {
      formulas_[name] = temp_formula;
    } else {
      ws_->import(*temp_formula, Silence());
      delete temp_formula;
      formulas_[name] = temp_formula = dynamic_cast<RooFormulaVar*>(ws_->function(name.c_str()));
    }
    return *temp_formula;
  }
}

RooFormulaVar& doofit::builder::EasyPdf::Formula(const std::string& name) {
  if (formulas_.count(name) == 1) {
    return *formulas_[name];
  } else {
    throw ObjectNotExistingException();
  }
}

RooArgSet doofit::builder::EasyPdf::Vars(const std::string &name) {
  Config::CommaSeparatedList<std::string> variables;
  variables.Parse(name);
  
  RooArgSet argset;
  for (int i=0; i<variables.size(); ++i) {
    if (vars_.count(variables[i]) == 1) {
      argset.add(Var(variables[i]));
    } else if (cats_.count(variables[i]) == 1) {
      argset.add(Cat(variables[i]));
    } else if (formulas_.count(variables[i]) == 1) {
      argset.add(Formula(variables[i]));
    } else {
      argset.add(Var(variables[i]));
    }
  }
  return argset;
}

RooArgSet doofit::builder::EasyPdf::AllVars() {
  RooArgSet argset;
  
  for (std::map<std::string,RooRealVar*>::const_iterator it = vars_.begin();
       it != vars_.end(); ++it) {
    argset.add(*(it->second));
  }
  for (std::map<std::string,RooCategory*>::const_iterator it = cats_.begin();
       it != cats_.end(); ++it) {
    argset.add(*(it->second));
  }
  for (std::map<std::string,RooFormulaVar*>::const_iterator it = formulas_.begin();
       it != formulas_.end(); ++it) {
    argset.add(*(it->second));
  }
  return argset;
}


RooGaussian& doofit::builder::EasyPdf::Gaussian(const std::string &name, RooAbsReal& x, RooAbsReal& mean, RooAbsReal& sigma) {
  return AddPdfToStore<RooGaussian>(new RooGaussian(name.c_str(), name.c_str(), x, mean, sigma));
}

RooExponential& doofit::builder::EasyPdf::Exponential(const std::string &name, RooAbsReal& x, RooAbsReal& e) {
  return AddPdfToStore<RooExponential>(new RooExponential(name.c_str(), name.c_str(), x, e));
}

RooProdPdf& doofit::builder::EasyPdf::Product(const std::string& name, const RooArgList& pdfs) {
  return AddPdfToStore<RooProdPdf>(new RooProdPdf(name.c_str(), name.c_str(), pdfs));
}

RooExtendPdf& doofit::builder::EasyPdf::Extend(const std::string& name, const RooAbsPdf& pdf, const RooAbsReal& yield) {
  return AddPdfToStore<RooExtendPdf>(new RooExtendPdf(name.c_str(), name.c_str(), pdf, yield));
}

RooAddPdf& doofit::builder::EasyPdf::Add(const std::string& name, const RooArgList& pdfs) {
  return AddPdfToStore<RooAddPdf>(new RooAddPdf(name.c_str(), name.c_str(), pdfs));
}

RooAddPdf& doofit::builder::EasyPdf::Add(const std::string& name, const RooArgList& pdfs, const RooArgList& coefs) {
  return AddPdfToStore<RooAddPdf>(new RooAddPdf(name.c_str(), name.c_str(), pdfs, coefs));
}

RooGaussModel& doofit::builder::EasyPdf::GaussModel(const std::string& name, RooRealVar& x, RooAbsReal& mean, RooAbsReal& sigma) {
  return AddPdfToStore<RooGaussModel>(new RooGaussModel(name.c_str(), name.c_str(), x, mean, sigma));
}

RooAddModel& doofit::builder::EasyPdf::DoubleGaussModel(const std::string& name, RooRealVar& x, RooAbsReal& mean, RooAbsReal& sigma1, RooAbsReal& sigma2, RooAbsReal& fraction) {
  return AddModel(name, RooArgList(GaussModel("p1_"+name,x,mean,sigma1),
                                   GaussModel("p2_"+name,x,mean,sigma2)),
                  RooArgList(fraction));
}

RooAddModel& doofit::builder::EasyPdf::TripleGaussModel(const std::string& name, RooRealVar& x, RooAbsReal& mean, RooAbsReal& sigma1, RooAbsReal& sigma2, RooAbsReal& sigma3, RooAbsReal& fraction1, RooAbsReal& fraction2) {
  return AddModel(name, RooArgList(GaussModel("p1_"+name,x,mean,sigma1),
                                   GaussModel("p2_"+name,x,mean,sigma2),
                                   GaussModel("p3_"+name,x,mean,sigma3)),
                  RooArgList(fraction1, fraction2));
}

RooAddModel& doofit::builder::EasyPdf::QuadGaussModel(const std::string& name, RooRealVar& x, RooAbsReal& mean, RooAbsReal& sigma1, RooAbsReal& sigma2, RooAbsReal& sigma3, RooAbsReal& sigma4, RooAbsReal& fraction1, RooAbsReal& fraction2, RooAbsReal& fraction3) {
  return AddModel(name, RooArgList(GaussModel("p1_"+name,x,mean,sigma1),
                                   GaussModel("p2_"+name,x,mean,sigma2),
                                   GaussModel("p3_"+name,x,mean,sigma3),
                                   GaussModel("p4_"+name,x,mean,sigma4)),
                  RooArgList(fraction1, fraction2, fraction3));
}

RooAddModel& doofit::builder::EasyPdf::AddModel(const std::string& name, const RooArgList& pdfs, const RooArgList& coefs) {
  return AddPdfToStore<RooAddModel>(new RooAddModel(name.c_str(), name.c_str(), pdfs, coefs));
}

RooAddPdf& doofit::builder::EasyPdf::DoubleGaussianScaled(const std::string& name, RooAbsReal& x, RooAbsReal& mean, RooAbsReal& sigma, RooAbsReal& scale, RooAbsReal& fraction, std::string sigma2_name) {
  if (sigma2_name.length() == 0) {
    sigma2_name = name+"_sigma2";
  }
  
  return Add(name, RooArgList(Gaussian("p1_"+name,x,mean,sigma),
                              Gaussian("p2_"+name,x,mean,Formula(sigma2_name, "@0*@1", RooArgList(sigma,scale)))),
             RooArgList(fraction));
}

RooAbsPdf& doofit::builder::EasyPdf::Pdf(const std::string &name) {
  if (pdfs_.count(name) == 1) {
    return *pdfs_[name];
  } else {
    throw ObjectNotExistingException();
  }
}
