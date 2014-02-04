#ifndef LARANA_HH
#define LARANA_HH

#include <vector>
#include <iostream>
#include "DAnaLibs.hh"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TPaveText.h"

class LArAna : public Ana {
  
private:

  std::string fFileName;
  TFile *fFile;
  TTree *fTree;
    
  std::vector<int>    fNuPdg;
  std::vector<double> fNuPx;
  std::vector<double> fNuPy;
  std::vector<double> fNuPz;
  std::vector<double> fNuIntVtxX;
  std::vector<double> fNuIntVtxY;
  std::vector<double> fNuIntVtxZ;
  std::vector<double> fNuEnergy;    
  std::vector<int>    fLeptonPdg;
  std::vector<double> fLeptonVx;
  std::vector<double> fLeptonVy;
  std::vector<double> fLeptonVz;
  std::vector<double> fLeptonPx;
  std::vector<double> fLeptonPy;
  std::vector<double> fLeptonPz;
  std::vector<double> fLeptonEnergy;
  std::vector<double> fLeptonThetaXZ2;
  std::vector<double> fLeptonThetaYZ2;
  std::vector<double> fLeptonThetaXZ;
  std::vector<double> fLeptonThetaYZ;
  std::vector<double> fHadronDecayX;
  std::vector<double> fHadronDecayY;
  std::vector<double> fHadronDecayZ;
  std::vector<bool>   fCCint;
  std::vector<bool>   fCCQEint;
  std::vector<bool>   fNCint;
  std::vector<bool>   fNCQEint;
  std::vector<int>    fEvent;
  std::vector<int>    fSubRun;
  std::vector<int>    fRun;

  std::vector< std::pair< std::vector<int>, std::vector<double> > > fpPdgCodeStartPx;
  std::vector< std::pair< std::vector<int>, std::vector<double> > > fpPdgCodeStartPy;
  std::vector< std::pair< std::vector<int>, std::vector<double> > > fpPdgCodeStartPz;
  std::vector< std::pair< std::vector<int>, std::vector<double> > > fpPdgCodeStartVx;
  std::vector< std::pair< std::vector<int>, std::vector<double> > > fpPdgCodeStartVy;
  std::vector< std::pair< std::vector<int>, std::vector<double> > > fpPdgCodeStartVz;
  std::vector< std::pair< std::vector<int>, std::vector<double> > > fpPdgCodeStartE;

  std::vector< std::vector<int> >    fTrackID;
  std::vector< std::vector<int> >    fPdgCode;
  std::vector< std::vector<double> > fStartVx;
  std::vector< std::vector<double> > fStartVy;
  std::vector< std::vector<double> > fStartVz;
  std::vector< std::vector<double> > fStartPx;
  std::vector< std::vector<double> > fStartPy;
  std::vector< std::vector<double> > fStartPz;
  std::vector< std::vector<double> > fStartE;
    
public:
    
  LArAna();    
  LArAna(const std::string& file_name);
    
  virtual ~LArAna();

  inline const std::vector<int>    NuPdg()          const { return fNuPdg;           }
  inline const std::vector<double> NuPx()           const { return fNuPx;            }
  inline const std::vector<double> NuPy()           const { return fNuPy;            }
  inline const std::vector<double> NuPz()           const { return fNuPz;            }
  inline const std::vector<double> NuIntVtxX()      const { return fNuIntVtxX;       }
  inline const std::vector<double> NuIntVtxY()      const { return fNuIntVtxY;       }
  inline const std::vector<double> NuIntVtxZ()      const { return fNuIntVtxZ;       }
  inline const std::vector<double> NuEnergy()       const { return fNuEnergy;        }
  inline const std::vector<int>    LeptonPdg()      const { return fLeptonPdg;       }
  inline const std::vector<double> LeptonVx()       const { return fLeptonVx;        }
  inline const std::vector<double> LeptonVy()       const { return fLeptonVy;        }
  inline const std::vector<double> LeptonVz()       const { return fLeptonVz;        }
  inline const std::vector<double> LeptonPx()       const { return fLeptonPx;        }
  inline const std::vector<double> LeptonPy()       const { return fLeptonPy;        }
  inline const std::vector<double> LeptonPz()       const { return fLeptonPz;        }
  inline const std::vector<double> LeptonThetaXZ2() const { return fLeptonThetaXZ2;  }
  inline const std::vector<double> LeptonThetaYZ2() const { return fLeptonThetaYZ2;  }
  inline const std::vector<double> LeptonThetaXZ()  const { return fLeptonThetaXZ;   }
  inline const std::vector<double> LeptonThetaYZ()  const { return fLeptonThetaYZ;   }
  inline const std::vector<double> HadronDecayX()   const { return fHadronDecayX;    }
  inline const std::vector<double> HadronDecayY()   const { return fHadronDecayY;    }
  inline const std::vector<double> HadronDecayZ()   const { return fHadronDecayZ;    }
  inline const std::vector<bool>   CCint()          const { return fCCint;           }
  inline const std::vector<bool>   CCQEint()        const { return fCCQEint;         }
  inline const std::vector<bool>   NCint()          const { return fNCint;           }
  inline const std::vector<bool>   NCQEint()        const { return fNCQEint;         }

  inline const std::vector< std::vector<int> >    TrackID() const { return fTrackID; }
  inline const std::vector< std::vector<int> >    PdgCode() const { return fPdgCode; }
  inline const std::vector< std::vector<double> > StartX()  const { return fStartVx; }
  inline const std::vector< std::vector<double> > StartY()  const { return fStartVy; }
  inline const std::vector< std::vector<double> > StartZ()  const { return fStartVz; }
  inline const std::vector< std::vector<double> > StartPX() const { return fStartPx; }
  inline const std::vector< std::vector<double> > StartPY() const { return fStartPy; }
  inline const std::vector< std::vector<double> > StartPZ() const { return fStartPz; }
  inline const std::vector< std::vector<double> > StartE()  const { return fStartE;  }
  
  inline const std::vector< std::pair< std::vector<int>, std::vector<double> > > PdgCodeStartPx() const { return fpPdgCodeStartPx; }
  inline const std::vector< std::pair< std::vector<int>, std::vector<double> > > PdgCodeStartPy() const { return fpPdgCodeStartPy; }
  inline const std::vector< std::pair< std::vector<int>, std::vector<double> > > PdgCodeStartPz() const { return fpPdgCodeStartPz; }
  inline const std::vector< std::pair< std::vector<int>, std::vector<double> > > PdgCodeStartVx() const { return fpPdgCodeStartVx; }
  inline const std::vector< std::pair< std::vector<int>, std::vector<double> > > PdgCodeStartVy() const { return fpPdgCodeStartVy; }
  inline const std::vector< std::pair< std::vector<int>, std::vector<double> > > PdgCodeStartVz() const { return fpPdgCodeStartVz; }
  inline const std::vector< std::pair< std::vector<int>, std::vector<double> > > PdgCodeStartE()  const { return fpPdgCodeStartE;  }

};
  
#endif
