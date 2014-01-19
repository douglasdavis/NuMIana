#include "LArAna.hh"
#include <iostream>
#include "TApplication.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "looks.h"

int main(int argc, char *argv[])
{
  looks();
  // SETUP
  std::string file_name = argv[1];
  lar::LArAna *my_ana = new lar::LArAna(file_name);
  
  // GETTING SOME DATA
  TH1D *hstartz = new TH1D("hstartz","hist",50,1,0);
  TH1D *hnuintx = new TH1D("hnuintx","hist",50,1,0);
  my_ana->FillTH1D(*hstartz,my_ana->StartZ(),200);
  my_ana->FillTH1D(*hnuintx,my_ana->NuIntVtxX());
  
  // DRAWING
  TApplication *tapp1 = new TApplication("tapp1",&argc,argv);
  TCanvas *can1 = new TCanvas();
  hstartz->Draw();

  TCanvas *can2 = new TCanvas();
  hnuintx->Draw();

  tapp1->Run();
  return 0;
}
