#ifndef DANALIBS_HH
#define DANALIBS_HH

#include "TH1D.h"
#include "TPaveText.h"
#include <iostream>
#include <vector>

class Ana {
  
protected:
  
public:

  TPaveText *fPlotTitle;
  
};

void FillTH1D(TH1D& histogram,
	      const std::vector<double>& values);

void FillTH1D(TH1D& histogram,
	      const std::vector<double>& values, 
	      const double& cut);

void max_min(const std::string& var,
	     const std::vector<double>& vec,
	     double& max,
	     double& min);

void max_min(const std::string& var,
	     const std::vector<int>& vec,
	     int& max,
	     int& min);

#endif
