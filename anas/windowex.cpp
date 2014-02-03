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

  if ( argc < 4 )
    return 0;
    
  std::string file_name1 = argv[1];
  std::string file_name2 = argv[2];
  std::string file_name3 = argv[3];

  WindowAna *bott_ana = new WindowAna(file_name1.c_str());
  WindowAna *long_ana = new WindowAna(file_name2.c_str());
  WindowAna *norm_ana = new WindowAna(file_name3.c_str());
  
  std::cout << "*************** LONG ************" << std::endl;
  long_ana->PrintDecays();
  long_ana->PrintNeutrinos();
  std::cout << "*************** BOTT ************" << std::endl;
  bott_ana->PrintDecays();
  bott_ana->PrintNeutrinos();
  std::cout << "*************** NORM ************" << std::endl;
  norm_ana->PrintDecays();
  norm_ana->PrintNeutrinos();

  TH1D *h_bott_vx = new TH1D("h_bott_vx",";x decay vertex;#nu/10^{9} POT",100,1,0);
  TH1D *h_bott_vy = new TH1D("h_bott_vy",";y decay vertex;#nu/10^{9} POT",100,1,0);
  TH1D *h_bott_vz = new TH1D("h_bott_vz",";z decay vertex;#nu/10^{9} POT",100,1,0);
  
  TH1D *h_long_vx = new TH1D("h_long_vx",";x decay vertex;#nu/10^{9} POT",100,1,0);
  TH1D *h_long_vy = new TH1D("h_long_vy",";y decay vertex;#nu/10^{9} POT",100,1,0);
  TH1D *h_long_vz = new TH1D("h_long_vz",";z decay vertex;#nu/10^{9} POT",100,1,0);
  
  TH1D *h_norm_vx = new TH1D("h_norm_vx",";x decay vertex;#nu/10^{9} POT",100,1,0);
  TH1D *h_norm_vy = new TH1D("h_norm_vy",";y decay vertex;#nu/10^{9} POT",100,1,0);
  TH1D *h_norm_vz = new TH1D("h_norm_vz",";z decay vertex;#nu/10^{9} POT",100,1,0);
  
  std::vector<double> vx_l = long_ana->vx();
  std::vector<double> vy_l = long_ana->vy();
  std::vector<double> vz_l = long_ana->vz();
  std::vector<double> vx_n = norm_ana->vx();
  std::vector<double> vy_n = norm_ana->vy();
  std::vector<double> vz_n = norm_ana->vz();
  std::vector<double> vx_b = bott_ana->vx();
  std::vector<double> vy_b = bott_ana->vy();
  std::vector<double> vz_b = bott_ana->vz();
  std::vector<double> px_l = long_ana->px();
  std::vector<double> py_l = long_ana->py();
  std::vector<double> pz_l = long_ana->pz();
  std::vector<double> px_b = bott_ana->px();
  std::vector<double> py_b = bott_ana->py();
  std::vector<double> pz_b = bott_ana->pz();
  std::vector<double> px_n = norm_ana->px();
  std::vector<double> py_n = norm_ana->py();
  std::vector<double> pz_n = norm_ana->pz();
  
  for ( int i = 0; i < vz_l.size(); i++ ) {
    if ( pz_l[i] <= 0 )
      h_long_vz->Fill(vz_l[i]);
  }
  for ( int i = 0; i < vz_b.size(); i++ ) {
    if ( pz_b[i] <= 0 )
      h_bott_vz->Fill(vz_b[i]);
  }
  for ( int i = 0; i < vz_n.size(); i++ ) {
    if ( pz_n[i] <= 0 )
      h_norm_vz->Fill(vz_n[i]);
  }

  long_ana->SetupTitle("Long Window");
  norm_ana->SetupTitle("Normal Window");
  bott_ana->SetupTitle("Bottom Window");

  
  TApplication *app = new TApplication("app",&argc,argv);
  TCanvas      *can1 = new TCanvas();
  can1->SetLogy();
  h_bott_vz->Draw();
  bott_ana->fPlotTitle->Draw("same");
  TCanvas      *can2 = new TCanvas();
  can2->SetLogy();
  h_long_vz->Draw();
  long_ana->fPlotTitle->Draw("same");
  TCanvas      *can3 = new TCanvas();
  can3->SetLogy();
  h_norm_vz->Draw();
  norm_ana->fPlotTitle->Draw("same");

  app->Run();

  return 0;
}
