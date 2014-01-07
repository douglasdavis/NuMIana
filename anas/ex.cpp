#include <iostream>
#include "NuMIana.hh"
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
  
  NuMIana *long_ana = new NuMIana(file_name1.c_str());
  NuMIana *bott_ana = new NuMIana(file_name2.c_str());
  NuMIana *norm_ana = new NuMIana(file_name3.c_str());
  
  std::cout << "*************** LONG ************" << std::endl;
  long_ana->PrintDecays();
  long_ana->PrintNeutrinos();

  std::cout << "*************** BOTT ************" << std::endl;
  bott_ana->PrintDecays();
  bott_ana->PrintNeutrinos();

  std::cout << "*************** NORM ************" << std::endl;
  norm_ana->PrintDecays();
  norm_ana->PrintNeutrinos();

  return 0;
}
