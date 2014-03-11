///////////////////////////////////////////////////////////////////////////////
///  \brief   Definition of EvRate class (doing flux/event rate histograms)
///  \author  douglasdavis@utexas.edu
///////////////////////////////////////////////////////////////////////////////

#ifndef SIMPLEANA2_HH
#define SIMPLEANA2_HH

#include <iostream>
#include <map>
#include <vector>
#include "TFile.h"
#include "TTree.h"

namespace numi {

  class simpleAna2 {
    
  private:
    
    TFile      *fFile;
    TTree      *fNuMITree;
    UInt_t      fNEvents;

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

    simpleAna2(const std::string& file_name);

    virtual ~simpleAna2();

    std::vector< Double_t > VectorOfV(const std::string& var);

  };

}

#endif
