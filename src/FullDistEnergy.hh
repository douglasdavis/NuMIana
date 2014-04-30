#ifndef FULLDISTENERGY_HH
#define FULLDISTENERGY_HH

#include <iostream>
#include <vector>
#include "TTree.h"
#include "TFile.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TChain.h"

namespace numi {

  class FullDistEnergy {

  private:

    TChain    *fNuMIChain;
    TFile     *fGENIEFile;

    Bool_t     fIsNormal;
    Bool_t     fIsBottom;
    Bool_t     fIsLength;

    UInt_t     fNFluxFiles;
    Double_t   fPOTPerFluxFile;

    Double_t   fwgt;
    Double_t   fvtxx;
    Double_t   fvtxy;
    Double_t   fvtxz;
    Double_t   fdist;
    Double_t   fpx;
    Double_t   fpy;
    Double_t   fpz;
    Double_t   fE;
    Int_t      fpdg;

    Double_t   ftpx;
    Double_t   ftpy;
    Double_t   ftpz;
    Double_t   fvx;
    Double_t   fvy;
    Double_t   fvz;
    Int_t      fppmedium;
    Int_t      fndecay;
    Int_t      ftptype;
    Int_t      frun;
    Int_t      fevtno;
    Int_t      fentryno;

    Double_t   fBottomArea;
    Double_t   fLengthArea;
    Double_t   fNormalArea;

    TFile     *fOutFile;
    
    TH2D      *fNumuDistEnergy;
    TH2D      *fNumubarDistEnergy;
    TH2D      *fNumuNumubarDistEnergy;
    
    TGraph    *fCCxsec_nue;
    TGraph    *fNCxsec_nue;
    TGraph    *fCCQExsec_nue;
    TGraph    *fLowExsec_nue;

  public:
    
    FullDistEnergy(const std::string& flux_file_dir,
	       const std::string& genie_file_name,
	       const std::vector< std::string >& file_vector,
	       const Bool_t& isbottom,
	       const Bool_t& islength,
	       const Bool_t& isnormal);

    virtual ~FullDistEnergy();

    void MakeHists(const std::string& out_file_name,
		   const Double_t& area_factor);
    
    Double_t BottomArea() const;
    Double_t LengthArea() const;
    Double_t NormalArea() const;

  };

}

inline Double_t numi::FullDistEnergy::BottomArea() const { return fBottomArea; }
inline Double_t numi::FullDistEnergy::LengthArea() const { return fLengthArea; }
inline Double_t numi::FullDistEnergy::NormalArea() const { return fNormalArea; }

#endif
