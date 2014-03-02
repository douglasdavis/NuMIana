///////////////////////////////////////////////////////////////////////////////
///  \brief   Definition of LArAna class (to analyze ntuples from LArNuMIana)
///  \author  douglasdavis@utexas.edu
///////////////////////////////////////////////////////////////////////////////

#ifndef LARANA_HH
#define LARANA_HH

#include <vector>
#include <iostream>
#include "TROOT.h"
#include "Ana.hh"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TPaveText.h"

namespace numi {

  class LArAna : public Ana {
  
  private:

    std::vector<Int_t>  fNuPdg;
    std::vector<Double_t> fNuPx;
    std::vector<Double_t> fNuPy;
    std::vector<Double_t> fNuPz;
    std::vector<Double_t> fNuIntVtxX;
    std::vector<Double_t> fNuIntVtxY;
    std::vector<Double_t> fNuIntVtxZ;
    std::vector<Double_t> fNuEnergy;    
    std::vector<Int_t>    fLeptonPdg;
    std::vector<Double_t> fLeptonVx;
    std::vector<Double_t> fLeptonVy;
    std::vector<Double_t> fLeptonVz;
    std::vector<Double_t> fLeptonPx;
    std::vector<Double_t> fLeptonPy;
    std::vector<Double_t> fLeptonPz;
    std::vector<Double_t> fLeptonEnergy;
    std::vector<Double_t> fLeptonThetaXZ2;
    std::vector<Double_t> fLeptonThetaYZ2;
    std::vector<Double_t> fLeptonThetaXZ;
    std::vector<Double_t> fLeptonThetaYZ;
    std::vector<bool>   fCCint;
    std::vector<bool>   fCCQEint;
    std::vector<bool>   fNCint;
    std::vector<bool>   fNCQEint;
    std::vector<Int_t>    fEvent;
    std::vector<Int_t>    fSubRun;
    std::vector<Int_t>    fRun;

    std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > > fpPdgCodeStartPx;
    std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > > fpPdgCodeStartPy;
    std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > > fpPdgCodeStartPz;
    std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > > fpPdgCodeStartVx;
    std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > > fpPdgCodeStartVy;
    std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > > fpPdgCodeStartVz;
    std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > > fpPdgCodeStartE;

    std::vector< std::vector<Int_t> >    fTrackID;
    std::vector< std::vector<Int_t> >    fPdgCode;
    std::vector< std::vector<Double_t> > fStartVx;
    std::vector< std::vector<Double_t> > fStartVy;
    std::vector< std::vector<Double_t> > fStartVz;
    std::vector< std::vector<Double_t> > fStartPx;
    std::vector< std::vector<Double_t> > fStartPy;
    std::vector< std::vector<Double_t> > fStartPz;
    std::vector< std::vector<Double_t> > fStartE;
    
  public:
    
    LArAna();    
    LArAna(const std::string& file_name);
    
    virtual ~LArAna();
    
    inline const std::vector<Int_t>&    NuPdg()          const { return fNuPdg;           }
    inline const std::vector<Double_t>& NuPx()           const { return fNuPx;            }
    inline const std::vector<Double_t>& NuPy()           const { return fNuPy;            }
    inline const std::vector<Double_t>& NuPz()           const { return fNuPz;            }
    inline const std::vector<Double_t>& NuIntVtxX()      const { return fNuIntVtxX;       }
    inline const std::vector<Double_t>& NuIntVtxY()      const { return fNuIntVtxY;       }
    inline const std::vector<Double_t>& NuIntVtxZ()      const { return fNuIntVtxZ;       }
    inline const std::vector<Double_t>& NuEnergy()       const { return fNuEnergy;        }
    inline const std::vector<Int_t>&    LeptonPdg()      const { return fLeptonPdg;       }
    inline const std::vector<Double_t>& LeptonVx()       const { return fLeptonVx;        }
    inline const std::vector<Double_t>& LeptonVy()       const { return fLeptonVy;        }
    inline const std::vector<Double_t>& LeptonVz()       const { return fLeptonVz;        }
    inline const std::vector<Double_t>& LeptonPx()       const { return fLeptonPx;        }
    inline const std::vector<Double_t>& LeptonPy()       const { return fLeptonPy;        }
    inline const std::vector<Double_t>& LeptonPz()       const { return fLeptonPz;        }
    inline const std::vector<Double_t>& LeptonThetaXZ2() const { return fLeptonThetaXZ2;  }
    inline const std::vector<Double_t>& LeptonThetaYZ2() const { return fLeptonThetaYZ2;  }
    inline const std::vector<Double_t>& LeptonThetaXZ()  const { return fLeptonThetaXZ;   }
    inline const std::vector<Double_t>& LeptonThetaYZ()  const { return fLeptonThetaYZ;   }
    inline const std::vector<bool>&   CCint()          const { return fCCint;           }
    inline const std::vector<bool>&   CCQEint()        const { return fCCQEint;         }
    inline const std::vector<bool>&   NCint()          const { return fNCint;           }
    inline const std::vector<bool>&   NCQEint()        const { return fNCQEint;         }
    
    inline const std::vector< std::vector<Int_t> >&    TrackID() const { return fTrackID; }
    inline const std::vector< std::vector<Int_t> >&    PdgCode() const { return fPdgCode; }
    inline const std::vector< std::vector<Double_t> >& StartX()  const { return fStartVx; }
    inline const std::vector< std::vector<Double_t> >& StartY()  const { return fStartVy; }
    inline const std::vector< std::vector<Double_t> >& StartZ()  const { return fStartVz; }
    inline const std::vector< std::vector<Double_t> >& StartPX() const { return fStartPx; }
    inline const std::vector< std::vector<Double_t> >& StartPY() const { return fStartPy; }
    inline const std::vector< std::vector<Double_t> >& StartPZ() const { return fStartPz; }
    inline const std::vector< std::vector<Double_t> >& StartE()  const { return fStartE;  }
  
    inline const std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > >& PdgCodeStartPx() const { return fpPdgCodeStartPx; }
    inline const std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > >& PdgCodeStartPy() const { return fpPdgCodeStartPy; }
    inline const std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > >& PdgCodeStartPz() const { return fpPdgCodeStartPz; }
    inline const std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > >& PdgCodeStartVx() const { return fpPdgCodeStartVx; }
    inline const std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > >& PdgCodeStartVy() const { return fpPdgCodeStartVy; }
    inline const std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > >& PdgCodeStartVz() const { return fpPdgCodeStartVz; }
    inline const std::vector< std::pair< std::vector<Int_t>, std::vector<Double_t> > >& PdgCodeStartE()  const { return fpPdgCodeStartE;  }

    TTree *SimulationNtuple() const { return fSimulationNtuple; }
    TTree *FluxNtuple()       const { return fFluxNtuple;       }
    
  };
}
  
#endif
