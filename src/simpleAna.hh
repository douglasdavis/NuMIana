///////////////////////////////////////////////////////////////////////////////
///  \brief   Definition of simpleAna class (to analyze simple flux ntuples)
///  \author  douglasdavis@utexas.edu
///////////////////////////////////////////////////////////////////////////////

#ifndef SIMPLEANA_HH
#define SIMPLEANA_HH

#include "TROOT.h"
#include <iostream>
#include <vector>
#include "Ana.hh"
#include "TFile.h"
#include "TTree.h"
#include "TPaveText.h"

namespace numi {

  class simpleAna : public Ana {
    
  private:
    
    TFile *fFile;
    
    std::vector<Double_t> fwgt;      ///< nu weight
    std::vector<Double_t> fvtxx;     ///< x position in lab frame
    std::vector<Double_t> fvtxy;     ///< y position in lab frame
    std::vector<Double_t> fvtxz;     ///< z position in lab frame
    std::vector<Double_t> fdist;     ///< distance from hadron decay
    std::vector<Double_t> fpx;       ///< lab momentum x
    std::vector<Double_t> fpy;       ///< lab momentum y
    std::vector<Double_t> fpz;       ///< lab momentum z
    std::vector<Double_t> fE;        ///< lab energy
    std::vector<Int_t>    fpdg;      ///< pdg code for neutrino

    std::vector<Double_t> ftpx;      ///< parent momentum at target exit x
    std::vector<Double_t> ftpy;      ///< parent momentum at target exit y
    std::vector<Double_t> ftpz;      ///< parent momentum at target exit z
    std::vector<Int_t>    ftptype;   ///< parent particle type at target exit
    std::vector<Int_t>    frun;      ///<
    std::vector<Int_t>    fevtno;    ///<
    std::vector<Int_t>    fentryno;  ///<

    std::vector< std::pair< Int_t, Double_t > > fPdgEnergy;

  public:
    
    simpleAna();
    simpleAna(const std::string& file_name, const bool& is_normal);
    virtual ~simpleAna();

    virtual void PrintNeutrinos();
    virtual void PrintDecayLocations();

    inline const std::vector<Double_t>& wgt()      const { return fwgt;      }
    inline const std::vector<Double_t>& vtxx()     const { return fvtxx;     }
    inline const std::vector<Double_t>& vtxy()     const { return fvtxy;     }
    inline const std::vector<Double_t>& vtxz()     const { return fvtxz;     }
    inline const std::vector<Double_t>& dist()     const { return fdist;     }
    inline const std::vector<Double_t>& px()       const { return fpx;       }
    inline const std::vector<Double_t>& py()       const { return fpy;       }
    inline const std::vector<Double_t>& pz()       const { return fpz;       }
    inline const std::vector<Double_t>& E()        const { return fE;        }  
    inline const std::vector<Int_t>&    pdg()      const { return fpdg;      }
    inline const std::vector<Double_t>& tpx()      const { return ftpx;      }
    inline const std::vector<Double_t>& tpy()      const { return ftpy;      }
    inline const std::vector<Double_t>& tpz()      const { return ftpz;      }
    inline const std::vector<Int_t>&    tptype()   const { return ftptype;   }
    inline const std::vector<Int_t>&    run()      const { return frun;      }
    inline const std::vector<Int_t>&    evtno()    const { return fevtno;    }
    inline const std::vector<Int_t>&    entryno()  const { return fentryno;  }

    inline const std::vector< std::pair< Int_t, Double_t > >& PdgEnergy() const { return fPdgEnergy; }

    TTree *EntryTree() const { return fEntryTree; }
    TTree *NuMI_Tree() const { return fNuMI_Tree; }
    
  };
}

#endif
