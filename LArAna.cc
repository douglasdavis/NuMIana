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
    std::vector<double> *_StartVx  = 0;
    std::vector<double> *_StartVy  = 0;
    std::vector<double> *_StartVz  = 0;
    std::vector<double> *_StartPx = 0;
    std::vector<double> *_StartPy = 0;
    std::vector<double> *_StartPz = 0;
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
    fTree->SetBranchAddress("StartVx", &_StartVx);
    fTree->SetBranchAddress("StartVy", &_StartVy);
    fTree->SetBranchAddress("StartVz", &_StartVz);
    fTree->SetBranchAddress("StartPx",&_StartPx);
    fTree->SetBranchAddress("StartPy",&_StartPy);
    fTree->SetBranchAddress("StartPz",&_StartPz);
    fTree->SetBranchAddress("StartE", &_StartE);

    TBranch *b_TrackID = fTree->GetBranch("TrackID");
    TBranch *b_PdgCode = fTree->GetBranch("PdgCode");
    TBranch *b_StartVx  = fTree->GetBranch("StartVx");
    TBranch *b_StartVy  = fTree->GetBranch("StartVy");
    TBranch *b_StartVz  = fTree->GetBranch("StartVz");
    TBranch *b_StartPx = fTree->GetBranch("StartPx");
    TBranch *b_StartPy = fTree->GetBranch("StartPy");
    TBranch *b_StartPz = fTree->GetBranch("StartPz");
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
      b_StartVx->GetEntry(i);
      b_StartVy->GetEntry(i);
      b_StartVz->GetEntry(i);
      b_StartPx->GetEntry(i);
      b_StartPy->GetEntry(i);
      b_StartPz->GetEntry(i);
      b_StartE->GetEntry(i);

      fTrackID.push_back(*_TrackID);
      fPdgCode.push_back(*_PdgCode);
      fStartVx.push_back(*_StartVx);
      fStartVy.push_back(*_StartVy);
      fStartVz.push_back(*_StartVz);
      fStartPx.push_back(*_StartPx);
      fStartPy.push_back(*_StartPy);
      fStartPz.push_back(*_StartPz);
      fStartE.push_back(*_StartE);
    }
  }
  
  LArAna::~LArAna() {}
  
}
