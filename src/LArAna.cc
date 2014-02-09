///////////////////////////////////////////////////////////////////////////////
//  \brief   Methods of LArAna class (to analyze ntuples from LArNuMIana)
//  \author  douglasdavis@utexas.edu
///////////////////////////////////////////////////////////////////////////////

#include "LArAna.hh"
#include "TBranch.h"

LArAna::LArAna() {}
  
LArAna::LArAna(const std::string& file_name)
{
  fFileName         = file_name;
  fFile             = new TFile(file_name.c_str());
  fSimulationNtuple = (TTree*)fFile->Get("LArNuMIana/LArNuMIanaSimulation");
  fFluxNtuple       = (TTree*)fFile->Get("LArNuMIana/LArNuMIanaFlux");

  int    _NuPdg, _LeptonPdg;
  double _NuPx, _NuPy, _NuPz, _LeptonPx, _LeptonPy, _LeptonPz;
  double _LeptonVx, _LeptonVy, _LeptonVz, _LeptonEnergy;
  double _LeptonThetaXZ2, _LeptonThetaYZ2;
  double _LeptonThetaXZ, _LeptonThetaYZ;
  double _NuIntVtxX, _NuIntVtxY, _NuIntVtxZ, _NuEnergy;
  double vx, vy, vz;
  int    ppmedium, ndecay;
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
    
  fSimulationNtuple->SetBranchAddress("NuPdg",         &_NuPdg);
  fSimulationNtuple->SetBranchAddress("LeptonPdg",     &_LeptonPdg);
  fSimulationNtuple->SetBranchAddress("NuPx",          &_NuPx);
  fSimulationNtuple->SetBranchAddress("NuPy",          &_NuPy);
  fSimulationNtuple->SetBranchAddress("NuPz",          &_NuPz);
  fSimulationNtuple->SetBranchAddress("LeptonPx",      &_LeptonPx);
  fSimulationNtuple->SetBranchAddress("LeptonPy",      &_LeptonPy);
  fSimulationNtuple->SetBranchAddress("LeptonPz",      &_LeptonPz);
  fSimulationNtuple->SetBranchAddress("LeptonVx",      &_LeptonVx);
  fSimulationNtuple->SetBranchAddress("LeptonVy",      &_LeptonVy);
  fSimulationNtuple->SetBranchAddress("LeptonVz",      &_LeptonVz);
  fSimulationNtuple->SetBranchAddress("LeptonThetaXZ2",&_LeptonThetaXZ2);
  fSimulationNtuple->SetBranchAddress("LeptonThetaYZ2",&_LeptonThetaYZ2);
  fSimulationNtuple->SetBranchAddress("LeptonThetaXZ", &_LeptonThetaXZ);
  fSimulationNtuple->SetBranchAddress("LeptonThetaYZ", &_LeptonThetaYZ);
  fSimulationNtuple->SetBranchAddress("NuIntVtxX",     &_NuIntVtxX);
  fSimulationNtuple->SetBranchAddress("NuIntVtxY",     &_NuIntVtxY);
  fSimulationNtuple->SetBranchAddress("NuIntVtxZ",     &_NuIntVtxZ);
  fSimulationNtuple->SetBranchAddress("NuEnergy",      &_NuEnergy);

  fSimulationNtuple->SetBranchAddress("CCint",         &_CCint);
  fSimulationNtuple->SetBranchAddress("CCQEint",       &_CCQEint);
  fSimulationNtuple->SetBranchAddress("NCint",         &_NCint);
  fSimulationNtuple->SetBranchAddress("NCQEint",       &_NCQEint);
    
  fSimulationNtuple->SetBranchAddress("TrackID",&_TrackID);
  fSimulationNtuple->SetBranchAddress("PdgCode",&_PdgCode);
  fSimulationNtuple->SetBranchAddress("StartVx",&_StartVx);
  fSimulationNtuple->SetBranchAddress("StartVy",&_StartVy);
  fSimulationNtuple->SetBranchAddress("StartVz",&_StartVz);
  fSimulationNtuple->SetBranchAddress("StartPx",&_StartPx);
  fSimulationNtuple->SetBranchAddress("StartPy",&_StartPy);
  fSimulationNtuple->SetBranchAddress("StartPz",&_StartPz);
  fSimulationNtuple->SetBranchAddress("StartE", &_StartE);
    
  TBranch *b_TrackID = fSimulationNtuple->GetBranch("TrackID");
  TBranch *b_PdgCode = fSimulationNtuple->GetBranch("PdgCode");
  TBranch *b_StartVx = fSimulationNtuple->GetBranch("StartVx");
  TBranch *b_StartVy = fSimulationNtuple->GetBranch("StartVy");
  TBranch *b_StartVz = fSimulationNtuple->GetBranch("StartVz");
  TBranch *b_StartPx = fSimulationNtuple->GetBranch("StartPx");
  TBranch *b_StartPy = fSimulationNtuple->GetBranch("StartPy");
  TBranch *b_StartPz = fSimulationNtuple->GetBranch("StartPz");
  TBranch *b_StartE  = fSimulationNtuple->GetBranch("StartE");

  fFluxNtuple->SetBranchAddress("vx",      &vz);
  fFluxNtuple->SetBranchAddress("vy",      &vy);
  fFluxNtuple->SetBranchAddress("vz",      &vx);
  fFluxNtuple->SetBranchAddress("ppmedium",&ppmedium);
  fFluxNtuple->SetBranchAddress("ndecay",  &ndecay);

  for ( int i = 0; i < fSimulationNtuple->GetEntries(); ++i ) {
    fSimulationNtuple->GetEntry(i);
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
  
  for ( auto i = 0; i < fFluxNtuple->GetEntries(); ++i ) {
    fFluxNtuple->GetEntry(i);
    fvx.push_back(vx);
    fvy.push_back(vy);
    fvz.push_back(vz);
    fppmedium.push_back(ppmedium);
    fndecay.push_back(ndecay);
    fppmediumndecay.push_back(std::make_pair(ppmedium,ndecay));
  }

}
  
LArAna::~LArAna() {}
