#include "TestWiese/ConfigTest/ConfigTest.h"

int main(int argc, char *argv[]) {
  
  ConfigTest config;
  config.InitializeOptions(argc, argv);
  
  ConfigTestSecond config2;
  config2.InitializeOptions(config.unrec_options());
  
  config.PrintHelp();
  
  config.Print();
  config2.Print();
  
  return 0;
}