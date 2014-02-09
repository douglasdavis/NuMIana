#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>
#include <fstream>
#include "Ana.hh"

Ana::Ana()
{
  int         int_code;
  std::string str_code;
  
  std::ifstream ppmedium_config;
  ppmedium_config.open("config/ppmediumCodes.dat");
  while ( ppmedium_config >> int_code >> str_code )
    fppmediumCodeMap[int_code] = str_code;
  ppmedium_config.close();
  
  std::ifstream ndecay_config;
  ndecay_config.open("config/ndecayCodes.dat");
  while ( ndecay_config >> int_code >> str_code )
    fndecayCodeMap[int_code] = str_code;
  ndecay_config.close();
}

Ana::~Ana() {}

void Ana::SetupTitle(const std::string& title_)
{
  PlotTitle = new TPaveText(0.6485149,0.9311224,0.8778878,0.9821429,"brNDC");
  PlotTitle->SetTextSize(0.048);
  PlotTitle->SetTextFont(102);
  PlotTitle->SetFillColor(0);
  PlotTitle->SetBorderSize(0);
  PlotTitle->AddText(title_.c_str());
}


void Ana::FillTH1D(TH1D& histogram, const std::vector<double>& values)
{
  for ( auto const &val : values )
    histogram.Fill(val);
}

void Ana::FillTH1D(TH1D& histogram, const std::vector<double>& values, const double& cut)
{
  for ( auto const &val : values )
    if ( val >= cut ) 
      histogram.Fill(val);
}

void Ana::max_min(const std::string& var, const std::vector<double>& vec, double& max, double& min)
{
  std::cout << var << std::endl;
  std::cout << "Max: " << *(std::max_element(vec.begin(),vec.end())) << std::endl;
  std::cout << "Min: " << *(std::min_element(vec.begin(),vec.end())) << std::endl;
  max = *(std::max_element(vec.begin(),vec.end()));
  min = *(std::min_element(vec.begin(),vec.end()));
}

void Ana::max_min(const std::string& var, const std::vector<int>& vec, int& max, int& min)
{
  std::cout << var << std::endl;
  std::cout << "Max: " << *(std::max_element(vec.begin(),vec.end())) << std::endl;
  std::cout << "Min: " << *(std::min_element(vec.begin(),vec.end())) << std::endl;
  max = *(std::max_element(vec.begin(),vec.end()));
  min = *(std::min_element(vec.begin(),vec.end()));
}

void Ana::FixTitle(TPaveText& pave, const std::string& title)
{
  pave.SetTextSize(0.048);
  pave.SetTextFont(102);
  pave.SetFillColor(0);
  pave.SetBorderSize(0);
  pave.AddText(title.c_str());
}

void Ana::PrintDecays(const std::vector<int>& ndecay_vec)
{
  int d[15] = {0};
  int counter = 0;
  int unk = 0;
  for ( int n : ndecay_vec ) {
    counter++;
    if ( n != 999 )
      d[n]++;
    else
      d[0]++;
  }
  
  for ( auto const& entry : fndecayCodeMap ) {
    if ( entry.first != 999 ) {
      std::cout << entry.first << " " << entry.second << " "
		<< d[entry.first] << " percent: " << 100*(double)d[entry.first]/(double)counter
		<< std::endl;
    }
    else { 
      std::cout << entry.first << " " << entry.second << " "
		<< d[0] << " percent: " << 100*(double)d[0]/(double)counter
		<< std::endl;
    }
  }
}

void Ana::Print_ndecayppmedium(const std::vector< std::pair<int,int> >& ana_data)
{
  std::map< int, std::vector<int> > m_ndecay_vppmedium;
  for ( auto const& entry : ana_data ) {
    m_ndecay_vppmedium[entry.second].push_back(entry.first);
  }

  unsigned int total_decays = 0;
  for ( auto const& entry : m_ndecay_vppmedium ) {
    total_decays += entry.second.size();
  }

  for ( auto const& entry : m_ndecay_vppmedium ) {
    auto total_entries = entry.second.size();
    std::cout << ndecayToString(entry.first) << " total: " << total_entries
	      << " percent: " << 100*((double)total_entries/(double)total_decays) << std::endl;
  }  
}

void Ana::Print_ppmediumndecay(const std::vector< std::pair<int,int> >& ana_data)
{
  std::map< int, std::vector<int> > m_ppmedium_vndecay;
  for ( auto const& entry : ana_data ) {
    m_ppmedium_vndecay[entry.first].push_back(entry.second);
  }
  
  unsigned int total_media = 0;
  for ( auto const& entry : m_ppmedium_vndecay) {
    total_media += entry.second.size();
  }
  
  for ( auto const& entry : m_ppmedium_vndecay ) {
    auto total_entries = entry.second.size();
    std::cout << ppmediumToString(entry.first) << " total: " << total_entries
	      << " percent: " << 100*((double)total_entries/(double)total_media) << std::endl;
  }
}
