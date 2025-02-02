#include <RooResolutionModel.h>
#include "SchillerRooAbsEffResModel.h"

namespace doofit {
namespace schiller {

//_____________________________________________________________________________
RooAbsEffResModel::RooAbsEffResModel(const char *name, const char *title, RooRealVar& __convVar) 
   : RooResolutionModel(name, title, __convVar)
{ }

//_____________________________________________________________________________
RooAbsEffResModel::RooAbsEffResModel(const RooAbsEffResModel& other, const char* name) 
  : RooResolutionModel(other, name)
{ }

RooAbsEffResModel::~RooAbsEffResModel()
{ }

}// namespace schiller
}// namespace doofit
