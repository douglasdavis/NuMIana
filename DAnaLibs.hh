#ifndef DANALIBS_HH
#define DANALIBS_HH

#include "TH1D.h"
<<<<<<< HEAD
#include "TPaveText.h"
=======
#include <iostream>
>>>>>>> 0df766ecb7e85ef0e9ec79e6d1469f10a1b9857c
#include <vector>

class Ana {
  
protected:
  
public:

  TPaveText *fPlotTitle;
  
};

void FillTH1D(TH1D& histogram, const std::vector<double>& values);
void FillTH1D(TH1D& histogram, const std::vector<double>& values, const double& cut);

void max_min(const std::string& var, const std::vector<double>& vec);
void max_min(const std::string& var, const std::vector<int>& vec);

#endif
