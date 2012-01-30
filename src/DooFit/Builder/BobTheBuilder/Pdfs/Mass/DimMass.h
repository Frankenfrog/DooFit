#ifndef BUILDER_BOBTHEBUILDER_DIMMASS_H
#define BUILDER_BOBTHEBUILDER_DIMMASS_H

// from Project
#include "DooFit/Builder/BobTheBuilder/Pdfs/Common/AbsDimensionReal.h"

namespace DooFit {
namespace Builder { namespace BobTheBuilder {

class DimMass : public AbsDimensionReal{
 public:
  DimMass();
  ~DimMass();
  
  boost::shared_ptr<AbsPdf> CreatePdf( const std::string& pdf_type );
};

}}
}
#endif // BUILDER_BOBTHEBUILDER_DIMMASS_H
