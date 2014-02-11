#include <iostream>
#include "simpleAna.hh"
#include "TH3D.h"
#include "Utils.hh"
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

  if ( argc < 4 )
    return 0;
    
  std::string file_name1 = argv[1];
  std::string file_name2 = argv[2];
  std::string file_name3 = argv[3];

  numi::simpleAna bott_ana(file_name1);
  numi::simpleAna long_ana(file_name2);
  numi::simpleAna norm_ana(file_name3);
  
  long_ana.SetupTitle("Long Window");
  norm_ana.SetupTitle("Normal Window");
  bott_ana.SetupTitle("Bottom Window");

  TApplication *app = new TApplication("app",&argc,argv);
  TCanvas      *can1 = new TCanvas();
  can1->SetLogy();
  bott_ana.PlotTitle->Draw("same");
  TCanvas      *can2 = new TCanvas();
  can2->SetLogy();
  long_ana.PlotTitle->Draw("same");
  TCanvas      *can3 = new TCanvas();
  can3->SetLogy();
  norm_ana.PlotTitle->Draw("same");

  app->Run();

  return 0;
}
