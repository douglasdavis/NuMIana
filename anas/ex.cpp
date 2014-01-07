#include <iostream>
#include "NuMIana.h"
#include "TH3D.h"
#include "TApplication.h"
#include "TCanvas.h"

int main(int argc, char *argv[])
{
  if ( argc < 4 )
    return 0;
  
  std::string file_name1 = argv[1];
  std::string file_name2 = argv[2];
  std::string file_name3 = argv[3];
  
  NuMIana long_ana(file_name1.c_str());
  NuMIana bott_ana(file_name2.c_str());
  NuMIana norm_ana(file_name3.c_str());
  
  long_ana.PrintDecays();
  bott_ana.PrintDecays();
  norm_ana.PrintDecays();
  
  return 0;
}
