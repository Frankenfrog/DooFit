
// from STL
#include <iostream>
#include <string>

// from RooFit
#include "RooWorkspace.h"

// from Project
#include "doofit/builder/bobthebuilder/Bob/Bob.h"

using namespace std;
using namespace doofit;
namespace bpt = boost::property_tree;

using namespace builder::bobthebuilder;

int main( int argc, char *argv[] ){
  
  string filename = argv[1];
  
  Bob builder;
  builder.load(filename);
  
  RooWorkspace ws("workspace","workspace");
  builder.DumpToRooWorkspace(ws);
  
  ws.Print();
  
  return 0;
}
