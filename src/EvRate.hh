///////////////////////////////////////////////////////////////////////////////
///  \brief   Definition of EvRate class (doing flux/event rate histograms)
///  \author  douglasdavis@utexas.edu
///////////////////////////////////////////////////////////////////////////////

#ifndef EVRATE_HH
#define EVRATE_HH

#include <iostream>
#include <map>
#include <vector>
#include "TFile.h"
#include "TChain.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TDirectory.h"

namespace numi {
  
  class EvRate {
    
  private:
    
    TChain     *fNuMIChain;
    TFile      *fGenieFile;
    TDirectory *fDir;

    TGraph     *fCCxsec_numu;
    TGraph     *fNCxsec_numu;
    TGraph     *fCCQExsec_numu;
    TGraph     *fCCxsec_numubar;
    TGraph     *fNCxsec_numubar;
    TGraph     *fCCQExsec_numubar;
    TGraph     *fCCxsec_nue;
    TGraph     *fNCxsec_nue;
    TGraph     *fCCQExsec_nue;
    TGraph     *fCCxsec_nuebar;
    TGraph     *fNCxsec_nuebar;
    TGraph     *fCCQExsec_nuebar;
    
    UInt_t      fNFluxFiles;
    Double_t    fLowerVzLimit;
    Double_t    fUpperVzLimit;
    Double_t    fEnergyCut;

    Bool_t      fIsBottom;
    Bool_t      fIsLength;
    Bool_t      fIsNormal;

    Double_t    fwgt;
    Double_t    fvtxx;
    Double_t    fvtxy;
    Double_t    fvtxz;
    Double_t    fdist;
    Double_t    fpx;
    Double_t    fpy;
    Double_t    fpz;
    Double_t    fE;
    Int_t       fpdg;

    Double_t    ftpx;
    Double_t    ftpy;
    Double_t    ftpz;
    Double_t    fvx;
    Double_t    fvy;
    Double_t    fvz;
    Int_t       fppmedium;
    Int_t       fndecay;
    Int_t       ftptype;
    Int_t       frun;
    Int_t       fevtno;
    Int_t       fentryno;

    Double_t    fBottomArea = 51.926;
    Double_t    fLengthArea = 51.600;
    Double_t    fNormalArea = 11.920;

  public:
    
    EvRate(const std::string& flux_file_dir,
	   const std::string& genie_file_name,
	   const std::vector< std::string >& file_vector,
	   const Bool_t& isbottom,
	   const Bool_t& islength,
	   const Bool_t& isnormal);
    
    virtual ~EvRate();

    void SetLowerVzLimit(const Double_t& lim);
    void SetUpperVzLimit(const Double_t& lim);
    void SetEnergyCut(const Double_t& cut);

    void MakeHists(const std::string& out_file_name, const Double_t& area_factor);

    Double_t BottomArea() const;
    Double_t LengthArea() const;
    Double_t NormalArea() const;
  
  };

}

inline Double_t numi::EvRate::BottomArea() const { return fBottomArea; }
inline Double_t numi::EvRate::LengthArea() const { return fLengthArea; }
inline Double_t numi::EvRate::NormalArea() const { return fNormalArea; }

#endif
