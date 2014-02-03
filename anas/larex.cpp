#include "LArAna.hh"
#include "WindowAna.hh"
#include "DAnaLibs.hh"
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

  LArAna    *lar_ana    = new LArAna(file_name1);
  WindowAna *window_ana = new WindowAna(file_name2);

  TH1D *h_NuE = new TH1D("h_NuE",";#nu Energy",60,1,0);
  FillTH1D(*h_NuE,lar_ana->NuEnergy());

  TH1D *h_LeptonThetaXZ2 = new TH1D("h_LeptonThetaXZ2",";Lepton Theta XZ;",60,1,0);
  FillTH1D(*h_LeptonThetaXZ2,lar_ana->LeptonThetaXZ2());

  lar_ana->fPlotTitle->AddText("NuMI MC");

  TApplication *app = new TApplication("app",&argc,argv);
  h_NuE->Draw();
  lar_ana->fPlotTitle->Draw("same");
  app->Run();


  return 0;
}
