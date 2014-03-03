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
#include "TLegend.h"

int main(int argc, char *argv[])
{
  looks();
  gStyle->SetOptStat(0);

  std::string file_name1("../data/gsimple/bottom/bottom.root");
  std::string file_name2("../data/gsimple/length/length.root");
  std::string file_name3("../data/gsimple/normal/normal.root");

  numi::simpleAna bott_ana(file_name1,false);
  numi::simpleAna long_ana(file_name2,false);
  numi::simpleAna norm_ana(file_name3,true);
  
  auto b_pdgE = bott_ana.PdgEnergy(); // vector<pair<Int_t,Double_t>>
  auto l_pdgE = long_ana.PdgEnergy();
  auto n_pdgE = norm_ana.PdgEnergy();

  //_______________________________________________________________________________________________________

  std::map < Int_t, TH1D* > hBott;
  std::map < Int_t, TH1D* > hLong;
  std::map < Int_t, TH1D* > hNorm;

  hBott[14]  = new TH1D("numu_bottom","MicroBooNE NuMI Flux, Bottom Window;Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",120,0,6);
  hBott[-14] = new TH1D("numubar_bottom","MicroBooNE NuMI Flux, Bottom Window;Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",120,0,6);
  hBott[12]  = new TH1D("nue_bottom","MicroBooNE NuMI Flux, Bottom Window;Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",120,0,6);
  hBott[-12] = new TH1D("nubar_bottom","MicroBooNE NuMI Flux, Bottom Window;Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",120,0,6);

  hLong[14]  = new TH1D("numu_length","MicroBooNE NuMI Flux, Length Window;Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",120,0,6);
  hLong[-14] = new TH1D("numubar_length","MicroBooNE NuMI Flux, Length Window;Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",120,0,6);
  hLong[12]  = new TH1D("nue_length","MicroBooNE NuMI Flux, Length Window;Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",120,0,6);
  hLong[-12] = new TH1D("nuebar_length","MicroBooNE NuMI Flux, Length Window;Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",120,0,6);

  hNorm[14]  = new TH1D("numu_normal","MicroBooNE NuMI Flux, Normal Window;Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",120,0,6);
  hNorm[-14] = new TH1D("numubar_normal","MicroBooNE NuMI Flux, Normal Window;Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",120,0,6);
  hNorm[12]  = new TH1D("nue_normal","MicroBooNE NuMI Flux, Normal Window;Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",120,0,6);
  hNorm[-12] = new TH1D("nuebar_normal","MicroBooNE NuMI Flux, Normal Window;Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",120,0,6);

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
    hist.second->Scale((1./bott_ana.BottArea())/1e1);
  }

  for ( auto const& hist : hLong ) {
    hist.second->GetXaxis()->CenterTitle();
    hist.second->GetYaxis()->CenterTitle();
    hist.second->Scale((1./long_ana.LongArea())/1e1);
  }

  for ( auto const& hist : hNorm ) {
    hist.second->GetXaxis()->CenterTitle();
    hist.second->GetYaxis()->CenterTitle();
    hist.second->Scale((1./norm_ana.NormArea())/1e1);
  }

  //_______________________________________________________________________________________________________

  TLegend *legend = new TLegend(0.640264,0.6454082,0.80033,0.8979592,NULL,"brNDC");
  legend->AddEntry(hBott[14], "#nu_{#mu}",      "l");
  legend->AddEntry(hBott[-14],"#bar{#nu}_{#mu}","l");
  legend->AddEntry(hBott[12], "#nu_{e}",        "l");
  legend->AddEntry(hBott[-12],"#bar{#nu}_{e}",  "l");
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetTextFont(102);
  legend->SetTextSize(0.048);
  
  //_______________________________________________________________________________________________________

  TApplication tapp("tapp",&argc,argv);

  TCanvas cb;
  cb.SetLogy();
  hBott[14]->Draw();
  hBott[-14]->Draw("same");
  hBott[12]->Draw("same");
  hBott[-12]->Draw("same");
  legend->Draw("same");
  cb.RedrawAxis();

  TCanvas cl;
  cl.SetLogy();
  hLong[14]->Draw();
  hLong[-14]->Draw("same");
  hLong[12]->Draw("same");
  hLong[-12]->Draw("same");
  legend->Draw("same");
  cl.RedrawAxis();

  TCanvas cn;
  cn.SetLogy();
  hNorm[14]->Draw();
  hNorm[-14]->Draw("same");
  hNorm[12]->Draw("same");
  hNorm[-12]->Draw("same");
  legend->Draw("same");
  cn.RedrawAxis();

  tapp.Run();
  Int_t ok;
  std::cin >> ok;
  return 0;

}

