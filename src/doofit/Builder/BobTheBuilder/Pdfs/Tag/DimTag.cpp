#include "doofit/Builder/BobTheBuilder/Pdfs/Tag/DimTag.h"


// from project
#include "doofit/utils//MsgStream.h"

// from project Pdf related classes
#include "doofit/Builder/BobTheBuilder/Pdfs/Common/AbsPdf.h"


namespace doofit {
namespace Builder{ 
namespace BobTheBuilder{

DimTag::DimTag() :
   AbsDimensionCat()
{
  
}

DimTag::~DimTag(){
  
}

boost::shared_ptr<AbsPdf> DimTag::CreatePdf( const std::string& pdf_type ){
  
}

}}
}
