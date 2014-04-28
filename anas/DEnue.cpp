#include "Utils.hh"
#include "TH2D.h"
#include "TFile.h"
#include <iostream>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  std::string root_file   = argv[1];
  std::string string_dm2  = argv[2];
  std::string string_s22t = argv[3];
  std::string out_file_n  = argv[4];

  double dm2  = atof(string_dm2.c_str());
  double s22t = atof(string_s22t.c_str());

  TFile *the_file = new TFile(root_file.c_str());
  TH2D  *NumuDistEnergyHist     = dynamic_cast<TH2D*>(the_file->Get("NumuDistEnergy"));
  TH2D  *NumuFluxDistEnergyHist = dynamic_cast<TH2D*>(the_file->Get("NumuFluxDistEnergy"));

  TFile *out_file = new TFile(out_file_n.c_str(),"RECREATE");
  TH2D  *NueDistEnergyHist     = new TH2D("NueDistEnergyHist",
					  ";Energy (MeV);L (m)",
					  20,0,100,150,0,750);
  TH2D  *NueFluxDistEnergyHist = new TH2D("NueFluxDistEnergyHist",
					  ";Energy (MeV);L (m)",
					  20,0,100,150,0,750);

  for ( int i = 0; i < NumuDistEnergyHist->GetNbinsX(); ++i ) {
    for ( int j = 0; j < NumuDistEnergyHist->GetNbinsY(); ++j ) {
      double x       = NumuDistEnergyHist->GetXaxis()->GetBinCenter(i+1);
      double y       = NumuDistEnergyHist->GetYaxis()->GetBinCenter(j+1);
      double LoverE  = y/x;
      double numuval = NumuDistEnergyHist->GetBinContent(i+i,j+i);
      double oprob   = numi::utils::OscProb(LoverE,dm2,s22t);
      double nueval  = numuval*oprob;
      NueDistEnergyHist->SetBinContent(i+i,j+i,nueval);
    }
  }

  for ( int i = 0; i < NumuFluxDistEnergyHist->GetNbinsX(); ++i ) {
    for ( int j = 0; j < NumuFluxDistEnergyHist->GetNbinsY(); ++j ) {
      double x       = NumuFluxDistEnergyHist->GetXaxis()->GetBinCenter(i+1);
      double y       = NumuFluxDistEnergyHist->GetYaxis()->GetBinCenter(j+1);
      double LoverE  = y/x;
      double numuval = NumuFluxDistEnergyHist->GetBinContent(i+i,j+i);
      double oprob   = numi::utils::OscProb(LoverE,dm2,s22t);
      double nueval  = numuval*oprob;
      NueFluxDistEnergyHist->SetBinContent(i+i,j+i,nueval);
    }
  }

  NueDistEnergyHist->Write();
  NueFluxDistEnergyHist->Write();
  out_file->Close();

  return 0;
}
