#include <iostream>
#include <algorithm>
#include <vector>
#include "DAnaLibs.hh"

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
