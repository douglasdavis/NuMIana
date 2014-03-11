///////////////////////////////////////////////////////////////////////////////
///  \brief   Definition of the base Ana class (to analyze LArNuMI events/flux)
///  \author  douglasdavis@utexas.edu
///////////////////////////////////////////////////////////////////////////////

#ifndef ANA_HH
#define ANA_HH

#include "TROOT.h"
#include "TH1D.h"
#include "TPaveText.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include <vector>
#include <map>

namespace numi {

  class Ana {
  
  protected:

    std::string   fFileName;    
    TFile        *fFile;
    TTree        *fSimulationNtuple;
    TTree        *fFluxNtuple;
    TChain       *fNuMIChain;

    Int_t                                      fNEvents;
    std::vector< Double_t >                    fvx;
    std::vector< Double_t >                    fvy;
    std::vector< Double_t >                    fvz;
    std::vector< Int_t >                       fppmedium;
    std::vector< Int_t >                       fndecay;
    std::vector< std::pair< Int_t, Int_t > >   fppmediumndecay;
    std::map< Int_t, std::string >             fppmediumCodeMap;
    std::map< Int_t, std::string >             fndecayCodeMap;

  public:
  
    Ana();
    virtual ~Ana();

    TPaveText *PlotTitle;
    void SetupTitle(const std::string& title_);  

    inline const Int_t NEvents() const;

    inline const std::vector< Double_t >&                    vx()              const;
    inline const std::vector< Double_t >&                    vy()              const;
    inline const std::vector< Double_t >&                    vz()              const;
    inline const std::vector< Int_t >&                       ppmedium()        const;
    inline const std::vector< Int_t >&                       ndecay()          const;
    inline const std::vector< std::pair< Int_t, Int_t > >&   ppmediumndecay()  const;
    inline const std::map< Int_t, std::string >&             ppmediumCodeMap() const;
    inline const std::map< Int_t, std::string >&             ndecayCodeMap()   const;

  };

}

inline const Int_t numi::Ana::NEvents() const { return fNEvents; }

inline const std::vector< Double_t >&                     numi::Ana::vx()              const { return fvx;              }
inline const std::vector< Double_t >&                     numi::Ana::vy()              const { return fvy;              }
inline const std::vector< Double_t >&                     numi::Ana::vz()              const { return fvz;              }
inline const std::vector< Int_t >&                        numi::Ana::ppmedium()        const { return fppmedium;        }
inline const std::vector< Int_t >&                        numi::Ana::ndecay()          const { return fndecay;          }
inline const std::vector< std::pair< Int_t, Int_t > >&    numi::Ana::ppmediumndecay()  const { return fppmediumndecay;  }
inline const std::map< Int_t, std::string >&              numi::Ana::ppmediumCodeMap() const { return fppmediumCodeMap; }
inline const std::map< Int_t, std::string >&              numi::Ana::ndecayCodeMap()   const { return fndecayCodeMap;   }

#endif
