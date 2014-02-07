#include <iostream>
#include "WindowAna.hh"
#include "TH3D.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TROOT.h"
#include "looks.hh"

int main(int argc, char *argv[])
{
  Ana ana;
  
  looks();
  gStyle->SetOptStat(0);
  if ( argc < 4 ) return 0;
    
  std::string file_name1 = argv[1];
  std::string file_name2 = argv[2];
  std::string file_name3 = argv[3];

  WindowAna bott_ana(file_name1);
  WindowAna long_ana(file_name2);
  WindowAna norm_ana(file_name3);
  
  ana.Print_ppmediumndecay(bott_ana.ppmediumndecay());
  
  return 0;
}
