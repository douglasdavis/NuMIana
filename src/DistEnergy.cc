#include "DistEnergy.hh"
#include <fstream>
#include <cmath>

namespace numi {

  // _____________________________________________________________________________________________________
  
  DistEnergy::DistEnergy(const std::string& flux_file_dir,
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
  
  DistEnergy::~DistEnergy() {}

  // _____________________________________________________________________________________________________

  void DistEnergy::MakeHists(const std::string& out_file_name,
			     const Double_t& area_factor)
  {

    fOutFile               = new TFile(out_file_name.c_str(),"RECREATE");    
    fNumuDistEnergy        = new TH2D("NumuDistEnergy",
				      ";Energy (MeV);Distance from origin to uB center",
				      20,0,100,150,0,750);
    fNumubarDistEnergy     = new TH2D("NumubarDistEnergy",
				      ";Energy (MeV);Distance from origin to uB center",
				      20,0,100,150,0,750);
    fNumuNumubarDistEnergy = new TH2D("NumuNumubarDistEnergy",
				      ";Energy (MeV);Distance from origin to uB center",
				      20,0,100,150,0,750);
    
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
	  if (fE < .1 ) {
	    xmx02 = pow((ubx - (fvx/1.0e2)),2);
	    ymy02 = pow((uby - (fvy/1.0e2)),2);
	    zmz02 = pow((ubz - (fvz/1.0e2)),2);
	    distfiller = std::sqrt(xmx02+ymy02+zmz02);
	    if ( fpdg == 14 )
	      fNumuDistEnergy->Fill(fE*1000,distfiller);
	    if ( fpdg == -14 )
	      fNumubarDistEnergy->Fill(fE*1000,distfiller);
	    if ( fpdg == 14 || fpdg == -14 )
	      fNumuNumubarDistEnergy->Fill(fE*1000,distfiller);
	  }
	}
      }
      else {
	if (fE < .1 ) {
	  xmx02 = pow((ubx - (fvx/1.0e2)),2);
	  ymy02 = pow((uby - (fvy/1.0e2)),2);
	  zmz02 = pow((ubz - (fvz/1.0e2)),2);
	  distfiller = std::sqrt(xmx02+ymy02+zmz02);
	  if ( fpdg == 14 )
	    fNumuDistEnergy->Fill(fE*1000,distfiller);
	  if ( fpdg == -14 )
	    fNumubarDistEnergy->Fill(fE*1000,distfiller);
	  if ( fpdg == 14 || fpdg == -14 )
	    fNumuNumubarDistEnergy->Fill(fE*1000,distfiller);
	}
      }
    }
  
    Double_t desiredPOT = 6e20;
    Double_t totalPOT   = fPOTPerFluxFile*fNFluxFiles;
    Double_t scaler     = desiredPOT/totalPOT;

    fNumuDistEnergy->Scale(scaler);
    fNumuDistEnergy->Scale(1/area_factor);
    fNumuDistEnergy->Write();

    fNumubarDistEnergy->Scale(scaler);
    fNumubarDistEnergy->Scale(1/area_factor);
    fNumubarDistEnergy->Write();

    fNumuNumubarDistEnergy->Scale(scaler);
    fNumuNumubarDistEnergy->Scale(1/area_factor);
    fNumuNumubarDistEnergy->Write();

    fCCxsec_nue->Write();
    fNCxsec_nue->Write();
    fCCQExsec_nue->Write();
    fLowExsec_nue->Write();

    fOutFile->Close();

  }
  
  // _____________________________________________________________________________________________________

}