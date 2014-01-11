#ifndef NUMIANA_HH
#define NUMIANA_HH

#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTree.h"

class NuMIana {
    
private:
    
  TFile *fFile;
    
  TTree *fEntryTree;
  std::vector<double> fwgt;      ///< nu weight
  std::vector<double> fvtxx;     ///< x position in lab frame
  std::vector<double> fvtxy;     ///< y position in lab frame
  std::vector<double> fvtxz;     ///< z position in lab frame
  std::vector<double> fdist;     ///< distance from hadron decay
  std::vector<double> fpx;       ///< lab momentum x
  std::vector<double> fpy;       ///< lab momentum y
  std::vector<double> fpz;       ///< lab momentum z
  std::vector<double> fE;        ///< lab energy
  std::vector<int>    fpdg;      ///< pdg code for neutrino

  TTree *fNuMI_Tree;
  std::vector<double> ftpx;      ///< parent momentum at target exit x
  std::vector<double> ftpy;      ///< parent momentum at target exit y
  std::vector<double> ftpz;      ///< parent momentum at target exit z
  std::vector<double> fvx;       ///< vertex position of hadron/muon decay x
  std::vector<double> fvy;       ///< vertex position of hadron/muon decay y
  std::vector<double> fvz;       ///< vertex position of hadron/muon decay z
  std::vector<int>    fndecay;   ///< decay mode;
  std::vector<int>    fppmedium; ///< tracking medium where parent was produced
  std::vector<int>    ftptype;   ///< parent particle type at target exit
  std::vector<int>    frun;      ///<
  std::vector<int>    fevtno;    ///<
  std::vector<int>    fentryno;  ///<

public:
    
  NuMIana();
  NuMIana(std::string file_name);
  virtual ~NuMIana();

  void PrintDecays();
  void PrintNeutrinos();
  void PrintDecayLocations();

  const std::vector<double>& wgt()      const { return fwgt;      }
  const std::vector<double>& vtxx()     const { return fvtxx;     }
  const std::vector<double>& vtxy()     const { return fvtxy;     }
  const std::vector<double>& vtxz()     const { return fvtxz;     }
  const std::vector<double>& dist()     const { return fdist;     }
  const std::vector<double>& px()       const { return fpx;       }
  const std::vector<double>& py()       const { return fpy;       }
  const std::vector<double>& pz()       const { return fpz;       }
  const std::vector<double>& E()        const { return fE;        }  
  const std::vector<int>&    pdg()      const { return fpdg;      }
  const std::vector<double>& tpx()      const { return ftpx;      }
  const std::vector<double>& tpy()      const { return ftpy;      }
  const std::vector<double>& tpz()      const { return ftpz;      }
  const std::vector<double>& vx()       const { return fvx;       }
  const std::vector<double>& vy()       const { return fvy;       }
  const std::vector<double>& vz()       const { return fvz;       }
  const std::vector<int>&    ndecay()   const { return fndecay;   }
  const std::vector<int>&    ppmedium() const { return fppmedium; }
  const std::vector<int>&    tptype()   const { return ftptype;   }
  const std::vector<int>&    run()      const { return frun;      }
  const std::vector<int>&    evtno()    const { return fevtno;    }
  const std::vector<int>&    entryno()  const { return fentryno;  }

};

#endif
