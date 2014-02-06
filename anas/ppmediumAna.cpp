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
  looks();
  gStyle->SetOptStat(0);
  if ( argc < 4 ) return 0;
    
  std::string file_name1 = argv[1];
  std::string file_name2 = argv[2];
  std::string file_name3 = argv[3];
  WindowAna bott_ana(file_name1);
  WindowAna long_ana(file_name2);
  WindowAna norm_ana(file_name3);

  auto B_evtno    = bott_ana.evtno();
  auto L_evtno    = long_ana.evtno();
  auto N_evtno    = norm_ana.evtno();
  auto B_ppmedium = bott_ana.ppmedium();
  auto L_ppmedium = long_ana.ppmedium();
  auto N_ppmedium = norm_ana.ppmedium();
  auto B_ndecay   = bott_ana.ndecay();
  auto L_ndecay   = long_ana.ndecay();
  auto N_ndecay   = norm_ana.ndecay();
  
  for ( auto i = 0; i < B_evtno.size(); i++ ) {
    std::cout << B_evtno[i]    << " "
	      << B_ppmedium[i] << " "
	      << B_ndecay[i]    << std::endl;
  }
  
  return 0;
}
