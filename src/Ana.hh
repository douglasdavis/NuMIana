///////////////////////////////////////////////////////////////////////////////
///  \brief   Definition of the base Ana class (to analyze LArNuMI events/flux)
///  \author  douglasdavis@utexas.edu
///////////////////////////////////////////////////////////////////////////////

#ifndef ANA_HH
#define ANA_HH

#include "TH1D.h"
#include "TPaveText.h"
#include <iostream>
#include <vector>
#include <map>

namespace numi {

  class Ana {
  
  protected:

    std::vector<double> fvx;
    std::vector<double> fvy;
    std::vector<double> fvz;
    std::vector<int>    fppmedium;
    std::vector<int>    fndecay;
    std::vector< std::pair< int, int > > fppmediumndecay;
    std::map< int, std::string > fppmediumCodeMap;
    std::map< int, std::string > fndecayCodeMap;

  public:
  
    Ana();
    virtual ~Ana();

    TPaveText *PlotTitle;
    void SetupTitle(const std::string& title_);  

    inline const std::vector<double>                  vx()              const;
    inline const std::vector<double>                  vy()              const;
    inline const std::vector<double>                  vz()              const;
    inline const std::vector<int>                     ppmedium()        const;
    inline const std::vector<int>                     ndecay()          const;
    inline const std::vector< std::pair< int, int > > ppmediumndecay()  const;
    inline const std::map< int, std::string >         ppmediumCodeMap() const;
    inline const std::map< int, std::string >         ndecayCodeMap()   const;

  };

}

inline const std::vector<double>                  numi::Ana::vx()              const { return fvx;              }
inline const std::vector<double>                  numi::Ana::vy()              const { return fvy;              }
inline const std::vector<double>                  numi::Ana::vz()              const { return fvz;              }
inline const std::vector<int>                     numi::Ana::ppmedium()        const { return fppmedium;        }
inline const std::vector<int>                     numi::Ana::ndecay()          const { return fndecay;          }
inline const std::vector< std::pair< int, int > > numi::Ana::ppmediumndecay()  const { return fppmediumndecay;  }
inline const std::map< int, std::string >         numi::Ana::ppmediumCodeMap() const { return fppmediumCodeMap; }
inline const std::map< int, std::string >         numi::Ana::ndecayCodeMap()   const { return fndecayCodeMap;   }

#endif
