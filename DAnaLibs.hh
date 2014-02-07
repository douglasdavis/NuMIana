#ifndef DANALIBS_HH
#define DANALIBS_HH

#include "TH1D.h"
#include "TPaveText.h"
#include <iostream>
#include <vector>

class Ana {
  
protected:
  
  std::vector< std::pair< int, int > > fppmediumNdecay;
  
public:
  
  TPaveText *PlotTitle;
  void SetupTitle(const std::string& title_);  
  
  inline const std::vector< std::pair< int, int > > ppmediumNdecay() const { return fppmediumNdecay; }
  
};

void FillTH1D(TH1D& histogram, const std::vector<double>& values);
void FillTH1D(TH1D& histogram, const std::vector<double>& values, const double& cut);

void max_min(const std::string& var, const std::vector<double>& vec, double& max, double& min);
void max_min(const std::string& var, const std::vector<int>& vec, int& max, int& min);

void FixTitle(TPaveText& pave, const std::string& title);

void PrintDecays(const std::vector<int>& ndecay_vec);

const std::string ndecayToString(const int& n);
const std::string ppmediumToString(const int& n);

void PrintPPmediumNdecay(const std::vector< std::pair<int,int> >& ana_data);

#endif
