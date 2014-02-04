#include <iostream>
#include <algorithm>
#include <vector>
#include "DAnaLibs.hh"

void Ana::SetupTitle(const std::string& title_)
{
  PlotTitle = new TPaveText(0.6485149,0.9311224,0.8778878,0.9821429,"brNDC");
  PlotTitle->SetTextSize(0.048);
  PlotTitle->SetTextFont(102);
  PlotTitle->SetFillColor(0);
  PlotTitle->SetBorderSize(0);
  PlotTitle->AddText(title_.c_str());
}


void FillTH1D(TH1D& histogram, const std::vector<double>& values)
{
  for ( auto const &val : values )
    histogram.Fill(val);
}

void FillTH1D(TH1D& histogram, const std::vector<double>& values, const double& cut)
{
  for ( auto const &val : values )
    if ( val >= cut ) 
      histogram.Fill(val);
}

void max_min(const std::string& var, const std::vector<double>& vec, double& max, double& min)
{
  std::cout << var << std::endl;
  std::cout << "Max: " << *(std::max_element(vec.begin(),vec.end())) << std::endl;
  std::cout << "Min: " << *(std::min_element(vec.begin(),vec.end())) << std::endl;
  max = *(std::max_element(vec.begin(),vec.end()));
  min = *(std::min_element(vec.begin(),vec.end()));
}

void max_min(const std::string& var, const std::vector<int>& vec, int& max, int& min)
{
  std::cout << var << std::endl;
  std::cout << "Max: " << *(std::max_element(vec.begin(),vec.end())) << std::endl;
  std::cout << "Min: " << *(std::min_element(vec.begin(),vec.end())) << std::endl;
  max = *(std::max_element(vec.begin(),vec.end()));
  min = *(std::min_element(vec.begin(),vec.end()));
}

void FixTitle(TPaveText& pave, const std::string& title)
{
  pave.SetTextSize(0.048);
  pave.SetTextFont(102);
  pave.SetFillColor(0);
  pave.SetBorderSize(0);
  pave.AddText(title.c_str());
}
