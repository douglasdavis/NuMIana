#include "FullDistEnergy.hh"
#include <fstream>
#include <cmath>

namespace numi {

  // _____________________________________________________________________________________________________
  
  FullDistEnergy::FullDistEnergy(const std::string& flux_file_dir,
				 const std::string& genie_file_name,
				 const std::vector< std::string >& file_vector,
				 const Bool_t& isbottom,
				 const Bool_t& islength,
				 const Bool_t& isnormal) : fBottomArea(51.926),
							   fLengthArea(51.600),
							   fNormalArea(11.920)
  {

    fIsBottom = isbottom;
    fIsNormal = isnormal;
    fIsLength = islength;

    fNuMIChain = new TChain("NuMI");
    fGENIEFile = new TFile(genie_file_name.c_str());
    
    fNFluxFiles      = file_vector.size();
    fPOTPerFluxFile = 1.0e8;

    for ( auto const& entry : file_vector )
      fNuMIChain->Add((flux_file_dir+"/"+entry).c_str());

    fCCxsec_nue       = dynamic_cast<TGraph*>(fGENIEFile->Get("nu_e_Ar40/tot_cc"));
    fNCxsec_nue       = dynamic_cast<TGraph*>(fGENIEFile->Get("nu_e_Ar40/tot_nc"));
    fCCQExsec_nue     = dynamic_cast<TGraph*>(fGENIEFile->Get("nu_e_Ar40/qel_cc_n"));

    fCCxsec_nue->SetTitle(";Energy (GeV);#sigma 10^{-38} cm^{2}");
    fNCxsec_nue->SetTitle(";Energy (GeV);#sigma 10^{-38} cm^{2}");
    fCCQExsec_nue->SetTitle(";Energy (GeV);#sigma 10^{-38} cm^{2}");
    
    fLowExsec_nue = new TGraph("config/lowe_nue_Ar40_xsec.dat","%lg %lg");
    fLowExsec_nue->SetTitle(";Energy (MeV);#sigma 10^{-38} cm^{2}");

    fNuMIChain->SetBranchAddress("wgt",     &fwgt);
    fNuMIChain->SetBranchAddress("vtxx",    &fvtxx);
    fNuMIChain->SetBranchAddress("vtxy",    &fvtxy);
    fNuMIChain->SetBranchAddress("vtxz",    &fvtxz);
    fNuMIChain->SetBranchAddress("dist",    &fdist);
    fNuMIChain->SetBranchAddress("px",      &fpx);
    fNuMIChain->SetBranchAddress("py",      &fpy);
    fNuMIChain->SetBranchAddress("pz",      &fpz);
    fNuMIChain->SetBranchAddress("E",       &fE);
    fNuMIChain->SetBranchAddress("pdg",     &fpdg);
    fNuMIChain->SetBranchAddress("tpx",     &ftpx);
    fNuMIChain->SetBranchAddress("tpy",     &ftpy);
    fNuMIChain->SetBranchAddress("tpz",     &ftpz);
    fNuMIChain->SetBranchAddress("vx",      &fvx);
    fNuMIChain->SetBranchAddress("vy",      &fvy);
    fNuMIChain->SetBranchAddress("vz",      &fvz);
    fNuMIChain->SetBranchAddress("ndecay",  &fndecay);
    fNuMIChain->SetBranchAddress("ppmedium",&fppmedium);
    fNuMIChain->SetBranchAddress("tptype",  &ftptype);
    fNuMIChain->SetBranchAddress("run",     &frun);
    fNuMIChain->SetBranchAddress("evtno",   &fevtno);
    fNuMIChain->SetBranchAddress("entryno", &fentryno);

  }

  // _____________________________________________________________________________________________________
  
  FullDistEnergy::~FullDistEnergy() {}

  // _____________________________________________________________________________________________________

