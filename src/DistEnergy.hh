#ifndef DISTENERGY_HH
#define DISTENERGY_HH

#include <iostream>
#include <vector>
#include "TTree.h"
#include "TFile.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TChain.h"

namespace numi {

  class DistEnergy {

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
    Double_t   fpx;
    Double_t   fpy;
    Double_t   fpz;
    Double_t   fE;
    Double_t   fdist;
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

    Double_t   fEnergyCut;
    Int_t      fNbinsX;
    Int_t      fNbinsY;
    Double_t   fXmin;
    Double_t   fXmax;
    Double_t   fYmin;
    Double_t   fYmax;

    TFile     *fOutFile;
    
    TH2D      *fNumuDistEnergy;
    TH2D      *fNumubarDistEnergy;
    TH2D      *fNumuNumubarDistEnergy;

    TH2D      *fNueDistEnergy;
    TH2D      *fNuebarDistEnergy;
    TH2D      *fNueNuebarDistEnergy;
    
    TH1D      *fNumuEnergy;
    TH1D      *fNueEnergy;
    TH1D      *fNumubarEnergy;
    TH1D      *fNuebarEnergy;

    TGraph    *fCCxsec_nue;
    TGraph    *fNCxsec_nue;
    TGraph    *fCCQExsec_nue;
    TGraph    *fLowExsec_nue;

  public:
    
    DistEnergy(const std::string& flux_file_dir,
	       const std::string& genie_file_name,
	       const std::vector< std::string >& file_vector,
	       const Bool_t& isbottom,
	       const Bool_t& islength,
	       const Bool_t& isnormal);

    virtual ~DistEnergy();

    void SetEnergyCut(const Double_t& ecut);

    void SetBinning(const Int_t& nx,
		    const Double_t& xmin,
		    const Double_t& xmax,
		    const Int_t& ny,
		    const Double_t& ymin,
		    const Double_t& ymax);

    void MakeHists(const std::string& out_file_name,
		   const Double_t& area_factor,
		   const Double_t& dm2,
		   const Double_t& s22t,
		   const Double_t& adm2,
		   const Double_t& as22t);
    
    Double_t OscProb(const Double_t& LoverE,
		     const Double_t& dm2,
		     const Double_t& s22t);
    
    void OscillateHist(const TH2D& mu,
		       TH2D& e,
		       const Double_t& dm2,
		       const Double_t& s22t);


    void Make1DFlux(const TH2D& hist2d,
		    TH1D& hist1d);

    Double_t BottomArea() const;
    Double_t LengthArea() const;
    Double_t NormalArea() const;

  };

}

inline Double_t numi::DistEnergy::BottomArea() const { return fBottomArea; }
inline Double_t numi::DistEnergy::LengthArea() const { return fLengthArea; }
inline Double_t numi::DistEnergy::NormalArea() const { return fNormalArea; }

#endif
