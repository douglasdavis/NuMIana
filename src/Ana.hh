///////////////////////////////////////////////////////////////////////////////
///  \brief   Definition of the base Ana class (to analyze LArNuMI events/flux)
///  \author  douglasdavis@utexas.edu
///////////////////////////////////////////////////////////////////////////////

#ifndef ANA_HH
#define ANA_HH

#include "TH1D.h"
#include "TPaveText.h"
#include "TTree.h"
#include <iostream>
#include <vector>
#include <map>

namespace numi {

  class Ana {
  
  protected:

    std::string  fFileName;    
    TFile       *fFile;
    TTree       *fSimulationNtuple;
    TTree       *fFluxNtuple;
    TTree       *fEntryTree;
    TTree       *fNuMI_Tree;

    std::vector<Double_t>                    fvx;
    std::vector<Double_t>                    fvy;
    std::vector<Double_t>                    fvz;
    std::vector<Int_t>                       fppmedium;
    std::vector<Int_t>                       fndecay;
    std::vector< std::pair< Int_t, Int_t > > fppmediumndecay;
    std::map< Int_t, std::string >           fppmediumCodeMap;
    std::map< Int_t, std::string >           fndecayCodeMap;

  public:
  
    Ana();
    virtual ~Ana();

    TPaveText *PlotTitle;
    void SetupTitle(const std::string& title_);  

    void FillHist_FluxNtuple(TH1D *hist, const std::string& var_name);
    void FillVec_FluxNtuple(std::vector<Double_t>& vec, const std::string& var_name);
    void FillHist_SimulationNtuple(TH1D *hist, const std::string& var_name);
    void FillVec_SimulationNtuple(std::vector<Double_t>& vec, const std::string& var_name);
    void FillHist_EntryTree(TH1D *hist, const std::string& var_name);
    void FillVec_EntryTree(std::vector<Double_t>& vec, const std::string& var_name);
    void FillHist_NuMI_Tree(TH1D *hist, const std::string& var_name);
    void FillVec_NuMI_Tree(std::vector<Double_t>& vec, const std::string& var_name);
    
    inline const std::vector<Double_t>&                    vx()              const;
    inline const std::vector<Double_t>&                    vy()              const;
    inline const std::vector<Double_t>&                    vz()              const;
    inline const std::vector<Int_t>&                       ppmedium()        const;
    inline const std::vector<Int_t>&                       ndecay()          const;
    inline const std::vector< std::pair< Int_t, Int_t > >& ppmediumndecay()  const;
    inline const std::map< Int_t, std::string >&           ppmediumCodeMap() const;
    inline const std::map< Int_t, std::string >&           ndecayCodeMap()   const;

  };

}

inline const std::vector<Double_t>&                     numi::Ana::vx()              const { return fvx;              }
inline const std::vector<Double_t>&                     numi::Ana::vy()              const { return fvy;              }
inline const std::vector<Double_t>&                     numi::Ana::vz()              const { return fvz;              }
inline const std::vector<Int_t>&                        numi::Ana::ppmedium()        const { return fppmedium;        }
inline const std::vector<Int_t>&                        numi::Ana::ndecay()          const { return fndecay;          }
inline const std::vector< std::pair< Int_t, Int_t > >&  numi::Ana::ppmediumndecay()  const { return fppmediumndecay;  }
inline const std::map< Int_t, std::string >&            numi::Ana::ppmediumCodeMap() const { return fppmediumCodeMap; }
inline const std::map< Int_t, std::string >&            numi::Ana::ndecayCodeMap()   const { return fndecayCodeMap;   }

#endif
