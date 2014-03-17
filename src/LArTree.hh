#ifndef LARTREE_H
#define LARTREE_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>

namespace numi {

  class LArTree {

  public :

    TTree                  *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t                   fCurrent; //!current Tree number in a TChain

    Int_t                   NuPdgCode;
    Double_t                NuPx;
    Double_t                NuPy;
    Double_t                NuPz;
    Double_t                NuVx;
    Double_t                NuVy;
    Double_t                NuVz;
    Double_t                NuE;
    Int_t                   LeptonPdgCode;
    Double_t                LeptonVx;
    Double_t                LeptonVy;
    Double_t                LeptonVz;
    Double_t                LeptonPx;
    Double_t                LeptonPy;
    Double_t                LeptonPz;
    Double_t                LeptonE;
    Double_t                LeptonThetaXZ2;
    Double_t                LeptonThetaYZ2;
    Double_t                LeptonThetaXZ;
    Double_t                LeptonThetaYZ;
    Bool_t                  CCint;
    Bool_t                  CCQEint;
    Bool_t                  NCint;
    Bool_t                  NCQEint;
    Int_t                   Event;
    Int_t                   SubRun;
    Int_t                   Run;
    Double_t                POT;
    std::vector<Int_t>     *TrackID;
    std::vector<Int_t>     *PdgCode;
    std::vector<Double_t>  *StartVx;
    std::vector<Double_t>  *StartVy;
    std::vector<Double_t>  *StartVz;
    std::vector<Double_t>  *StartPx;
    std::vector<Double_t>  *StartPy;
    std::vector<Double_t>  *StartPz;
    std::vector<Double_t>  *StartE;
    Int_t                   flux_run;
    Int_t                   flux_evtno;
    Double_t                flux_tpx;
    Double_t                flux_tpy;
    Double_t                flux_tpz;
    Int_t                   flux_tptype;
    Double_t                flux_vx;
    Double_t                flux_vy;
    Double_t                flux_vz;
    Int_t                   flux_ndecay;
    Int_t                   flux_ppmedium;

    TBranch                *b_NuPdgCode;   //!
    TBranch                *b_NuPx;   //!
    TBranch                *b_NuPy;   //!
    TBranch                *b_NuPz;   //!
    TBranch                *b_NuVx;   //!
    TBranch                *b_NuVy;   //!
    TBranch                *b_NuVz;   //!
    TBranch                *b_NuE;   //!
    TBranch                *b_LeptonPdgCode;   //!
    TBranch                *b_LeptonVx;   //!
    TBranch                *b_LeptonVy;   //!
    TBranch                *b_LeptonVz;   //!
    TBranch                *b_LeptonPx;   //!
    TBranch                *b_LeptonPy;   //!
    TBranch                *b_LeptonPz;   //!
    TBranch                *b_LeptonE;   //!
    TBranch                *b_LeptonThetaXZ2;   //!
    TBranch                *b_LeptonThetaYZ2;   //!
    TBranch                *b_LeptonThetaXZ;   //!
    TBranch                *b_LeptonThetaYZ;   //!
    TBranch                *b_CCint;   //!
    TBranch                *b_CCQEint;   //!
    TBranch                *b_NCint;   //!
    TBranch                *b_NCQEint;   //!
    TBranch                *b_Event;   //!
    TBranch                *b_SubRun;   //!
    TBranch                *b_Run;   //!
    TBranch                *b_POT;   //!
    TBranch                *b_TrackID;   //!
    TBranch                *b_PdgCode;   //!
    TBranch                *b_StartVx;   //!
    TBranch                *b_StartVy;   //!
    TBranch                *b_StartVz;   //!
    TBranch                *b_StartPx;   //!
    TBranch                *b_StartPy;   //!
    TBranch                *b_StartPz;   //!
    TBranch                *b_StartE;   //!
    TBranch                *b_flux_run;   //!
    TBranch                *b_flux_evtno;   //!
    TBranch                *b_flux_tpx;   //!
    TBranch                *b_flux_tpy;   //!
    TBranch                *b_flux_tpz;   //!
    TBranch                *b_flux_tptype;   //!
    TBranch                *b_flux_vx;   //!
    TBranch                *b_flux_vy;   //!
    TBranch                *b_flux_vz;   //!
    TBranch                *b_flux_ndecay;   //!
    TBranch                *b_flux_ppmedium;   //!

    LArTree(TTree *tree=0, std::string file_name=0);
    virtual ~LArTree();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop();
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);

  };

}

#endif
