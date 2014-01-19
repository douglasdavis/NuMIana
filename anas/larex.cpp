#include "LArAna.hh"
#include <iostream>
#include "TApplication.h"
#include "TH1D.h"
#include "TCanvas.h"

int main(int argc, char *argv[])
{
  // SETUP
  std::string file_name = argv[1];
  lar::LArAna *my_ana = new lar::LArAna(file_name);
  
  // GETTING SOME DATA
  TH1D *hstartx = new TH1D("hstartx","hist",100,1,0);
  TH1D *hnuintx = new TH1D("hnuintx","hist",100,1,0);
  my_ana->FillTH1D(*hstartx,my_ana->StartX());
  my_ana->FillTH1D(*hnuintx,my_ana->NuIntVtxX());
  
  // DRAWING
  TApplication *tapp = new TApplication("tapp",&argc,argv);
  TCanvas *can1 = new TCanvas();
  hstartx->Draw();
  TCanvas *can2 = new TCanvas();
  hnuintx->Draw();
  tapp->Run();
  
  return 0;
}
