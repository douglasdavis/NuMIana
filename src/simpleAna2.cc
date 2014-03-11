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
  
  
  std::vector< Double_t > simpleAna2::Vector_D(const std::string& var) const
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
  
  
  std::vector< std::pair < Int_t, Double_t > > simpleAna2::VectorPair_I_D(const std::string& var1,
									  const std::string& var2) const
  {
    std::vector< std::pair < Int_t, Double_t > > temp_vec;
    Double_t temp_d;
    Int_t    temp_i;
    fNuMITree->SetBranchAddress(var2.c_str(),&temp_d);
    fNuMITree->SetBranchAddress(var1.c_str(),&temp_i);
    for ( UInt_t i = 0; i < fNEvents; ++i) {
      fNuMITree->GetEntry(i);
      temp_vec.push_back(std::make_pair(temp_i,temp_d));
    }
    return temp_vec;
  }
    
}
