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
  Ana ana;

  looks();
  gStyle->SetOptStat(0);
  std::string file_name1 = argv[1];
  std::string file_name2 = argv[2];

  LArAna    *lar_ana    = new LArAna(file_name1);
  simpleAna *window_ana = new simpleAna(file_name2);

  /*
  auto PdgCodeStartPx = lar_ana->PdgCodeStartPx();
  auto PdgCodeStartE  = lar_ana->PdgCodeStartE();
  
  for ( auto vec_entry : PdgCodeStartPx ) {
    for ( auto i = 0; i < vec_entry.first.size(); i++ ) {
      std::cout << vec_entry.first[i] << " " << vec_entry.second[i] << std::endl;
    }
  }

  std::cout << " *************** " << std::endl;

  for ( auto vec_entry : PdgCodeStartE ) {
    for ( auto i = 0; i < vec_entry.first.size(); i++ ) {
      std::cout << vec_entry.first[i] << " " << vec_entry.second[i] << std::endl;
    }
  }
  */

  TH1D *h_NuE = new TH1D("h_NuE",";#nu Energy",60,1,0);
  ana.FillTH1D(*h_NuE,lar_ana->NuEnergy());
  
  TH1D *h_LeptonThetaXZ2 = new TH1D("h_LeptonThetaXZ2",";Lepton Theta XZ;",60,1,0);
  ana.FillTH1D(*h_LeptonThetaXZ2,lar_ana->LeptonThetaXZ2());

  TPaveText *title2 = new TPaveText(0.6485149,0.9311224,0.8778878,0.9821429,"brNDC");
  ana.FixTitle(*title2,"NuMI MC Energy");

  lar_ana->SetupTitle("NuMI MC");
  TApplication *app = new TApplication("app",&argc,argv);
  h_NuE->Draw();
  //lar_ana->PlotTitle->Draw("same");
  title2->Draw("same");
  app->Run();
  
  return 0;
}
