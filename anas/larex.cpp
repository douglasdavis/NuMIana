#include "LArAna.hh"
#include "WindowAna.hh"
#include "DAnaLibs.hh"
#include <iostream>
#include "TApplication.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "looks.h"

int main(int argc, char *argv[])
{
  looks();
  gStyle->SetOptStat(0);
  std::string file_name1 = argv[1];
  std::string file_name2 = argv[2];

  lar::LArAna       *lar_ana    = new lar::LArAna(file_name1);
  window::WindowAna *window_ana = new window::WindowAna(file_name2);

  TH1D *h_LeptonVx = new TH1D("h_LeptonTx",";Lepton Vx",100,1,0);
  FillTH1D(*h_LeptonVx,lar_ana->LeptonVx());

  lar_ana->fPlotTitle->AddText("The Title");

  TApplication *app = new TApplication("app",&argc,argv);
  h_LeptonVx->Draw();
  lar_ana->fPlotTitle->Draw("same");
  app->Run();


  return 0;
}
