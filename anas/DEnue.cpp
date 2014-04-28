#include "TH2D.h"
#include "TFile.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>

double osc_prob(const double& LoverE, const double& dm2, const double& s22t)
{
  // sin^2(2theta)*sin(1.267*dm^2*L/E)
  return s22t*std::sin(1.267*dm2*LoverE);
}

int main(int argc, char *argv[])
{
  std::string root_file   = argv[1]; // root file containing numu th2d
  std::string string_dm2  = argv[2]; // known dm^2 value
  std::string string_s22t = argv[3]; // known sin^2(2theta) value
  std::string out_file_n  = argv[4]; // name of output file

  double dm2  = atof(string_dm2.c_str());
  double s22t = atof(string_s22t.c_str());

  TFile *the_file = new TFile(root_file.c_str());
  // Get the numu histogram from file
  TH2D  *NumuDistEnergyHist = dynamic_cast<TH2D*>(the_file->Get("NumuDistEnergy"));

  TFile *out_file = new TFile(out_file_n.c_str(),"RECREATE");
  TH2D  *NueDistEnergyHist = new TH2D("NueDistEnergyHist",
				      ";Energy (MeV);L (m)",
				      20,0,100,150,0,750);

  for ( int i = 0; i < NumuDistEnergyHist->GetNbinsX(); ++i ) {
    for ( int j = 0; j < NumuDistEnergyHist->GetNbinsY(); ++j ) {
      // get the E value (x) at bin i+i (horizontal axis)
      double x       = NumuDistEnergyHist->GetXaxis()->GetBinCenter(i+1);
      // get the L value (y) at bin j+1 (vertical axis)
      double y       = NumuDistEnergyHist->GetYaxis()->GetBinCenter(j+1);
      // L/E = y/x
      double LoverE  = y/x;
      // Get the total number of numu at bin i+1,j+1 (the given E,L)
      double numuval = NumuDistEnergyHist->GetBinContent(i+i,j+i);
      // calculate probability of oscillation with parameters
      double oprob   = osc_prob(LoverE,dm2,s22t);
      double nueval  = numuval*oprob;
      NueDistEnergyHist->SetBinContent(i+i,j+i,nueval);

    }
  }

  NumuDistEnergyHist->Write(); //why not write both?
  NueDistEnergyHist->Write();
  out_file->Close();

  return 0;
}
