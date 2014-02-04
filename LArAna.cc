#include "LArAna.hh"
#include "TBranch.h"

LArAna::LArAna() {}
  
LArAna::LArAna(const std::string& file_name)
{
  fFileName = file_name;
  fFile = new TFile(file_name.c_str());
  fTree = (TTree*)fFile->Get("LArNuMIana/LArNuMIanaSimulation");
    
  int    _NuPdg, _LeptonPdg;
  double _NuPx, _NuPy, _NuPz, _LeptonPx, _LeptonPy, _LeptonPz;
  double _LeptonVx, _LeptonVy, _LeptonVz, _LeptonEnergy;
  double _LeptonThetaXZ2, _LeptonThetaYZ2;
  double _LeptonThetaXZ, _LeptonThetaYZ;
  double _NuIntVtxX, _NuIntVtxY, _NuIntVtxZ, _NuEnergy;
  double _HadronDecayX, _HadronDecayY, _HadronDecayZ;
  bool   _CCint, _CCQEint, _NCint, _NCQEint;
  int    _Event, _SubRun, _Run;
    
  std::vector<int>    *_TrackID = 0;
  std::vector<int>    *_PdgCode = 0;
  std::vector<double> *_StartVx  = 0;
  std::vector<double> *_StartVy  = 0;
  std::vector<double> *_StartVz  = 0;
  std::vector<double> *_StartPx = 0;
  std::vector<double> *_StartPy = 0;
  std::vector<double> *_StartPz = 0;
  std::vector<double> *_StartE  = 0;
    
  fTree->SetBranchAddress("NuPdg",         &_NuPdg);
  fTree->SetBranchAddress("LeptonPdg",     &_LeptonPdg);
  fTree->SetBranchAddress("NuPx",          &_NuPx);
  fTree->SetBranchAddress("NuPy",          &_NuPy);
  fTree->SetBranchAddress("NuPz",          &_NuPz);
  fTree->SetBranchAddress("LeptonPx",      &_LeptonPx);
  fTree->SetBranchAddress("LeptonPy",      &_LeptonPy);
  fTree->SetBranchAddress("LeptonPz",      &_LeptonPz);
  fTree->SetBranchAddress("LeptonVx",      &_LeptonVx);
  fTree->SetBranchAddress("LeptonVy",      &_LeptonVy);
  fTree->SetBranchAddress("LeptonVz",      &_LeptonVz);
  fTree->SetBranchAddress("LeptonThetaXZ2",&_LeptonThetaXZ2);
  fTree->SetBranchAddress("LeptonThetaYZ2",&_LeptonThetaYZ2);
  fTree->SetBranchAddress("LeptonThetaXZ", &_LeptonThetaXZ);
  fTree->SetBranchAddress("LeptonThetaYZ", &_LeptonThetaYZ);
  fTree->SetBranchAddress("NuIntVtxX",     &_NuIntVtxX);
  fTree->SetBranchAddress("NuIntVtxY",     &_NuIntVtxY);
  fTree->SetBranchAddress("NuIntVtxZ",     &_NuIntVtxZ);
  fTree->SetBranchAddress("NuEnergy",      &_NuEnergy);
  fTree->SetBranchAddress("HadronDecayX",  &_HadronDecayX);
  fTree->SetBranchAddress("HadronDecayY",  &_HadronDecayY);
  fTree->SetBranchAddress("HadronDecayZ",  &_HadronDecayZ);
  fTree->SetBranchAddress("CCint",         &_CCint);
  fTree->SetBranchAddress("CCQEint",       &_CCQEint);
  fTree->SetBranchAddress("NCint",         &_NCint);
  fTree->SetBranchAddress("NCQEint",       &_NCQEint);
    
  fTree->SetBranchAddress("TrackID",&_TrackID);
  fTree->SetBranchAddress("PdgCode",&_PdgCode);
  fTree->SetBranchAddress("StartVx",&_StartVx);
  fTree->SetBranchAddress("StartVy",&_StartVy);
  fTree->SetBranchAddress("StartVz",&_StartVz);
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
    fNuPdg.push_back(_NuPdg);
    fLeptonPdg.push_back(_LeptonPdg);
    fNuPx.push_back(_NuPx);
    fNuPy.push_back(_NuPy);
    fNuPz.push_back(_NuPz);
    fNuEnergy.push_back(_NuEnergy);
    fLeptonVx.push_back(_LeptonVx);
    fLeptonVy.push_back(_LeptonVy);
    fLeptonVz.push_back(_LeptonVz);
    fLeptonPx.push_back(_LeptonPx);
    fLeptonPy.push_back(_LeptonPy);
    fLeptonPz.push_back(_LeptonPz);
    fLeptonThetaXZ2.push_back(_LeptonThetaXZ2);
    fLeptonThetaYZ2.push_back(_LeptonThetaYZ2);
    fLeptonThetaXZ.push_back(_LeptonThetaXZ);
    fLeptonThetaYZ.push_back(_LeptonThetaYZ);
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

    fpPdgCodeStartPx.push_back(std::make_pair(*_PdgCode,*_StartPx));
    fpPdgCodeStartPy.push_back(std::make_pair(*_PdgCode,*_StartPy));
    fpPdgCodeStartPz.push_back(std::make_pair(*_PdgCode,*_StartPz));
    fpPdgCodeStartVx.push_back(std::make_pair(*_PdgCode,*_StartVx));
    fpPdgCodeStartVy.push_back(std::make_pair(*_PdgCode,*_StartVy));
    fpPdgCodeStartVz.push_back(std::make_pair(*_PdgCode,*_StartVz));
    fpPdgCodeStartE.push_back(std::make_pair(*_PdgCode,*_StartE));


  }

}
  
LArAna::~LArAna() {}
