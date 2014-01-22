#ifndef LARANA_HH
#define LARANA_HH

#include <vector>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

namespace lar {
  
  class LArAna {
    
  private:

    std::string fFileName;
    TFile *fFile;
    TTree *fTree;
    
    std::vector<double> fNuIntVtxX;
    std::vector<double> fNuIntVtxY;
    std::vector<double> fNuIntVtxZ;
    std::vector<double> fNuEnergy;
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
    
    void FillTH1D(TH1D& histogram, const std::vector<double>& values);
    void FillTH1D(TH1D& histogram, const std::vector< std::vector<double> >& values);
    void FillTH1D(TH1D& histogram, const std::vector<double>& values, const double& cut);
    void FillTH1D(TH1D& histogram, const std::vector< std::vector<double> >& values, const double& cut);

    inline const std::vector<double> NuIntVtxX()     const { return fNuIntVtxX;    }
    inline const std::vector<double> NuIntVtxY()     const { return fNuIntVtxY;    }
    inline const std::vector<double> NuIntVtxZ()     const { return fNuIntVtxZ;    }
    inline const std::vector<double> NuEnergy()      const { return fNuEnergy;     }
    inline const std::vector<double> HadronDecayX()  const { return fHadronDecayX; }
    inline const std::vector<double> HadronDecayY()  const { return fHadronDecayY; }
    inline const std::vector<double> HadronDecayZ()  const { return fHadronDecayZ; }
    inline const std::vector<bool>   CCint()         const { return fCCint;        }
    inline const std::vector<bool>   CCQEint()       const { return fCCQEint;      }
    inline const std::vector<bool>   NCint()         const { return fNCint;        }
    inline const std::vector<bool>   NCQEint()       const { return fNCQEint;      }

    inline const std::vector< std::vector<int> > TrackID() const { return fTrackID; }
    inline const std::vector< std::vector<int> > PdgCode() const { return fPdgCode; }

    inline const std::vector< std::vector<double> > StartX()  const { return fStartVx;  }
    inline const std::vector< std::vector<double> > StartY()  const { return fStartVy;  }
    inline const std::vector< std::vector<double> > StartZ()  const { return fStartVz;  }
    inline const std::vector< std::vector<double> > StartPX() const { return fStartPx; }
    inline const std::vector< std::vector<double> > StartPY() const { return fStartPy; }
    inline const std::vector< std::vector<double> > StartPZ() const { return fStartPz; }
    inline const std::vector< std::vector<double> > StartE()  const { return fStartE;  }

  };
  
}

#endif
  
