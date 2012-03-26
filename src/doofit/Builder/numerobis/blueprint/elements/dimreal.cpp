#include "doofit/Builder/numerobis/blueprint/elements/dimreal.h"

// from RooFit
#include "RooRealVar.h"

namespace doofit {
namespace builder {
namespace numerobis {
namespace blueprint {
namespace elements {


DimReal::DimReal(){
  
}

DimReal::DimReal(const std::string& id_rel, const std::string& id_abs, 
                 const std::string& desc, double val_min, double val_max, const std::string& unit) 
    : val_min_(val_min)
    , val_max_(val_max)
    , unit_(unit)
{
  set_id_rel(id_rel);
  set_id_abs(id_abs);
  set_desc(desc);
  
  set_initialized(true);
  set_ready(true);
}


DimReal::~DimReal() {
  
}

RooAbsReal* DimReal::CreateTempRooObj(std::vector<RooAbsArg*> dependants) {
  RooRealVar* temp_realvar = new RooRealVar(id_abs().c_str(), desc().c_str(), val_min(), val_max(), unit().c_str());
  return temp_realvar;
}

} // namespace elements 
} // namespace blueprint 
} // namespace numerobis 
} // namespace builder 
} // namespace doofit
