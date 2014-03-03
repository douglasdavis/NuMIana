#include <iostream>
#include "simpleAna.hh"
#include "LArAna.hh"
#include "Utils.hh"
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

  std::string bott_file = argv[1];
  std::string long_file = argv[2];
  std::string norm_file = argv[3];
  /*
  numi::LArAna larbott(bott_file);
  numi::LArAna larlong(long_file);
  numi::LArAna larnorm(norm_file);

  larbott.Print_ndecayppmedium(larbott.ppmediumndecay());
  //  larlong.Print_ndecayppmedium(larlong.ppmediumndecay());
  larnorm.Print_ndecayppmedium(larnorm.ppmediumndecay());
  */
  numi::simpleAna sbott(bott_file,false);
  numi::simpleAna slong(long_file,false);
  numi::simpleAna snorm(norm_file,true);

  numi::utils::Print_ndecayppmedium(sbott.ppmediumndecay(),
		       sbott.ndecayCodeMap(),
		       sbott.ppmediumCodeMap());
  numi::utils::Print_ndecayppmedium(slong.ppmediumndecay(),
		       slong.ndecayCodeMap(),
		       slong.ppmediumCodeMap());
  numi::utils::Print_ndecayppmedium(snorm.ppmediumndecay(),
		       snorm.ndecayCodeMap(),
		       snorm.ppmediumCodeMap());
  return 0;
}
