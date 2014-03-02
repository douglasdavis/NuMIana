#ifndef EVRATE_HH
#define EVRATE_HH

#include <iostream>
#include <map>
#include "TFile.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TDirectory.h"

namespace numi {
  
  class EvRate {
    
  private:
    
    TFile      *fFluxFile;
    TFile      *fGenieFile;
    TDirectory *fDir;

    std::map< std::string, TGraph* > fXsecGraphs;
  
  public:
  
    EvRate(const std::string& flux_file_name,
	   const std::string& genie_file_name,
	   const Int_t& nu_pdg);
  
    virtual ~EvRate();
  
  };

}

#endif
