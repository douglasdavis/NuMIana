#include "LArAna.hh"
#include "simpleAna.hh"
#include "Ana.hh"
#include <iostream>
#include "TApplication.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "looks.hh"

int main(int argc, char *argv[])
{

  looks();
  gStyle->SetOptStat(0);
  std::string file_name1 = argv[1];
  std::string file_name2 = argv[2];

  numi::LArAna    bottana(file_name1);
  numi::LArAna    normana(file_name2);

  auto bott_CCQE      = bottana.CCQEint();
  auto norm_CCQE      = normana.CCQEint();
  auto bott_LeptonPdg = bottana.LeptonPdg();
  auto norm_LeptonPdg = normana.LeptonPdg();
  
  int b_numuCCQE = 0;
  int b_nueCCQE = 0;
  
  int n_numuCCQE = 0;
  int n_nueCCQE = 0;
  
  for ( auto i = 0; i < bott_CCQE.size(); ++i ) {
    std::cout << bott_CCQE[i] << " " << bott_LeptonPdg[i] << std::endl;
    if ( bott_CCQE[i] ) {
      if ( bott_LeptonPdg[i] == 11 )
	++b_nueCCQE;
      if ( bott_LeptonPdg[i] == 13 )
	++b_numuCCQE;
    }
  }
  
  for ( auto i = 0; i < norm_CCQE.size(); ++i ) {
    std::cout << norm_CCQE[i] << " " << norm_LeptonPdg[i] << std::endl;
    if ( norm_CCQE[i] ) {
      if ( norm_LeptonPdg[i] == 11 )
	++n_nueCCQE;
      if ( norm_LeptonPdg[i] == 13 )
	++n_numuCCQE;
    }
  }
  
  std::cout << "bottom nue  : " << b_nueCCQE  << std::endl;
  std::cout << "bottom numu : " << b_numuCCQE << std::endl;
  std::cout << "normal nue  : " << n_nueCCQE  << std::endl;
  std::cout << "normal numu : " << n_numuCCQE << std::endl;

  //  numi::simpleAna window_ana(file_name2);

  /*
  auto PdgCodeStartPx = lar_ana.PdgCodeStartPx();
  auto PdgCodeStartE  = lar_ana.PdgCodeStartE();
  
  for ( auto vec_entry : PdgCodeStartPx ) {
    for ( auto i = 0; i < vec_entry.first.size(); i++ ) {
      std::cout << vec_entry.first[i] << " " << vec_entry.second[i] << std::endl;
    }
  }

  for ( auto vec_entry : PdgCodeStartE ) {
    for ( auto i = 0; i < vec_entry.first.size(); i++ ) {
      std::cout << vec_entry.first[i] << " " << vec_entry.second[i] << std::endl;
    }
  }
  */
  return 0;
}
