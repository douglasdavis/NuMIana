#include <iostream>
#include "simpleAna.hh"
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

  std::string file_name1("../data/gsimple/bottom/bottom.root");
  std::string file_name2("../data/gsimple/length/length.root");
  std::string file_name3("../data/gsimple/normal/normal.root");

  numi::simpleAna bott_ana(file_name1);
  numi::simpleAna long_ana(file_name2);
  numi::simpleAna norm_ana(file_name3);
  
  auto b_pdgE = bott_ana.PdgEnergy(); // vector<pair<Int_t,Double_t>>
  auto l_pdgE = long_ana.PdgEnergy();
  auto n_pdgE = norm_ana.PdgEnergy();

  //_______________________________________________________________________________________________________

  std::map < Int_t, TH1D* > hBott;
  std::map < Int_t, TH1D* > hLong;
  std::map < Int_t, TH1D* > hNorm;

  hBott[14]  = new TH1D("numu_bottom",";Energy (GeV);#nu_{#mu}/m^{2}/50 MeV/10^{9} POT",120,0,6);
  hBott[-14] = new TH1D("numubar_bottom",";Energy (GeV);#bar{#nu}_{#mu}/m^{2}/50 MeV/10^{9} POT",120,0,6);
  hBott[12]  = new TH1D("nue_bottom",";Energy (GeV);#nu_{e}/m^{2}/50 MeV/10^{9} POT",120,0,6);
  hBott[-12] = new TH1D("nubar_bottom",";Energy (GeV);#bar{#nu}_{e}/m^{2}/50 MeV/10^{9} POT",120,0,6);

  hLong[14]  = new TH1D("numu_length",";Energy (GeV);#nu_{#mu}/m^{2}/50 MeV/10^{9} POT",120,0,6);
  hLong[-14] = new TH1D("numubar_length",";Energy (GeV);#bar{#nu}_{#mu}/m^{2}/50 MeV/10^{9} POT",120,0,6);
  hLong[12]  = new TH1D("nue_length",";Energy (GeV);#nu_{e}/m^{2}/50 MeV/10^{9} POT",120,0,6);
  hLong[-12] = new TH1D("nuebar_length",";Energy (GeV);#bar{#nu}_{e}/m^{2}/50 MeV/10^{9} POT",120,0,6);

  hNorm[14]  = new TH1D("numu_normal",";Energy (GeV);#nu_{#mu}/m^{2}/50 MeV/10^{9} POT",120,0,6);
  hNorm[-14] = new TH1D("numubar_normal",";Energy (GeV);#bar{#nu}_{#mu}/m^{2}/50 MeV/10^{9} POT",120,0,6);
  hNorm[12]  = new TH1D("nue_normal",";Energy (GeV);#nu_{e}/m^{2}/50 MeV/10^{9} POT",120,0,6);
  hNorm[-12] = new TH1D("nuebar_normal",";Energy (GeV);#bar{#nu}_{e}/m^{2}/50 MeV/10^{9} POT",120,0,6);

  std::vector< std::map< Int_t, TH1D* > > formatVec;
  formatVec.push_back(hBott);
  formatVec.push_back(hLong);
  formatVec.push_back(hNorm);
  for ( auto const& topentry : formatVec ) {
    for ( auto const& entry : topentry ) {
      if ( entry.first == 14 )
	entry.second->SetLineColor(kAzure-5);
      if ( entry.first == -14 )
	entry.second->SetLineColor(kRed+2);
      if ( entry.first == 12 )
	entry.second->SetLineColor(kGreen+2);
      if ( entry.first == -12 )
	entry.second->SetLineColor(kOrange+2);
    }
  }

  //_______________________________________________________________________________________________________

  for ( auto const& entry : b_pdgE )
    hBott[entry.first]->Fill(entry.second);

  for ( auto const& entry : l_pdgE )
    hLong[entry.first]->Fill(entry.second);

  for ( auto const& entry : n_pdgE )
    hNorm[entry.first]->Fill(entry.second);

  //_______________________________________________________________________________________________________

  for ( auto const& hist : hBott ) {
    hist.second->GetXaxis()->CenterTitle();
    hist.second->GetYaxis()->CenterTitle();
  }

  for ( auto const& hist : hLong ) {
    hist.second->GetXaxis()->CenterTitle();
    hist.second->GetYaxis()->CenterTitle();
  }

  for ( auto const& hist : hNorm ) {
    hist.second->GetXaxis()->CenterTitle();
    hist.second->GetYaxis()->CenterTitle();
  }

  //_______________________________________________________________________________________________________

  TApplication tapp("tapp",&argc,argv);

  TCanvas cb;
  cb.SetLogy();
  hBott[14]->Draw();
  hBott[-14]->Draw("same");
  hBott[12]->Draw("same");
  hBott[-12]->Draw("same");
  cb.RedrawAxis();

  TCanvas cl;
  cl.SetLogy();
  hLong[14]->Draw();
  hLong[-14]->Draw("same");
  hLong[12]->Draw("same");
  hLong[-12]->Draw("same");
  cl.RedrawAxis();

  TCanvas cn;
  cn.SetLogy();
  hNorm[14]->Draw();
  hNorm[-14]->Draw("same");
  hNorm[12]->Draw("same");
  hNorm[-12]->Draw("same");
  cn.RedrawAxis();

  tapp.Run();
  return 0;

}

