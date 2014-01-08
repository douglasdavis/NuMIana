#include <iostream>
#include "NuMIana.hh"
#include "TH3D.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TROOT.h"
#include "looks.h"

int main(int argc, char *argv[])
{
  looks();

  if ( argc < 4 )
    return 0;
  
  std::string file_name1 = argv[1];
  std::string file_name2 = argv[2];
  std::string file_name3 = argv[3];
  
  NuMIana *bott_ana = new NuMIana(file_name1.c_str());
  NuMIana *long_ana = new NuMIana(file_name2.c_str());
  NuMIana *norm_ana = new NuMIana(file_name3.c_str());
  
  std::cout << "*************** LONG ************" << std::endl;
  long_ana->PrintDecays();
  long_ana->PrintNeutrinos();

  std::cout << "*************** BOTT ************" << std::endl;
  bott_ana->PrintDecays();
  bott_ana->PrintNeutrinos();

  std::cout << "*************** NORM ************" << std::endl;
  norm_ana->PrintDecays();
  norm_ana->PrintNeutrinos();
  
  TH1D *h_bott_vx = new TH1D("h_bott_vx",";x decay vertex;#nu/10^{9} POT",500,1,0);
  TH1D *h_bott_vy = new TH1D("h_bott_vy",";y decay vertex;#nu/10^{9} POT",500,1,0);
  TH1D *h_bott_vz = new TH1D("h_bott_vz",";z decay vertex;#nu/10^{9} POT",500,1,0);

  TH1D *h_long_vx = new TH1D("h_long_vx",";x decay vertex;#nu/10^{9} POT",500,1,0);
  TH1D *h_long_vy = new TH1D("h_long_vy",";y decay vertex;#nu/10^{9} POT",500,1,0);
  TH1D *h_long_vz = new TH1D("h_long_vz",";z decay vertex;#nu/10^{9} POT",500,1,0);

  TH1D *h_norm_vx = new TH1D("h_norm_vx",";x decay vertex;#nu/10^{9} POT",500,1,0);
  TH1D *h_norm_vy = new TH1D("h_norm_vy",";y decay vertex;#nu/10^{9} POT",500,1,0);
  TH1D *h_norm_vz = new TH1D("h_norm_vz",";z decay vertex;#nu/10^{9} POT",500,1,0);

  std::vector<TH1D*> hist_vec;
  hist_vec.push_back(h_bott_vx);
  hist_vec.push_back(h_bott_vy);
  hist_vec.push_back(h_bott_vz);
  hist_vec.push_back(h_long_vx);
  hist_vec.push_back(h_long_vy);
  hist_vec.push_back(h_long_vz);
  hist_vec.push_back(h_norm_vx);
  hist_vec.push_back(h_norm_vy);
  hist_vec.push_back(h_norm_vz);
  fix_hist(hist_vec);

  for ( double n : bott_ana->vx() )
    h_bott_vx->Fill(n);
  for ( double n : bott_ana->vy() )
    h_bott_vy->Fill(n);
  for ( double n : bott_ana->vz() )
    h_bott_vz->Fill(n);
  for ( double n : long_ana->vx() )
    h_long_vx->Fill(n);
  for ( double n : long_ana->vy() )
    h_long_vy->Fill(n);
  for ( double n : long_ana->vz() )
    h_long_vz->Fill(n);
  for ( double n : norm_ana->vx() )
    h_norm_vx->Fill(n);
  for ( double n : norm_ana->vy() )
    h_norm_vy->Fill(n);
  for ( double n : norm_ana->vz() )
    h_norm_vz->Fill(n);

  TApplication *app = new TApplication("app",&argc,argv);
  TCanvas      *can1 = new TCanvas();
  can1->SetLogy();
  h_bott_vz->Draw();
  TCanvas      *can2 = new TCanvas();
  can2->SetLogy();
  h_long_vz->Draw();
  TCanvas      *can3 = new TCanvas();
  can3->SetLogy();
  h_norm_vz->Draw();

  app->Run();

  return 0;
}
