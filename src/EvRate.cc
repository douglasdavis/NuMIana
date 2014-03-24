///////////////////////////////////////////////////////////////////////////////
///  \brief   Methods of EvRate class (doing flux/event rate histograms)
///  \author  douglasdavis@utexas.edu
///////////////////////////////////////////////////////////////////////////////

#include "EvRate.hh"
#include "TTree.h"
#include <iostream>
#include <fstream>

namespace numi {
  
  EvRate::EvRate(const std::string& flux_file_dir,
		 const std::string& genie_file_name,
		 const std::vector< std::string >& file_vector,
		 const Bool_t& isbottom,
		 const Bool_t& islength,
		 const Bool_t& isnormal) {
    
    fBottomArea = 51.926;
    fLengthArea = 51.600;
    fNormalArea = 11.920;

    fNuMIChain = new TChain("NuMI");
    fGenieFile = new TFile(genie_file_name.c_str());
    
    fNFluxFiles  = file_vector.size();
    
    fLowerVzLimit = -1e10;
    fUpperVzLimit =  1e15;
    fEnergyCut    =  0.0;
    
    fIsBottom   = isbottom;
    fIsLength   = islength;
    fIsNormal   = isnormal;

    for ( auto const& entry : file_vector )
      fNuMIChain->Add((flux_file_dir+"/"+entry).c_str());
    
    fCCxsec_numu      = dynamic_cast<TGraph*> (fGenieFile->Get("nu_mu_Ar40/tot_cc"));
    fNCxsec_numu      = dynamic_cast<TGraph*> (fGenieFile->Get("nu_mu_Ar40/tot_nc"));
    fCCQExsec_numu    = dynamic_cast<TGraph*> (fGenieFile->Get("nu_mu_Ar40/qel_cc_n"));

    fCCxsec_numubar   = dynamic_cast<TGraph*> (fGenieFile->Get("nu_mu_bar_Ar40/tot_cc"));
    fNCxsec_numubar   = dynamic_cast<TGraph*> (fGenieFile->Get("nu_mu_bar_Ar40/tot_nc"));
    fCCQExsec_numubar = dynamic_cast<TGraph*> (fGenieFile->Get("nu_mu_bar_Ar40/qel_cc_p"));

    fCCxsec_nue       = dynamic_cast<TGraph*> (fGenieFile->Get("nu_e_Ar40/tot_cc"));
    fNCxsec_nue       = dynamic_cast<TGraph*> (fGenieFile->Get("nu_e_Ar40/tot_nc"));
    fCCQExsec_nue     = dynamic_cast<TGraph*> (fGenieFile->Get("nu_e_Ar40/qel_cc_n"));

    fCCxsec_nuebar    = dynamic_cast<TGraph*> (fGenieFile->Get("nu_e_bar_Ar40/tot_cc"));
    fNCxsec_nuebar    = dynamic_cast<TGraph*> (fGenieFile->Get("nu_e_bar_Ar40/tot_nc"));
    fCCQExsec_nuebar  = dynamic_cast<TGraph*> (fGenieFile->Get("nu_e_bar_Ar40/qel_cc_p"));

    Double_t LowE_energy[74];
    Double_t LowE_xsec[74];
    Double_t LowE_efiller;
    Double_t LowE_xfiller;
    std::ifstream LowE_file;
    LowE_file.open("config/lowe_nue_Ar40_xsec.dat");
    Int_t counterint = 0;
    while ( LowE_file >> LowE_efiller >> LowE_xfiller ) {
      LowE_energy[counterint] = LowE_efiller/1.0e3;
      LowE_xsec[counterint]   = LowE_xfiller/1.0e4;
    }
    
    fLowExsec_nue = new TGraph(74,LowE_energy,LowE_xsec);

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
  
  void EvRate::SetLowerVzLimit(const Double_t& lim)
  {
    fLowerVzLimit = lim;
  }

  void EvRate::SetUpperVzLimit(const Double_t& lim)
  {
    fUpperVzLimit = lim;
  }

  void EvRate::SetEnergyCut(const Double_t& cut)
  {
    fEnergyCut  = cut;
  }

  void EvRate::MakeHists(const std::string& out_file_name, const Double_t& area_factor)
  {
    Int_t    nbins       = 120;
    Double_t E_min       = 0;
    Double_t E_max       = 6;
    Double_t BinEnergy   = (E_max-E_min)/(Double_t)nbins;
    Double_t FluxPOT     = 1e8;
    Double_t CCPOT       = 6e20;
    Double_t XsecExpo    = 1e-42/(40*1.66e-27);
    Double_t POTscaler   = CCPOT/FluxPOT;
    Double_t Tonage      = 6.14e4;
    Double_t Xsec_factor = POTscaler*XsecExpo*Tonage;

    const Int_t n_parents = 8;
    std::string parent_strings[n_parents] = { "_K0L", "_K+", "_K-", "_mu+", "_mu-", "_pi+", "_pi-" , "_other" };

    
    std::map < std::string, TH1D* > hFlux_numu;
    std::map < std::string, TH1D* > hCC_numu;
    std::map < std::string, TH1D* > hNC_numu;
    std::map < std::string, TH1D* > hCCQE_numu;

    std::map < std::string, TH1D* > hFlux_numubar;
    std::map < std::string, TH1D* > hCC_numubar;
    std::map < std::string, TH1D* > hNC_numubar;
    std::map < std::string, TH1D* > hCCQE_numubar;

    std::map < std::string, TH1D* > hFlux_nue;
    std::map < std::string, TH1D* > hCC_nue;
    std::map < std::string, TH1D* > hNC_nue;
    std::map < std::string, TH1D* > hCCQE_nue;

    std::map < std::string, TH1D* > hFlux_nuebar;
    std::map < std::string, TH1D* > hCC_nuebar;
    std::map < std::string, TH1D* > hNC_nuebar;
    std::map < std::string, TH1D* > hCCQE_nuebar;

    std::string flux_title    = ";Energy (GeV);#nu/m^{2}/50 MeV/10^{8} POT";
    std::string ccint_title   = ";Energy (GeV);Events/50 MeV/6 #times 10^{20} POT/61.4 t";
    std::string ncint_title   = ";Energy (GeV);Events/50 MeV/6 #times 10^{20} POT/61.4 t";
    std::string ccqeint_title = ";Energy (GeV);Events/50 MeV/6 #times 10^{20} POT/61.4 t"; 

    hFlux_numu["total"]    = new TH1D("Flux_Total_numu",flux_title.c_str(),   nbins,E_min,E_max);
    hCC_numu["total"]      = new TH1D("CC_Total_numu",  ccint_title.c_str(),  nbins,E_min,E_max);
    hNC_numu["total"]      = new TH1D("NC_Total_numu",  ncint_title.c_str(),  nbins,E_min,E_max);
    hCCQE_numu["total"]    = new TH1D("CCQE_Total_numu",ccqeint_title.c_str(),nbins,E_min,E_max);

    hFlux_numubar["total"] = new TH1D("Flux_Total_numubar",flux_title.c_str(),   nbins,E_min,E_max);
    hCC_numubar["total"]   = new TH1D("CC_Total_numubar",  ccint_title.c_str(),  nbins,E_min,E_max);
    hNC_numubar["total"]   = new TH1D("NC_Total_numubar",  ncint_title.c_str(),  nbins,E_min,E_max);
    hCCQE_numubar["total"] = new TH1D("CCQE_Total_numubar",ccqeint_title.c_str(),nbins,E_min,E_max);

    hFlux_nue["total"]     = new TH1D("Flux_Total_nue",flux_title.c_str(),   nbins,E_min,E_max);
    hCC_nue["total"]       = new TH1D("CC_Total_nue",  ccint_title.c_str(),  nbins,E_min,E_max);
    hNC_nue["total"]       = new TH1D("NC_Total_nue",  ncint_title.c_str(),  nbins,E_min,E_max);
    hCCQE_nue["total"]     = new TH1D("CCQE_Total_nue",ccqeint_title.c_str(),nbins,E_min,E_max);

    hFlux_nuebar["total"]  = new TH1D("Flux_Total_nuebar",flux_title.c_str(),   nbins,E_min,E_max);
    hCC_nuebar["total"]    = new TH1D("CC_Total_nuebar",  ccint_title.c_str(),  nbins,E_min,E_max);
    hNC_nuebar["total"]    = new TH1D("NC_Total_nuebar",  ncint_title.c_str(),  nbins,E_min,E_max);
    hCCQE_nuebar["total"]  = new TH1D("CCQE_Total_nuebar",ccqeint_title.c_str(),nbins,E_min,E_max);
    
    std::string HNBF, HNF, HNBCC, HNCC, HNBNC, HNNC, HNCCQE, HNBCCQE;
    HNBF    = "Flux";
    HNBCC   = "CC";
    HNBNC   = "NC";
    HNBCCQE = "CCQE";

    for ( auto i = 0; i < n_parents; i++ ) {

      HNF    = HNBF+parent_strings[i]+"_numu";
      hFlux_numu[parent_strings[i]] = new TH1D(HNF.c_str(),flux_title.c_str(),nbins,E_min,E_max);

      HNCC   = HNBCC+parent_strings[i]+"_numu";
      hCC_numu[parent_strings[i]] = new TH1D(HNCC.c_str(),ccint_title.c_str(),nbins,E_min,E_max);
      
      HNNC   = HNBNC+parent_strings[i]+"_numu";
      hNC_numu[parent_strings[i]] = new TH1D(HNNC.c_str(),ncint_title.c_str(),nbins,E_min,E_max);

      HNCCQE = HNBCCQE+parent_strings[i]+"_numu";
      hCCQE_numu[parent_strings[i]] = new TH1D(HNCCQE.c_str(),ccqeint_title.c_str(),nbins,E_min,E_max);

      HNF    = HNBF+parent_strings[i]+"_numubar";
      hFlux_numubar[parent_strings[i]] = new TH1D(HNF.c_str(),flux_title.c_str(),nbins,E_min,E_max);

      HNCC  = HNBCC+parent_strings[i]+"_numubar";
      hCC_numubar[parent_strings[i]] = new TH1D(HNCC.c_str(),ccint_title.c_str(),nbins,E_min,E_max);
      
      HNNC  = HNBNC+parent_strings[i]+"_numubar";
      hNC_numubar[parent_strings[i]] = new TH1D(HNNC.c_str(),ncint_title.c_str(),nbins,E_min,E_max);

      HNCCQE = HNBCCQE+parent_strings[i]+"_numubar";
      hCCQE_numubar[parent_strings[i]] = new TH1D(HNCCQE.c_str(),ccqeint_title.c_str(),nbins,E_min,E_max);

      HNF    = HNBF+parent_strings[i]+"_nue";
      hFlux_nue[parent_strings[i]] = new TH1D(HNF.c_str(),flux_title.c_str(),nbins,E_min,E_max);

      HNCC  = HNBCC+parent_strings[i]+"_nue";
      hCC_nue[parent_strings[i]] = new TH1D(HNCC.c_str(),ccint_title.c_str(),nbins,E_min,E_max);
      
      HNNC  = HNBNC+parent_strings[i]+"_nue";
      hNC_nue[parent_strings[i]] = new TH1D(HNNC.c_str(),ncint_title.c_str(),nbins,E_min,E_max);

      HNCCQE = HNBCCQE+parent_strings[i]+"_nue";
      hCCQE_nue[parent_strings[i]] = new TH1D(HNCCQE.c_str(),ccqeint_title.c_str(),nbins,E_min,E_max);

      HNF    = HNBF+parent_strings[i]+"_nuebar";
      hFlux_nuebar[parent_strings[i]] = new TH1D(HNF.c_str(),flux_title.c_str(),nbins,E_min,E_max);

      HNCC  = HNBCC+parent_strings[i]+"_nuebar";
      hCC_nuebar[parent_strings[i]] = new TH1D(HNCC.c_str(),ccint_title.c_str(),nbins,E_min,E_max);
      
      HNNC  = HNBNC+parent_strings[i]+"_nuebar";
      hNC_nuebar[parent_strings[i]] = new TH1D(HNNC.c_str(),ncint_title.c_str(),nbins,E_min,E_max);
      
      HNCCQE = HNBCCQE+parent_strings[i]+"_nuebar";
      hCCQE_nuebar[parent_strings[i]] = new TH1D(HNCCQE.c_str(),ccqeint_title.c_str(),nbins,E_min,E_max);

    }
    
    for ( Int_t i = 0; i < fNuMIChain->GetEntries(); i++ ) {

      if ( i%5000000 == 0 ) std::cout << " >> " << i << " events stored." << std::endl; 

      fNuMIChain->GetEntry(i);

      if ( ( fvz > fLowerVzLimit ) && ( fvz < fUpperVzLimit ) && ( fE > fEnergyCut ) ) {

	if ( fIsBottom || fIsLength ) {
	  if ( fpdg == 14 ) {
	    hFlux_numu["total"]->Fill(fE);
	    if ( fndecay == 1 || fndecay == 2 || fndecay == 3 || fndecay == 4 ) hFlux_numu["_K0L"]->Fill(fE);
	    if ( fndecay == 5 || fndecay == 6 || fndecay == 7 )                 hFlux_numu["_K+"]->Fill(fE);
	    if ( fndecay == 8 || fndecay == 9 || fndecay == 10 )                hFlux_numu["_K-"]->Fill(fE);
	    if ( fndecay == 11 )                                                hFlux_numu["_mu+"]->Fill(fE);
	    if ( fndecay == 12 )                                                hFlux_numu["_mu-"]->Fill(fE);
	    if ( fndecay == 13 )                                                hFlux_numu["_pi+"]->Fill(fE);
	    if ( fndecay == 14 )                                                hFlux_numu["_pi-"]->Fill(fE);
	    if ( fndecay == 999 )                                               hFlux_numu["_other"]->Fill(fE);
	  } // pdg == numu
	  if ( fpdg == -14 ) {
	    hFlux_numubar["total"]->Fill(fE);
	    if ( fndecay == 1 || fndecay == 2 || fndecay == 3 || fndecay == 4 ) hFlux_numubar["_K0L"]->Fill(fE);
	    if ( fndecay == 5 || fndecay == 6 || fndecay == 7 )                 hFlux_numubar["_K+"]->Fill(fE);
	    if ( fndecay == 8 || fndecay == 9 || fndecay == 10 )                hFlux_numubar["_K-"]->Fill(fE);
	    if ( fndecay == 11 )                                                hFlux_numubar["_mu+"]->Fill(fE);
	    if ( fndecay == 12 )                                                hFlux_numubar["_mu-"]->Fill(fE);
	    if ( fndecay == 13 )                                                hFlux_numubar["_pi+"]->Fill(fE);
	    if ( fndecay == 14 )                                                hFlux_numubar["_pi-"]->Fill(fE);
	    if ( fndecay == 999 )                                               hFlux_numubar["_other"]->Fill(fE);
	  } // pdg == numubar
	  if ( fpdg == 12 ) {
	    hFlux_nue["total"]->Fill(fE);
	    if ( fndecay == 1 || fndecay == 2 || fndecay == 3 || fndecay == 4 ) hFlux_nue["_K0L"]->Fill(fE);
	    if ( fndecay == 5 || fndecay == 6 || fndecay == 7 )                 hFlux_nue["_K+"]->Fill(fE);
	    if ( fndecay == 8 || fndecay == 9 || fndecay == 10 )                hFlux_nue["_K-"]->Fill(fE);
	    if ( fndecay == 11 )                                                hFlux_nue["_mu+"]->Fill(fE);
	    if ( fndecay == 12 )                                                hFlux_nue["_mu-"]->Fill(fE);
	    if ( fndecay == 13 )                                                hFlux_nue["_pi+"]->Fill(fE);
	    if ( fndecay == 14 )                                                hFlux_nue["_pi-"]->Fill(fE);
	    if ( fndecay == 999 )                                               hFlux_nue["_other"]->Fill(fE);
	  } // pdg == nue
	  if ( fpdg == -12 ) {
	    hFlux_nuebar["total"]->Fill(fE);
	    if ( fndecay == 1 || fndecay == 2 || fndecay == 3 || fndecay == 4 ) hFlux_nuebar["_K0L"]->Fill(fE);
	    if ( fndecay == 5 || fndecay == 6 || fndecay == 7 )                 hFlux_nuebar["_K+"]->Fill(fE);
	    if ( fndecay == 8 || fndecay == 9 || fndecay == 10 )                hFlux_nuebar["_K-"]->Fill(fE);
	    if ( fndecay == 11 )                                                hFlux_nuebar["_mu+"]->Fill(fE);
	    if ( fndecay == 12 )                                                hFlux_nuebar["_mu-"]->Fill(fE);
	    if ( fndecay == 13 )                                                hFlux_nuebar["_pi+"]->Fill(fE);
	    if ( fndecay == 14 )                                                hFlux_nuebar["_pi-"]->Fill(fE);
	    if ( fndecay == 999 )                                               hFlux_nuebar["_other"]->Fill(fE);
	  } // pdg == nuebar
	} // length or bottom
	
	if ( fIsNormal ) {
	  if ( fpz > 0 ) {
	    if ( fpdg == 14 ) {
	      hFlux_numu["total"]->Fill(fE);
	      if ( fndecay == 1 || fndecay == 2 || fndecay == 3 || fndecay == 4 ) hFlux_numu["_K0L"]->Fill(fE);
	      if ( fndecay == 5 || fndecay == 6 || fndecay == 7 )                 hFlux_numu["_K+"]->Fill(fE);
	      if ( fndecay == 8 || fndecay == 9 || fndecay == 10 )                hFlux_numu["_K-"]->Fill(fE);
	      if ( fndecay == 11 )                                                hFlux_numu["_mu+"]->Fill(fE);
	      if ( fndecay == 12 )                                                hFlux_numu["_mu-"]->Fill(fE);
	      if ( fndecay == 13 )                                                hFlux_numu["_pi+"]->Fill(fE);
	      if ( fndecay == 14 )                                                hFlux_numu["_pi-"]->Fill(fE);
	      if ( fndecay == 999 )                                               hFlux_numu["_other"]->Fill(fE);
	    } // pdg == numu
	    if ( fpdg == -14 ) {
	      hFlux_numubar["total"]->Fill(fE);
	      if ( fndecay == 1 || fndecay == 2 || fndecay == 3 || fndecay == 4 ) hFlux_numubar["_K0L"]->Fill(fE);
	      if ( fndecay == 5 || fndecay == 6 || fndecay == 7 )                 hFlux_numubar["_K+"]->Fill(fE);
	      if ( fndecay == 8 || fndecay == 9 || fndecay == 10 )                hFlux_numubar["_K-"]->Fill(fE);
	      if ( fndecay == 11 )                                                hFlux_numubar["_mu+"]->Fill(fE);
	      if ( fndecay == 12 )                                                hFlux_numubar["_mu-"]->Fill(fE);
	      if ( fndecay == 13 )                                                hFlux_numubar["_pi+"]->Fill(fE);
	      if ( fndecay == 14 )                                                hFlux_numubar["_pi-"]->Fill(fE);
	      if ( fndecay == 999 )                                               hFlux_numubar["_other"]->Fill(fE);
	    } // pdg == numubar
	    if ( fpdg == 12 ) {
	      hFlux_nue["total"]->Fill(fE);
	      if ( fndecay == 1 || fndecay == 2 || fndecay == 3 || fndecay == 4 ) hFlux_nue["_K0L"]->Fill(fE);
	      if ( fndecay == 5 || fndecay == 6 || fndecay == 7 )                 hFlux_nue["_K+"]->Fill(fE);
	      if ( fndecay == 8 || fndecay == 9 || fndecay == 10 )                hFlux_nue["_K-"]->Fill(fE);
	      if ( fndecay == 11 )                                                hFlux_nue["_mu+"]->Fill(fE);
	      if ( fndecay == 12 )                                                hFlux_nue["_mu-"]->Fill(fE);
	      if ( fndecay == 13 )                                                hFlux_nue["_pi+"]->Fill(fE);
	      if ( fndecay == 14 )                                                hFlux_nue["_pi-"]->Fill(fE);
	      if ( fndecay == 999 )                                               hFlux_nue["_other"]->Fill(fE);
	    } // pdg == nue
	    if ( fpdg == -12 ) {
	      hFlux_nuebar["total"]->Fill(fE);
	      if ( fndecay == 1 || fndecay == 2 || fndecay == 3 || fndecay == 4 ) hFlux_nuebar["_K0L"]->Fill(fE);
	      if ( fndecay == 5 || fndecay == 6 || fndecay == 7 )                 hFlux_nuebar["_K+"]->Fill(fE);
	      if ( fndecay == 8 || fndecay == 9 || fndecay == 10 )                hFlux_nuebar["_K-"]->Fill(fE);
	      if ( fndecay == 11 )                                                hFlux_nuebar["_mu+"]->Fill(fE);
	      if ( fndecay == 12 )                                                hFlux_nuebar["_mu-"]->Fill(fE);
	      if ( fndecay == 13 )                                                hFlux_nuebar["_pi+"]->Fill(fE);
	      if ( fndecay == 14 )                                                hFlux_nuebar["_pi-"]->Fill(fE);
	      if ( fndecay == 999 )                                               hFlux_nuebar["_other"]->Fill(fE);
	    } // pdg == nuebar
	  } // pz cut
	}  // if isnormal
      } // vtx cut
    } // for all entries in chain
    
    TFile *out_file = new TFile(out_file_name.c_str(),"RECREATE");
    for ( auto const& entry : hFlux_numu ) {
      entry.second->Scale(1.0/(area_factor*fNFluxFiles*3.14159265));
      entry.second->Write();
    }
    for ( auto const& entry : hFlux_numubar ) {
      entry.second->Scale(1.0/(area_factor*fNFluxFiles*3.14159265));
      entry.second->Write();
    }
    for ( auto const& entry : hFlux_nue ) {
      entry.second->Scale(1.0/(area_factor*fNFluxFiles*3.14159265));
      entry.second->Write();
    }
    for ( auto const& entry : hFlux_nuebar ) {
      entry.second->Scale(1.0/(area_factor*fNFluxFiles*3.14159265));
      entry.second->Write();
    }

    Double_t hist_val, energy, xsecval, filler;

    for ( auto const& hist : hFlux_numu ) {
      for ( Int_t i = 0; i < hist.second->GetNbinsX(); i++ ) {
	hist_val = hist.second->GetBinContent(i+1);
	energy   = hist.second->GetBinCenter(i+1);

	// CC
	xsecval  = fCCxsec_numu->Eval(energy);
	filler   = xsecval*hist_val;
	hCC_numu[hist.first]->SetBinContent(i+1,filler);

	// NC
	xsecval  = fNCxsec_numu->Eval(energy);
	filler   = xsecval*hist_val;
	hNC_numu[hist.first]->SetBinContent(i+1,filler);

	// CCQE
	xsecval  = fCCQExsec_numu->Eval(energy);
	filler   = xsecval*hist_val;
	hCCQE_numu[hist.first]->SetBinContent(i+1,filler);
      }
    }

    for ( auto const& hist : hFlux_numubar ) {
      for ( Int_t i = 0; i < hist.second->GetNbinsX(); i++ ) {
	hist_val = hist.second->GetBinContent(i+1);
	energy   = hist.second->GetBinCenter(i+1);

	// CC
	xsecval  = fCCxsec_numubar->Eval(energy);
	filler   = xsecval*hist_val;
	hCC_numubar[hist.first]->SetBinContent(i+1,filler);

	// NC
	xsecval  = fNCxsec_numubar->Eval(energy);
	filler   = xsecval*hist_val;
	hNC_numubar[hist.first]->SetBinContent(i+1,filler);

	// CCQE
	xsecval  = fCCQExsec_numubar->Eval(energy);
	filler   = xsecval*hist_val;
	hCCQE_numubar[hist.first]->SetBinContent(i+1,filler);
      }
    }

    for ( auto const& hist : hFlux_nue ) {
      for ( Int_t i = 0; i < hist.second->GetNbinsX(); i++ ) {
	hist_val = hist.second->GetBinContent(i+1);
	energy   = hist.second->GetBinCenter(i+1);

	// CC
	xsecval  = fCCxsec_nue->Eval(energy);
	if ( energy < 0.100 )
	  xsecval = fLowExsec_nue->Eval(energy);
	filler   = xsecval*hist_val;
	hCC_nue[hist.first]->SetBinContent(i+1,filler);

	// NC
	xsecval  = fNCxsec_nue->Eval(energy);
	filler   = xsecval*hist_val;
	hNC_nue[hist.first]->SetBinContent(i+1,filler);

	// CCQE
	xsecval  = fCCQExsec_nue->Eval(energy);
	if ( energy < 0.100 )
	  xsecval = fLowExsec_nue->Eval(energy);
	filler   = xsecval*hist_val;
	hCCQE_nue[hist.first]->SetBinContent(i+1,filler);
      }
    }
    
    for ( auto const& hist : hFlux_nuebar ) {
      for ( Int_t i = 0; i < hist.second->GetNbinsX(); i++ ) {
	hist_val = hist.second->GetBinContent(i+1);
	energy   = hist.second->GetBinCenter(i+1);

	// CC
	xsecval  = fCCxsec_nuebar->Eval(energy);
	filler   = xsecval*hist_val;
	hCC_nuebar[hist.first]->SetBinContent(i+1,filler);

	// NC
	xsecval  = fNCxsec_nuebar->Eval(energy);
	filler   = xsecval*hist_val;
	hNC_nuebar[hist.first]->SetBinContent(i+1,filler);
	
	// CCQE
	xsecval  = fCCQExsec_nuebar->Eval(energy);
	filler   = xsecval*hist_val;
	hCCQE_nuebar[hist.first]->SetBinContent(i+1,filler);
      }
    }
    
    for ( auto const& entry : hCC_numu ) {
      entry.second->Scale(Xsec_factor);
      entry.second->Write();
    }
    for ( auto const& entry : hCC_numubar ) {
      entry.second->Scale(Xsec_factor);
      entry.second->Write();
    }
    for ( auto const& entry : hCC_nue ) {
      entry.second->Scale(Xsec_factor);
      entry.second->Write();
    }
    for ( auto const& entry : hCC_nuebar ) {
      entry.second->Scale(Xsec_factor);
      entry.second->Write();
    }

    for ( auto const& entry : hNC_numu ) {
      entry.second->Scale(Xsec_factor);
      entry.second->Write();
    }
    for ( auto const& entry : hNC_numubar ) {
      entry.second->Scale(Xsec_factor);
      entry.second->Write();
    }
    for ( auto const& entry : hNC_nue ) {
      entry.second->Scale(Xsec_factor);
      entry.second->Write();
    }
    for ( auto const& entry : hNC_nuebar ) {
      entry.second->Scale(Xsec_factor);
      entry.second->Write();
    }

    for ( auto const& entry : hCCQE_numu ) {
      entry.second->Scale(Xsec_factor);
      entry.second->Write();
    }
    for ( auto const& entry : hCCQE_numubar ) {
      entry.second->Scale(Xsec_factor);
      entry.second->Write();
    }
    for ( auto const& entry : hCCQE_nue ) {
      entry.second->Scale(Xsec_factor);
      entry.second->Write();
    }
    for ( auto const& entry : hCCQE_nuebar ) {
      entry.second->Scale(Xsec_factor);
      entry.second->Write();
    }

    out_file->Close();

  }
  
}
