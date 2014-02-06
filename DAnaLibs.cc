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

void PrintDecays(const std::vector<int>& ndecay_vec)
{
  std::cout << "====================================" << std::endl
	    << "          Printing ndecays          " << std::endl
	    << "====================================" << std::endl;
  
  int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0, d7 = 0,
    d8 = 0, d9 = 0, d10 = 0, d11 = 0, d12 = 0, d13 = 0, d14 = 0;
  int counter = 0; int unk = 0;
  for ( int n : ndecay_vec ) {
    counter++;
    switch(n) {
    case 1:  d1++;  break;
    case 2:  d2++;  break;
    case 3:  d3++;  break;
    case 4:  d4++;  break;    
    case 5:  d5++;  break;
    case 6:  d6++;  break;
    case 7:  d7++;  break;
    case 8:  d8++;  break;
    case 9:  d9++;  break;
    case 10: d10++; break;
    case 11: d11++; break;
    case 12: d12++; break;
    case 13: d13++; break;
    case 14: d14++; break;
    default:
      unk++;
      break;
    }
  }
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
}

const std::string ndecayToString(const int& n)
{
  if      ( n == 1   ) { return "K0L -> nue pi- e+";      }
  else if ( n == 2   ) { return "K0L -> nuebar pi+ e-";   }
  else if ( n == 3   ) { return "K0L -> numu pi- mu+";    }
  else if ( n == 4   ) { return "K0L -> numubar pi+ mu-"; }
  else if ( n == 5   ) { return "K+  -> numu mu+";        }
  else if ( n == 6   ) { return "K+  -> nue pi0 e+";      }
  else if ( n == 7   ) { return "K+  -> numu pi0 mu+";    }
  else if ( n == 8   ) { return "K-  -> numubar mu-";     }
  else if ( n == 9   ) { return "K-  -> nuebar pi0 e-";   }
  else if ( n == 10  ) { return "K-  -> numubar pi0 mu-"; }
  else if ( n == 11  ) { return "mu+ -> numubar nue e+";  }
  else if ( n == 12  ) { return "mu- -> numu nuebar e-";  }
  else if ( n == 13  ) { return "pi+ -> numu mu+";        }
  else if ( n == 14  ) { return "pi- -> numubar mu-";     }
  else if ( n == 999 ) { return "Other";                  }
  else                 { return "BAD BAD BAD";            }
}
