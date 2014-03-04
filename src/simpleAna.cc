///////////////////////////////////////////////////////////////////////////////
///  \brief   Methods of simpleAna class (to analyze simple flux ntuples)
///  \author  douglasdavis@utexas.edu
///////////////////////////////////////////////////////////////////////////////

#include "simpleAna.hh"

namespace numi {
  
  simpleAna::simpleAna() {}
  
  simpleAna::simpleAna(const std::vector< std::string >& file_names, const Bool_t& is_normal)
  {
    fNuMIChain = new TChain("NuMI");
    for ( auto const& j : file_names )
      fNuMIChain->Add(j.c_str());
    
    Double_t wgt, vtxx, vtxy, vtxz;
    Double_t dist, px, py, pz, E;
    Int_t    pdg;
    Double_t tpx, tpy, tpz, vx, vy, vz;
    Int_t    ndecay, ptype, ppmedium, tptype;
    Int_t    run, evtno, entryno;
  
    fNuMIChain->SetBranchAddress("wgt", &wgt);
    fNuMIChain->SetBranchAddress("vtxx",&vtxx);
    fNuMIChain->SetBranchAddress("vtxy",&vtxy);
    fNuMIChain->SetBranchAddress("vtxz",&vtxz);
    fNuMIChain->SetBranchAddress("dist",&dist);
    fNuMIChain->SetBranchAddress("px",  &px);
    fNuMIChain->SetBranchAddress("py",  &py);
    fNuMIChain->SetBranchAddress("pz",  &pz);
    fNuMIChain->SetBranchAddress("E",   &E);
    fNuMIChain->SetBranchAddress("pdg", &pdg);

    fNuMIChain->SetBranchAddress("tpx",&tpx);
    fNuMIChain->SetBranchAddress("tpy",&tpy);
    fNuMIChain->SetBranchAddress("tpz",&tpz);
    fNuMIChain->SetBranchAddress("vx", &vx);
    fNuMIChain->SetBranchAddress("vy", &vy);
    fNuMIChain->SetBranchAddress("vz", &vz);

    fNuMIChain->SetBranchAddress("ndecay",  &ndecay);
    fNuMIChain->SetBranchAddress("ppmedium",&ppmedium);
    fNuMIChain->SetBranchAddress("tptype",  &tptype);
    fNuMIChain->SetBranchAddress("run",     &run);
    fNuMIChain->SetBranchAddress("evtno",   &evtno);
    fNuMIChain->SetBranchAddress("entryno", &entryno);
    

    if ( is_normal ) {
      fNEvents = 0;
      for ( Int_t i = 0; i < fNuMIChain->GetEntries(); ++i ) {
	fNuMIChain->GetEntry(i);
	if ( pz > 0 ) {
	  fNEvents++;
	  fwgt.push_back(wgt);
	  fvtxx.push_back(vtxx);
	  fvtxy.push_back(vtxy);
	  fvtxz.push_back(vtxz);
	  fdist.push_back(dist);
	  fpx.push_back(px);
	  fpy.push_back(py);
	  fpz.push_back(pz);
	  fE.push_back(E);
	  fpdg.push_back(pdg);
	  ftpx.push_back(tpx);
	  ftpy.push_back(tpy);
	  ftpz.push_back(tpz);
	  fvx.push_back(vx);
	  fvy.push_back(vy);
	  fvz.push_back(vz);
	  fndecay.push_back(ndecay);
	  fppmedium.push_back(ppmedium);
	  ftptype.push_back(tptype);
	  frun.push_back(run);
	  fevtno.push_back(evtno);
	  fentryno.push_back(entryno);
	
	  fppmediumndecay.push_back(std::make_pair(ppmedium,ndecay));  
	  fPdgEnergy.push_back(std::make_pair(pdg,E));
	}
      }
      
    } else {
      fNEvents = fNuMIChain->GetEntries();
      for ( Int_t i = 0; i < fNuMIChain->GetEntries(); ++i ) {
	fNuMIChain->GetEntry(i);
	fwgt.push_back(wgt);
	fvtxx.push_back(vtxx);
	fvtxy.push_back(vtxy);
	fvtxz.push_back(vtxz);
	fdist.push_back(dist);
	fpx.push_back(px);
	fpy.push_back(py);
	fpz.push_back(pz);
	fE.push_back(E);
	fpdg.push_back(pdg);
	ftpx.push_back(tpx);
	ftpy.push_back(tpy);
	ftpz.push_back(tpz);
	fvx.push_back(vx);
	fvy.push_back(vy);
	fvz.push_back(vz);
	fndecay.push_back(ndecay);
	fppmedium.push_back(ppmedium);
	ftptype.push_back(tptype);
	frun.push_back(run);
	fevtno.push_back(evtno);
	fentryno.push_back(entryno);	

	fppmediumndecay.push_back(std::make_pair(ppmedium,ndecay));
	fPdgEnergy.push_back(std::make_pair(pdg,E));
      }
      
    }
  }

  simpleAna::~simpleAna() {}

  void simpleAna::PrintNeutrinos()
  {
    std::cout << " ** NEUTRINOS ** " << std::endl;
    Int_t numu = 0, numubar = 0, nue = 0, nuebar = 0;
    Int_t counter = 0;
    for ( Int_t n : fpdg ) {
      counter++;
      switch(n) {
      case 14:  numu++;    break;
      case -14: numubar++; break;
      case 12:  nue++;     break;
      case -12: nuebar++;  break;
      default:
	std::cout << "Warning in simpleAna::PrintNeutrinos(): Unkown pdg code: " << n << std::endl;
	break;
      }
    }
    std::cout << " numu    : " << numu    << " :: " 
	      << 100*(Double_t)numu/(Double_t)counter    << std::endl;
    std::cout << " numubar : " << numubar << " :: " 
	      << 100*(Double_t)numubar/(Double_t)counter << std::endl;
    std::cout << " nue     : " << nue     << " :: " 
	      << 100*(Double_t)nue/(Double_t)counter     << std::endl;
    std::cout << " nuebar  : " << nuebar  << " :: " 
	      << 100*(Double_t)nuebar/(Double_t)counter  << std::endl;
  }

  ///____________________________________________________________________________

  void simpleAna::PrintDecayLocations()
  {
    // target hall
    Int_t target_hall = 0;
    Int_t target = 0;
    Int_t horn_1 = 0;
    Int_t horn_2 = 0;
    // decay pipe
    Int_t decay_pipe = 0;
    Int_t decay_pipe_pre_ub = 0;
    Int_t decay_pipe_post_ub = 0;
    // Int_t absorber_etc
    Int_t absorber_etc = 0;

    std::cout << "** DECAY LOCATIONS **" << std::endl;
    std::cout << std::endl;
  }

}
