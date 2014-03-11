#include "simpleAna2.hh"
#include "TH1D.h"
#include "TH2D.h"

namespace numi {
  
  simpleAna2::simpleAna2(const std::string& file_name)
  {
    fFile = new TFile(file_name.c_str());
    fNuMITree = dynamic_cast<TTree*> (fFile->Get("NuMI"));
    fNEvents = fNuMITree->GetEntries();
  }
  
  simpleAna2::~simpleAna2() {}
  
  
  std::vector< Double_t > simpleAna2::VectorV(const std::string& var)
  {
    std::vector< Double_t > temp_vec;
    Double_t temp_var;
    fNuMITree->SetBranchAddress(var.c_str(),&temp_var);
    for ( UInt_t i = 0; i < fNEvents; ++i ) {
      fNuMITree->GetEntry(i);
      temp_vec.push_back(temp_var);
    }
    return temp_vec;
  }
  
}
