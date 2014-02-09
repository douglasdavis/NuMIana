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
    switch(n) {
    case 1:  d[1]++;  break;
    case 2:  d[2]++;  break;
    case 3:  d[3]++;  break;
    case 4:  d[4]++;  break;    
    case 5:  d[5]++;  break;
    case 6:  d[6]++;  break;
    case 7:  d[7]++;  break;
    case 8:  d[8]++;  break;
    case 9:  d[9]++;  break;
    case 10: d[10]++; break;
    case 11: d[11]++; break;
    case 12: d[12]++; break;
    case 13: d[13]++; break;
    case 14: d[14]++; break;
    case 999: d[0]++; break;
    default: unk++; break;
    }
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
  /*
  std::cout << "1   K0L -> nue pi- e+      : " << d1  
	    << " :: " << 100*(double)d1/(double)counter  << std::endl
	    << "2   K0L -> nuebar pi+ e-   : " << d2  
	    << " :: " << 100*(double)d2/(double)counter  << std::endl 
	    << "3   K0L -> numu pi- mu+    : " << d3  
	    << " :: " << 100*(double)d3/(double)counter  << std::endl
	    << "4   K0L -> numubar pi+ mu- : " << d4  
	    << " :: " << 100*(double)d4/(double)counter  << std::endl
	    << "5   K+  -> numu mu+        : " << d5  
	    << " :: " << 100*(double)d5/(double)counter  << std::endl
	    << "6   K+  -> nue pi0 e+      : " << d6  
	    << " :: " << 100*(double)d6/(double)counter  << std::endl
	    << "7   K+  -> numu pi0 mu+    : " << d7  
	    << " :: " << 100*(double)d7/(double)counter  << std::endl
	    << "8   K-  -> numubar mu-     : " << d8  
	    << " :: " << 100*(double)d8/(double)counter  << std::endl
	    << "9   K-  -> nuebar pi0 e-   : " << d9  
	    << " :: " << 100*(double)d9/(double)counter  << std::endl
	    << "10  K-  -> numubar pi0 mu- : " << d10 
	    << " :: " << 100*(double)d10/(double)counter << std::endl
	    << "11  mu+ -> numubar nue e+  : " << d11 
	    << " :: " << 100*(double)d11/(double)counter << std::endl
	    << "12  mu- -> numu nuebar e-  : " << d12 
	    << " :: " << 100*(double)d12/(double)counter << std::endl
	    << "13  pi+ -> numu mu+        : " << d13 
	    << " :: " << 100*(double)d13/(double)counter << std::endl
	    << "14  pi- -> numubar mu-     : " << d14 
	    << " :: " << 100*(double)d14/(double)counter << std::endl
	    << "999 unkown                 : " << unk 
	    << " :: " << 100*(double)unk/(double)counter << std::endl;
  */
}

const std::string Ana::ndecayToString(const int& n)
{
  if      ( n == 1   ) { return "K0L_->nue_pi-_e+";      }
  else if ( n == 2   ) { return "K0L_->nuebar_pi+_e-";   }
  else if ( n == 3   ) { return "K0L_->numu_pi-_mu+";    }
  else if ( n == 4   ) { return "K0L_->numubar_pi+_mu-"; }
  else if ( n == 5   ) { return "K+_->numu_mu+";         }
  else if ( n == 6   ) { return "K+_->nue_pi0_e+";       }
  else if ( n == 7   ) { return "K+_->numu_pi0_mu+";     }
  else if ( n == 8   ) { return "K-_->numubar_mu-";      }
  else if ( n == 9   ) { return "K-_->nuebar_pi0_e-";    }
  else if ( n == 10  ) { return "K-_->numubar_pi0_mu-";  }
  else if ( n == 11  ) { return "mu+_->numubar_nue_e+";  }
  else if ( n == 12  ) { return "mu-_->numu_nuebar_e-";  }
  else if ( n == 13  ) { return "pi+_->numu_mu+";        }
  else if ( n == 14  ) { return "pi-_->numubar_mu-";     }
  else if ( n == 999 ) { return "Other";                 }
  else                 { return "ok";                    }
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
