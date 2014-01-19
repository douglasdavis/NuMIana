#include "LArAna.hh"
#include "TBranch.h"

namespace lar {
  
  LArAna::LArAna() {}
  
  LArAna::LArAna(const std::string& file_name)
  {
    fFileName = file_name;
    fFile = new TFile(file_name.c_str());
    fTree = (TTree*)fFile->Get("LArNuMIana/LArNuMIanaSimulation");

    double _NuIntVtxX, _NuIntVtxY, _NuIntVtxZ, _NuEnergy;
    double _HadronDecayX, _HadronDecayY, _HadronDecayZ;
    bool _CCint, _CCQEint, _NCint, _NCQEint;
    int _Event, _SubRun, _Run;

    std::vector<int>    *_TrackID = 0;
    std::vector<int>    *_PdgCode = 0;
    std::vector<double> *_StartX  = 0;
    std::vector<double> *_StartY  = 0;
    std::vector<double> *_StartZ  = 0;
    std::vector<double> *_StartPX = 0;
    std::vector<double> *_StartPY = 0;
    std::vector<double> *_StartPZ = 0;
    std::vector<double> *_StartE  = 0;
    
    fTree->SetBranchAddress("NuIntVtxX",   &_NuIntVtxX);
    fTree->SetBranchAddress("NuIntVtxY",   &_NuIntVtxY);
    fTree->SetBranchAddress("NuIntVtxZ",   &_NuIntVtxZ);
    fTree->SetBranchAddress("HadronDecayX",&_HadronDecayX);
    fTree->SetBranchAddress("HadronDecayY",&_HadronDecayY);
    fTree->SetBranchAddress("HadronDecayZ",&_HadronDecayZ);
    fTree->SetBranchAddress("CCint",       &_CCint);
    fTree->SetBranchAddress("CCQEint",     &_CCQEint);
    fTree->SetBranchAddress("NCint",       &_NCint);
    fTree->SetBranchAddress("NCQEint",     &_NCQEint);

    fTree->SetBranchAddress("TrackID",&_TrackID);
    fTree->SetBranchAddress("PdgCode",&_PdgCode);
    fTree->SetBranchAddress("StartX", &_StartX);
    fTree->SetBranchAddress("StartY", &_StartY);
    fTree->SetBranchAddress("StartZ", &_StartZ);
    fTree->SetBranchAddress("StartPX",&_StartPX);
    fTree->SetBranchAddress("StartPY",&_StartPY);
    fTree->SetBranchAddress("StartPZ",&_StartPZ);
    fTree->SetBranchAddress("StartE", &_StartE);

    TBranch *b_TrackID = fTree->GetBranch("TrackID");
    TBranch *b_PdgCode = fTree->GetBranch("PdgCode");
    TBranch *b_StartX  = fTree->GetBranch("StartX");
    TBranch *b_StartY  = fTree->GetBranch("StartY");
    TBranch *b_StartZ  = fTree->GetBranch("StartZ");
    TBranch *b_StartPX = fTree->GetBranch("StartPX");
    TBranch *b_StartPY = fTree->GetBranch("StartPY");
    TBranch *b_StartPZ = fTree->GetBranch("StartPZ");
    TBranch *b_StartE  = fTree->GetBranch("StartE");

    for ( int i = 0; i < fTree->GetEntries(); i++ ) {
      fTree->GetEntry(i);
      
      fNuIntVtxX.push_back(_NuIntVtxX);
      fNuIntVtxY.push_back(_NuIntVtxY);
      fNuIntVtxZ.push_back(_NuIntVtxZ);
      fHadronDecayX.push_back(_HadronDecayX);
      fHadronDecayY.push_back(_HadronDecayY);
      fHadronDecayZ.push_back(_HadronDecayZ);
      fCCint.push_back(_CCint);
      fCCQEint.push_back(_CCQEint);
      fNCint.push_back(_NCint);
      fNCQEint.push_back(_NCQEint);
      
      b_TrackID->GetEntry(i);
      b_PdgCode->GetEntry(i);
      b_StartX->GetEntry(i);
      b_StartY->GetEntry(i);
      b_StartZ->GetEntry(i);
      b_StartPX->GetEntry(i);
      b_StartPY->GetEntry(i);
      b_StartPZ->GetEntry(i);
      b_StartE->GetEntry(i);

      fTrackID.push_back(*_TrackID);
      fPdgCode.push_back(*_PdgCode);
      fStartX.push_back(*_StartX);
      fStartY.push_back(*_StartY);
      fStartZ.push_back(*_StartZ);
      fStartPX.push_back(*_StartPX);
      fStartPY.push_back(*_StartPY);
      fStartPZ.push_back(*_StartPZ);
      fStartE.push_back(*_StartE);
    }
  }
  
  LArAna::~LArAna() {}
  
  void LArAna::FillTH1D(TH1D& histogram, const std::vector<double>& values)
  {
    for ( auto const &val : values )
      histogram.Fill(val);
  }
  
  void LArAna::FillTH1D(TH1D& histogram, const std::vector< std::vector<double> >& values)
  {
    for ( auto const &vec : values )
      for ( auto const &val : vec ) 
	histogram.Fill(val);    
  }
}
