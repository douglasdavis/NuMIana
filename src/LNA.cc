#include "LNA.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <cmath>

namespace numi {

  LNA::LNA(TTree *tree, std::string file_name) : fChain(0) 
  {
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(file_name.c_str());
      if (!f || !f->IsOpen()) {
	f = new TFile(file_name.c_str());
      }
      std::string dir_string = file_name+":/LArNuMIana";
      TDirectory * dir = (TDirectory*)f->Get(dir_string.c_str());
      dir->GetObject("LArNuMIanaSimulation",tree);
      fPOTHist  = (TH1D*)f->Get("POT");
      fTotalPOT = fPOTHist->GetMean()*fPOTHist->GetEntries();
      Init(tree);
    }
  }

  LNA::~LNA()
  {
    if (!fChain) return;
    delete fChain->GetCurrentFile();
  }

  Int_t LNA::GetEntry(Long64_t entry)
  {
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
  }

  Long64_t LNA::LoadTree(Long64_t entry)
  {
    // Set the environment to read one entry
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
    }
    return centry;
  }

  void LNA::Init(TTree *tree)
  {
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    // Set object pointer
    Process = 0;
    ProdMaterial = 0;
    EndMaterial = 0;
    ProdVolume = 0;
    EndVolume = 0;
    TrackID = 0;
    ParentID = 0;
    PdgCode = 0;
    StartVx = 0;
    StartVy = 0;
    StartVz = 0;
    StartPx = 0;
    StartPy = 0;
    StartPz = 0;
    StartE = 0;
    InTPC = 0;
    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("NuPdgCode", &NuPdgCode, &b_NuPdgCode);
    fChain->SetBranchAddress("NuPx", &NuPx, &b_NuPx);
    fChain->SetBranchAddress("NuPy", &NuPy, &b_NuPy);
    fChain->SetBranchAddress("NuPz", &NuPz, &b_NuPz);
    fChain->SetBranchAddress("NuVx", &NuVx, &b_NuVx);
    fChain->SetBranchAddress("NuVy", &NuVy, &b_NuVy);
    fChain->SetBranchAddress("NuVz", &NuVz, &b_NuVz);
    fChain->SetBranchAddress("VertexInTPC", &VertexInTPC, &b_VertexInTPC);
    fChain->SetBranchAddress("NuE", &NuE, &b_NuE);
    fChain->SetBranchAddress("LeptonPdgCode", &LeptonPdgCode, &b_LeptonPdgCode);
    fChain->SetBranchAddress("LeptonVx", &LeptonVx, &b_LeptonVx);
    fChain->SetBranchAddress("LeptonVy", &LeptonVy, &b_LeptonVy);
    fChain->SetBranchAddress("LeptonVz", &LeptonVz, &b_LeptonVz);
    fChain->SetBranchAddress("LeptonPx", &LeptonPx, &b_LeptonPx);
    fChain->SetBranchAddress("LeptonPy", &LeptonPy, &b_LeptonPy);
    fChain->SetBranchAddress("LeptonPz", &LeptonPz, &b_LeptonPz);
    fChain->SetBranchAddress("LeptonE", &LeptonE, &b_LeptonE);
    fChain->SetBranchAddress("LeptonThetaXZ2", &LeptonThetaXZ2, &b_LeptonThetaXZ2);
    fChain->SetBranchAddress("LeptonThetaYZ2", &LeptonThetaYZ2, &b_LeptonThetaYZ2);
    fChain->SetBranchAddress("LeptonThetaXZ", &LeptonThetaXZ, &b_LeptonThetaXZ);
    fChain->SetBranchAddress("LeptonThetaYZ", &LeptonThetaYZ, &b_LeptonThetaYZ);
    fChain->SetBranchAddress("CCint", &CCint, &b_CCint);
    fChain->SetBranchAddress("CCQEint", &CCQEint, &b_CCQEint);
    fChain->SetBranchAddress("NCint", &NCint, &b_NCint);
    fChain->SetBranchAddress("NCQEint", &NCQEint, &b_NCQEint);
    fChain->SetBranchAddress("Event", &Event, &b_Event);
    fChain->SetBranchAddress("SubRun", &SubRun, &b_SubRun);
    fChain->SetBranchAddress("Run", &Run, &b_Run);
    fChain->SetBranchAddress("Process", &Process, &b_Process);
    fChain->SetBranchAddress("ProdMaterial", &ProdMaterial, &b_ProdMaterial);
    fChain->SetBranchAddress("EndMaterial", &EndMaterial, &b_EndMaterial);
    fChain->SetBranchAddress("ProdVolume", &ProdVolume, &b_ProdVolume);
    fChain->SetBranchAddress("EndVolume", &EndVolume, &b_EndVolume);
    fChain->SetBranchAddress("TrackID", &TrackID, &b_TrackID);
    fChain->SetBranchAddress("ParentID", &ParentID, &b_ParentID);
    fChain->SetBranchAddress("PdgCode", &PdgCode, &b_PdgCode);
    fChain->SetBranchAddress("StartVx", &StartVx, &b_StartVx);
    fChain->SetBranchAddress("StartVy", &StartVy, &b_StartVy);
    fChain->SetBranchAddress("StartVz", &StartVz, &b_StartVz);
    fChain->SetBranchAddress("StartPx", &StartPx, &b_StartPx);
    fChain->SetBranchAddress("StartPy", &StartPy, &b_StartPy);
    fChain->SetBranchAddress("StartPz", &StartPz, &b_StartPz);
    fChain->SetBranchAddress("StartE", &StartE, &b_StartE);
    fChain->SetBranchAddress("InTPC", &InTPC, &b_InTPC);
    fChain->SetBranchAddress("flux_run", &flux_run, &b_flux_run);
    fChain->SetBranchAddress("flux_evtno", &flux_evtno, &b_flux_evtno);
    fChain->SetBranchAddress("flux_tpx", &flux_tpx, &b_flux_tpx);
    fChain->SetBranchAddress("flux_tpy", &flux_tpy, &b_flux_tpy);
    fChain->SetBranchAddress("flux_tpz", &flux_tpz, &b_flux_tpz);
    fChain->SetBranchAddress("flux_tptype", &flux_tptype, &b_flux_tptype);
    fChain->SetBranchAddress("flux_vx", &flux_vx, &b_flux_vx);
    fChain->SetBranchAddress("flux_vy", &flux_vy, &b_flux_vy);
    fChain->SetBranchAddress("flux_vz", &flux_vz, &b_flux_vz);
    fChain->SetBranchAddress("flux_ndecay", &flux_ndecay, &b_flux_ndecay);
    fChain->SetBranchAddress("flux_ppmedium", &flux_ppmedium, &b_flux_ppmedium);
    Notify();
  }

  Bool_t LNA::Notify()
  {
    return kTRUE;
  }

  void LNA::Show(Long64_t entry)
  {
    if (!fChain) return;
    fChain->Show(entry);
  }

  Int_t LNA::Cut(Long64_t entry)
  {
    return 1;
  }

  void LNA::Loop()
  {
    if (fChain == 0) return;
    TH2D *h   = new TH2D("h",";p_{z};p_{T}",100,0,20,100,0,2);
    TH1D *pzh = new TH1D("pzh",";p_{z};",100,1,0);
    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if ( flux_evtno != 0 ) {
	double pt = std::sqrt(flux_tpx*flux_tpx+flux_tpy*flux_tpy);
	double pz = flux_tpz;
	h->Fill(pz,pt);
	pzh->Fill(NuPz);
      }
      
    }
    TCanvas *ch = new TCanvas();
    h->Draw("colz");
    TCanvas* cpzh = new TCanvas();
    pzh->Draw();
  }

}
