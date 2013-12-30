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

  inline std::vector<double> wgt()      const { return fwgt;      }
  inline std::vector<double> vtxx()     const { return fvtxx;     }
  inline std::vector<double> vtxy()     const { return fvtxy;     }
  inline std::vector<double> vtxz()     const { return fvtxz;     }
  inline std::vector<double> dist()     const { return fdist;     }
  inline std::vector<double> px()       const { return fpx;       }
  inline std::vector<double> py()       const { return fpy;       }
  inline std::vector<double> pz()       const { return fpz;       }
  inline std::vector<double> E()        const { return fE;        }  
  inline std::vector<double> tpx()      const { return ftpx;      }
  inline std::vector<double> tpy()      const { return ftpy;      }
  inline std::vector<double> tpz()      const { return ftpz;      }
  inline std::vector<double> vx()       const { return fvx;       }
  inline std::vector<double> vy()       const { return fvy;       }
  inline std::vector<double> vz()       const { return fvz;       }
  inline std::vector<int>    ndecay()   const { return fndecay;   }
  inline std::vector<int>    ppmedium() const { return fppmedium; }
  inline std::vector<int>    tptype()   const { return ftptype;   }
  inline std::vector<int>    run()      const { return frun;      }
  inline std::vector<int>    evtno()    const { return fevtno;    }
  inline std::vector<int>    entryno()  const { return fentryno;  }

};
