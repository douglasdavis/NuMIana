#ifndef ANA_HH
#define ANA_HH

#include "TH1D.h"
#include "TPaveText.h"
#include <iostream>
#include <vector>

class Ana {
  
protected:
  
  std::vector<double> fvx;
  std::vector<double> fvy;
  std::vector<double> fvz;
  std::vector<int>    fppmedium;
  std::vector<int>    fndecay;
  std::vector< std::pair< int, int > > fppmediumndecay;
  
public:
  
  Ana();
  ~Ana();

  TPaveText *PlotTitle;
  void SetupTitle(const std::string& title_);  

  void FillTH1D(TH1D& histogram, const std::vector<double>& values);
  void FillTH1D(TH1D& histogram, const std::vector<double>& values, const double& cut);
  void max_min(const std::string& var, const std::vector<double>& vec, double& max, double& min);
  void max_min(const std::string& var, const std::vector<int>& vec, int& max, int& min);
  void FixTitle(TPaveText& pave, const std::string& title);
  void PrintDecays(const std::vector<int>& ndecay_vec);
  void Print_ppmediumndecay(const std::vector< std::pair<int,int> >& ana_data);

  inline const std::string ndecayToString(const int& n) const;
  inline const std::string ppmediumToString(const int& n) const;
  
  inline const std::vector<double>                  vx()             const { return fvx;             }
  inline const std::vector<double>                  vy()             const { return fvy;             }
  inline const std::vector<double>                  vz()             const { return fvz;             }
  inline const std::vector<int>                     ppmedium()       const { return fppmedium;       }
  inline const std::vector<int>                     ndecay()         const { return fndecay;         }
  inline const std::vector< std::pair< int, int > > ppmediumndecay() const { return fppmediumndecay; }
  
};

#endif
