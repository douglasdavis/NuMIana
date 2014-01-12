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
  gStyle->SetOptStat(0);

  if ( argc < 4 )
    return 0;
    
  std::string file_name1 = argv[1];
  std::string file_name2 = argv[2];
  std::string file_name3 = argv[3];

  /*
  std::string file_name1 = "files/bott/combined.root";
  std::string file_name2 = "files/long/combined.root";
  std::string file_name3 = "files/norm/combined.root";
  */

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
  
  /*
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
  */
  
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
    if ( pz_l[i] >= 0 )
      h_long_vz->Fill(vz_l[i]);
  }
  for ( int i = 0; i < vz_b.size(); i++ ) {
    if ( pz_b[i] >= 0 )
      h_bott_vz->Fill(vz_b[i]);
  }
  for ( int i = 0; i < vz_n.size(); i++ ) {
    if ( pz_n[i] >= 0 )
      h_norm_vz->Fill(vz_n[i]);
  }

  long_ana->fPlotTitle->AddText("Long Window");
  norm_ana->fPlotTitle->AddText("Normal Window");
  bott_ana->fPlotTitle->AddText("Bottom Window");

  
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
