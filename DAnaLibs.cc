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
