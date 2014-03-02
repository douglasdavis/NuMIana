#include "EvRate.hh"
#include "TTree.h"

namespace numi {
  
  EvRate::EvRate(const std::string& flux_file_name,
		 const std::string& genie_file_name,
		 const Int_t& nu_pdg) {
    
    fFluxFile  = new TFile(flux_file_name.c_str());
    fGenieFile = new TFile(genie_file_name.c_str());

    if ( nu_pdg == 14 )
      fDir = (TDirectory*)fGenieFile->Get("nu_mu_Ar40");
    if ( nu_pdg == -14 )
      fDir = (TDirectory*)fGenieFile->Get("nu_mu_bar_Ar40");
    if ( nu_pdg == 12 )
      fDir = (TDirectory*)fGenieFile->Get("nu_e_Ar40");
    if ( nu_pdg == -12 )
      fDir = (TDirectory*)fGenieFile->Get("nu_e_bar_Ar40");
    
  }
  
  EvRate::~EvRate() {}
  
}