  void FullDistEnergy::MakeHists(const std::string& out_file_name,
				 const Double_t& area_factor,
				 const Double_t& dm2,
				 const Double_t& s22t,
				 const Double_t& adm2,
				 const Double_t& as22t)
  {

    fOutFile               = new TFile(out_file_name.c_str(),"RECREATE");    
    fNumuDistEnergy        = new TH2D("NumuDistEnergy",
				      ";Energy (MeV);Distance from origin to uB center",
				      120,0,3,150,0,750);
    fNumubarDistEnergy     = new TH2D("NumubarDistEnergy",
				      ";Energy (MeV);Distance from origin to uB center",
				      120,0,3,150,0,750);
    fNumuNumubarDistEnergy = new TH2D("NumuNumubarDistEnergy",
				      ";Energy (MeV);Distance from origin to uB center",
				      120,0,3,150,0,750);
    fNueDistEnergy         = new TH2D("NueDistEnergy",
				      ";Energy (MeV);Distance from origin to uB center",
				      120,0,3,150,0,750);
    fNuebarDistEnergy      = new TH2D("NuebarDistEnergy",
				      ";Energy (MeV);Distance from origin to uB center",
				      120,0,3,150,0,750);
    
    Double_t distfiller;
    Double_t xmx02;
    Double_t ymy02;
    Double_t zmz02;

    Double_t ubx = 54.500;
    Double_t uby = 74.460;
    Double_t ubz = 677.61;

    for ( UInt_t i = 0; i < fNuMIChain->GetEntries(); ++i ) {
      fNuMIChain->GetEntry(i);
      if ( fIsNormal ) {
	if ( fpz < 0 ) {
	  continue;
	}
	else {
	  xmx02 = pow((ubx - (fvx/1.0e2)),2);
	  ymy02 = pow((uby - (fvy/1.0e2)),2);
	  zmz02 = pow((ubz - (fvz/1.0e2)),2);
	  distfiller = std::sqrt(xmx02+ymy02+zmz02);
	  if ( fpdg == 14 )
	    fNumuDistEnergy->Fill(fE,distfiller);
	  if ( fpdg == -14 )
	    fNumubarDistEnergy->Fill(fE,distfiller);
	  if ( fpdg == 14 || fpdg == -14 )
	    fNumuNumubarDistEnergy->Fill(fE,distfiller);
	}
      }
      else {
	xmx02 = pow((ubx - (fvx/1.0e2)),2);
	ymy02 = pow((uby - (fvy/1.0e2)),2);
	zmz02 = pow((ubz - (fvz/1.0e2)),2);
	distfiller = std::sqrt(xmx02+ymy02+zmz02);
	if ( fpdg == 14 )
	  fNumuDistEnergy->Fill(fE,distfiller);
	if ( fpdg == -14 )
	  fNumubarDistEnergy->Fill(fE,distfiller);
	if ( fpdg == 14 || fpdg == -14 )
	  fNumuNumubarDistEnergy->Fill(fE,distfiller);
      }
    }
  
    Double_t desiredPOT = 6e20;
    Double_t totalPOT   = fPOTPerFluxFile*fNFluxFiles;
    Double_t pot_scaler = desiredPOT/totalPOT;

    fNumuDistEnergy->Scale(pot_scaler);
    fNumuDistEnergy->Scale(1/(area_factor*3.14159));
    fNumuDistEnergy->Write();

    fNumubarDistEnergy->Scale(pot_scaler);
    fNumubarDistEnergy->Scale(1/(area_factor*3.14159));
    fNumubarDistEnergy->Write();

    fNumuNumubarDistEnergy->Scale(pot_scaler);
    fNumuNumubarDistEnergy->Scale(1/(area_factor*3.14159));
    fNumuNumubarDistEnergy->Write();

    OscillateHist(fNumuDistEnergy,fNueDistEnergy,dm2,s22t);
    OscillateHist(fNumubarDistEnergy,fNuebarDistEnergy,adm2,as22t);

    fNueDistEnergy->Write();
    fNuebarDistEnergy->Write();

    fCCxsec_nue->Write();
    fNCxsec_nue->Write();
    fCCQExsec_nue->Write();
    fLowExsec_nue->Write();

    fOutFile->Close();

  }
  
  // _____________________________________________________________________________________________________

  double FullDistEnergy::OscProb(const double& LoverE, const double& dm2, const double& s22t)
  {
    // sin^2(2theta)*sin(1.267*dm^2*L/E)
    return s22t*std::sin(1.267*dm2*LoverE);
  }

  void FullDistEnergy::OscillateHist(TH2D *mu, TH2D *e, const double& dm2, const double& s22t)
  {
    for ( int i = 0; i < mu->GetNbinsX(); ++i ) {
      for ( int j = 0; j < mu->GetNbinsY(); ++j ) {
	double energy_val = mu->GetXaxis()->GetBinCenter(i+1);
	double dist_val   = mu->GetYaxis()->GetBinCenter(j+1);
	double LoverE     = (dist_val*0.001)/energy_val; // km/GeV
	double numu_flux  = mu->GetBinContent(i+1,j+1);
	double oprob      = OscProb(LoverE,dm2,s22t);
	double nue_flux   = numu_flux*oprob;
	e->SetBinContent(i+1,j+1,nue_flux);
      }
    }
  }

  // _____________________________________________________________________________________________________

}
