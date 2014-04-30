#include "TH2D.h"
#include "TFile.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>


double osc_prob(const double& LoverE, const double& dm2, const double& s22t);

void OscillateHist(TH2D *mu, TH2D *e, const double& dm2, const double& s22t);

int main(int argc, char *argv[])
{
  std::string root_file    = argv[1]; // root file containing numu th2d
  std::string string_dm2   = argv[2]; // known dm^2 value
  std::string string_s22t  = argv[3]; // known sin^2(2theta) value
  std::string string_adm2  = argv[4]; // known dm^2 (anti-nu)
  std::string string_as22t = argv[5]; // known sin^2(2theta) (anti-nu)
  std::string out_file_n   = argv[6]; // name of output file

  double dm2   = atof(string_dm2.c_str());
  double s22t  = atof(string_s22t.c_str());
  double adm2  = atof(string_adm2.c_str());
  double as22t = atof(string_as22t.c_str());

  TFile *the_file = new TFile(root_file.c_str());

  TH2D  *NumuDistEnergyHist        = dynamic_cast<TH2D*>(the_file->Get("NumuDistEnergy"));
  TH2D  *NumubarDistEnergyHist     = dynamic_cast<TH2D*>(the_file->Get("NumubarDistEnergy"));
  TH2D  *NumuNumubarDistEnergyHist = dynamic_cast<TH2D*>(the_file->Get("NumuNumubarDistEnergy"));

  TFile *out_file = new TFile(out_file_n.c_str(),"RECREATE");
  TH2D  *NueDistEnergyHist       = new TH2D("NueDistEnergyHist",
					    ";Energy (GeV);L (m)",
					    120,0,6,150,0,750);
  TH2D  *NuebarDistEnergyHist    = new TH2D("NuebarDistEnergyHist",
					    ";Energy (GeV);L (m)",
					    120,0,6,150,0,750);
  TH2D  *NueNuebarDistEnergyHist = new TH2D("NueNuebarDistEnergyHist",
					    ";Energy (GeV);L (m)",
					    120,0,6,150,0,750);

  OscillateHist(NumuDistEnergyHist,NueDistEnergyHist,dm2,s22t);
  OscillateHist(NumubarDistEnergyHist,NuebarDistEnergyHist,adm2,as22t);
  //  OscillateHist(NumuNumubarDistEnergyHist,NueNuebarDistEnergyHist,dm2,s22t);

  NumuDistEnergyHist->Write(); //why not write both?
  NueDistEnergyHist->Write();

  NumubarDistEnergyHist->Write();
  NuebarDistEnergyHist->Write();

  //  NumuNumubarDistEnergyHist->Write();
  //  NueNuebarDistEnergyHist->Write();

  out_file->Close();

  return 0;
}


double osc_prob(const double& LoverE, const double& dm2, const double& s22t)
{
  // sin^2(2theta)*sin(1.267*dm^2*L/E)
  return s22t*std::sin(1.267*dm2*LoverE);
}


void OscillateHist(TH2D *mu, TH2D *e, const double& dm2, const double& s22t)
{
  for ( int i = 0; i < mu->GetNbinsX(); ++i ) {
    for ( int j = 0; j < mu->GetNbinsY(); ++j ) {
      double energy_val = mu->GetXaxis()->GetBinCenter(i+1);
      double dist_val   = mu->GetYaxis()->GetBinCenter(j+1);
      double LoverE     = (dist_val*.001)/energy_val; // km/GeV
      double numu_flux  = mu->GetBinContent(i+1,j+1);
      double oprob      = osc_prob(LoverE,dm2,s22t);
      double nue_flux   = numu_flux*oprob;
      e->SetBinContent(i+1,j+1,nue_flux);
    }
  }
}
