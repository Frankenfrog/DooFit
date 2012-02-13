// from STL
#include <iostream>
#include <string>

// from RooFit
#include "RooWorkspace.h"

// from Project
#include "doofit/Config/CommonConfig.h"
#include "doofit/Builder/numerobis/numerobis.h"
#include "doofit/Builder/numerobis/numerobis_config.h"

using namespace std;

using namespace doofit;
using namespace doofit::builder::numerobis;

int main( int argc, char *argv[] ){
  
  string filename = argv[1];

  Config::CommonConfig cfg_com("common");
  cfg_com.InitializeOptions(argc, argv);
  
  NumerobisConfig cfg_bld("numerobis");
  cfg_bld.InitializeOptions(cfg_com);
  
  // More or less mandatory step after initialization of all Config objects.
  // Check if the help flag is set and (if so) print a help message.
  cfg_com.CheckHelpFlagAndPrintHelp();
  cfg_bld.CheckHelpFlagAndPrintHelp();
  

  Numerobis(cfg_com,cfg_bld);
  
  return 0;
}