///////////////////////////////////////////////////////////////////////////////
///  \brief   Methods of EvRate class (doing flux/event rate histograms)
///  \author  douglasdavis@utexas.edu
///////////////////////////////////////////////////////////////////////////////

#include "EvRate.hh"
#include "TTree.h"

namespace numi {
  
  EvRate::EvRate(const std::string& flux_file_dir,
		 const std::string& genie_file_name,
		 const std::vector< std::string >& file_vector,
		 const Int_t& nu_pdg,
		 const Bool_t& isbottom,
		 const Bool_t& islength,
		 const Bool_t& isnormal) {
    
    fNuMIChain = new TChain("NuMI");
    fGenieFile = new TFile(genie_file_name.c_str(),"READ");
    
    fSelectedPdg = nu_pdg;
    fNFluxFiles  = file_vector.size();
    
    fLowerVzCut = -1.0e10;
    fUpperVzCut =  1.0e10;
    
    fIsBottom   = isbottom;
    fIsLength   = islength;
    fIsNormal   = isnormal;

    for ( auto const& entry : file_vector )
      fNuMIChain->Add((flux_file_dir+"/"+entry).c_str());
    
    if ( nu_pdg == 14 )
      fDir = (TDirectory*)fGenieFile->Get("nu_mu_Ar40");
    if ( nu_pdg == -14 )
      fDir = (TDirectory*)fGenieFile->Get("nu_mu_bar_Ar40");
    if ( nu_pdg == 12 )
      fDir = (TDirectory*)fGenieFile->Get("nu_e_Ar40");
    if ( nu_pdg == -12 )
      fDir = (TDirectory*)fGenieFile->Get("nu_e_bar_Ar40");
    
    fXsecGraphs["tot_cc"]  = (TGraph*)fDir->Get("tot_cc");
    std::cout << fXsecGraphs["tot_cc"]->Eval(6) << std::endl;
    fXsecGraphs["tot_nc"]  = (TGraph*)fDir->Get("tot_nc");
    
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
  
  EvRate::~EvRate() {}
  
  void EvRate::MakeHists(const std::string& out_file_name, const Double_t& area_factor)
  {
    Int_t    nbins     = 120;
    Double_t E_min     = 0;
    Double_t E_max     = 6;
    Double_t BinEnergy = (E_max-E_min)/(Double_t)nbins;
    Double_t FluxPOT   = 1e8;
    Double_t CCPOT     = 6e20;
    Double_t XsecExpo  = 1e-42;
    Double_t POTscaler = CCPOT/FluxPOT;

    const Int_t n_parents = 7;
    std::string parent_strings[n_parents] = { "K0L", "K+", "K-", "mu+", "mu-", "pi+", "pi-" };

    std::map < std::string, TH1D* > hFlux;
    std::map < std::string, TH1D* > hCC;
    std::map < std::string, TH1D* > hNC;
    
    hFlux["total"] = new TH1D("FluxTotal",";Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",nbins,E_min,E_max);
    hCC["total"]   = new TH1D("CCTotal",  ";Energy (GeV);CC int/50 MeV/6 #times 10^{20} POT",nbins,E_min,E_max);
    hNC["total"]   = new TH1D("NCTotal",  ";Energy (GeV);NC int/50 MeV/6 #times 10^{20} POT",nbins,E_min,E_max);

    for ( auto i = 0; i < n_parents; i++ ) {
      
      std::string HNBF  = "Flux";
      std::string HNF    = HNBF+parent_strings[i];
      hFlux[parent_strings[i]] = new TH1D(HNF.c_str(),";Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT",nbins,E_min,E_max);

      std::string HNBCC = "CC";
      std::string HNCC  = HNBCC+parent_strings[i];
      hCC[parent_strings[i]] = new TH1D(HNCC.c_str(),";Energy (GeV);CC int/m^{2}/50 MeV/6 #times 10^{20} POT",nbins,E_min,E_max);
      
      std::string HNBNC = "NC";
      std::string HNNC  = HNBNC+parent_strings[i];
      hNC[parent_strings[i]] = new TH1D(HNNC.c_str(),";Energy (GeV);NC int/m^{2}/50 MeV/6 #times 10^{20} POT",nbins,E_min,E_max);
      
    }
    std::cout << " << Histograms initialized >> " << std::endl;

    std::cout << " << Filling histograms >> "     << std::endl;
    for ( Int_t i = 0; i < fNuMIChain->GetEntries(); i++ ) {
      fNuMIChain->GetEntry(i);
      if ( fIsBottom || fIsLength ) {
	if ( fpdg == fSelectedPdg ) {
	  hFlux["total"]->Fill(fE);
	  if ( fndecay == 1 || fndecay == 2 || fndecay == 3 || fndecay == 4 )
	    hFlux["K0L"]->Fill(fE);
	  if ( fndecay == 5 || fndecay == 6 || fndecay == 7 )
	    hFlux["K+"]->Fill(fE);
	  if ( fndecay == 8 || fndecay == 9 || fndecay == 10 )
	    hFlux["K-"]->Fill(fE);
	  if ( fndecay == 11 )
	    hFlux["mu+"]->Fill(fE);
	  if ( fndecay == 12 )
	    hFlux["mu-"]->Fill(fE);
	  if ( fndecay == 13 )
	    hFlux["pi+"]->Fill(fE);
	  if ( fndecay == 14 )
	    hFlux["pi-"]->Fill(fE);
	} // selected pdg
      } // length or bottom
      if ( fIsNormal ) {
	if ( fpz > 0 ) {
	  if ( fpdg == fSelectedPdg ) {
	    hFlux["total"]->Fill(fE);
	    if ( fndecay == 1 || fndecay == 2 || fndecay == 3 || fndecay == 4 )
	      hFlux["K0L"]->Fill(fE);
	    if ( fndecay == 5 || fndecay == 6 || fndecay == 7 )
	      hFlux["K+"]->Fill(fE);
	    if ( fndecay == 8 || fndecay == 9 || fndecay == 10 )
	      hFlux["K-"]->Fill(fE);
	    if ( fndecay == 11 )
	      hFlux["mu+"]->Fill(fE);
	    if ( fndecay == 12 )
	      hFlux["mu-"]->Fill(fE);
	    if ( fndecay == 13 )
	      hFlux["pi+"]->Fill(fE);
	    if ( fndecay == 14 )
	      hFlux["pi-"]->Fill(fE);
	  } // pdg = selected pdg
	} // if pz > 0
      }	// if isnormal
    } // for all entries in chain

    for ( auto const& hist : hFlux ) {
      for ( Int_t i = 0; i < hist.second->GetNbinsX(); i++ ) {
	Double_t hist_val = hist.second->GetBinContent(i+1);
	Double_t energy   = hist.second->GetBinCenter(i+1);
	Double_t filler   = (fXsecGraphs["cc_tot"]->Eval(energy))*energy*hist_val;
	hCC[hist.first]->SetBinContent(i+1,filler);
      }
    }

    std::cout << " << Writing histograms to file >> " << std::endl;
    TFile *out_file = new TFile(out_file_name.c_str(),"RECREATE");
    
    for ( auto const& entry : hFlux ) {
      entry.second->Scale(1.0/(area_factor*fNFluxFiles));
      entry.second->Write();
    }
    for ( auto const& entry : hCC )
      entry.second->Write();
    for ( auto const& entry : hNC )
      entry.second->Write();

    out_file->Close();
    std::cout << " << Done >> " << std::endl;
  }
  
}
