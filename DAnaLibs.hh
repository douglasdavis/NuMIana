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

  void SetupTitle(const std::string& title_)
  {
    fPlotTitle = new TPaveText(0.6485149,0.9311224,0.8778878,0.9821429,"brNDC");
    fPlotTitle->SetTextSize(0.048);
    fPlotTitle->SetTextFont(102);
    fPlotTitle->SetFillColor(0);
    fPlotTitle->SetBorderSize(0);
    fPlotTitle->AddText(title_.c_str());
  }
  
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
