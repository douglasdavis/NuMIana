#include <iostream>
#include <algorithm>
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

/// ____________________________________________________________________________________

Ana::~Ana() {}

/// ____________________________________________________________________________________

void Ana::SetupTitle(const std::string& title_)
{
  PlotTitle = new TPaveText(0.6485149,0.9311224,0.8778878,0.9821429,"brNDC");
  PlotTitle->SetTextSize(0.048);
  PlotTitle->SetTextFont(102);
  PlotTitle->SetFillColor(0);
  PlotTitle->SetBorderSize(0);
  PlotTitle->AddText(title_.c_str());
}

/// ____________________________________________________________________________________

void Ana::FillTH1D(TH1D& histogram, const std::vector<double>& values)
{
  for ( auto const &val : values )
    histogram.Fill(val);
}

/// ____________________________________________________________________________________

void Ana::FillTH1D(TH1D& histogram, const std::vector<double>& values, const double& cut)
{
  for ( auto const &val : values )
    if ( val >= cut ) 
      histogram.Fill(val);
}

/// ____________________________________________________________________________________

void Ana::max_min(const std::string& var, const std::vector<double>& vec, double& max, double& min)
{
  std::cout << var << std::endl;
  std::cout << "Max: " << *(std::max_element(vec.begin(),vec.end())) << std::endl;
  std::cout << "Min: " << *(std::min_element(vec.begin(),vec.end())) << std::endl;
  max = *(std::max_element(vec.begin(),vec.end()));
  min = *(std::min_element(vec.begin(),vec.end()));
}

/// ____________________________________________________________________________________

void Ana::max_min(const std::string& var, const std::vector<int>& vec, int& max, int& min)
{
  std::cout << var << std::endl;
  std::cout << "Max: " << *(std::max_element(vec.begin(),vec.end())) << std::endl;
  std::cout << "Min: " << *(std::min_element(vec.begin(),vec.end())) << std::endl;
  max = *(std::max_element(vec.begin(),vec.end()));
  min = *(std::min_element(vec.begin(),vec.end()));
}

/// ____________________________________________________________________________________

void Ana::FixTitle(TPaveText& pave, const std::string& title)
{
  pave.SetTextSize(0.048);
  pave.SetTextFont(102);
  pave.SetFillColor(0);
  pave.SetBorderSize(0);
  pave.AddText(title.c_str());
}

/// ____________________________________________________________________________________

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

/// ____________________________________________________________________________________

// One of the most confusing peices of code I've probably ever written
// Synopsis:
// First we declare two maps, one which has key that is ndecay and entry
// that is a vector containing all the ppmedium codes for events that had the ndecay
// The second map has key which is ppmedium code and value which is total # of events
// with that ppmedium code. (this is for each ndecay, will explain later here).
// We then fill the first map by looping through the vector of pairs which is
// each event's ndecay and ppmedium. Now we have the map which contains each ndecay
// and the the vector of ppmediums for each ndecay
// Then we loop through that map to get the total number of neutrinos in the ntuple
// so we can then loop through the map again and start calculating percentages.
// The first percentage we calculate is the percentage of each ndecay for the entire ntuple
// we then loop through the ppmedium codes map to intialize the second map described above
// (key is ppmedium code, value is total number for each ndecay that we're looping through)
// we erase this map during each iteration to clear it for the next ndecay to show the
// percentages for. We have to loop through the vector which is the value of the first map
// to fill define the value of the second map. This then allows us to calculate the percentage
// of each ppmedium for each ndecay. Then it starts all over with a fresh count of each
// ppmedium for each ndecay. I might do the same where I swap ppmedium and ndecay.
// ... if Karol wants it.

void Ana::Print_ndecayppmedium(const std::vector< std::pair<int,int> >& ana_data)
{
  // map (ndecay code, vector of ppmedium codes with that decay)
  std::map< int, std::vector<int> > m_ndecay_vppmedium;
  // map (ppmedium code, total # of decays with that ppmedium)
  std::map< int, int > m_ppmedium_total;

  // fill the first map
  for ( auto const& entry : ana_data )
    m_ndecay_vppmedium[entry.second].push_back(entry.first);

  // get the total # neutrinos in the ntuple
  unsigned int total_decays = 0;
  for ( auto const& entry : m_ndecay_vppmedium ) {
    total_decays += entry.second.size();
  }
  std::cout << "total_decays = " << total_decays << std::endl;
  // print the ndecay code with the percentage of the total # events with that code
  // print the ndecay with individual ppmedium percentages
  for ( auto const& entry : m_ndecay_vppmedium ) {
    auto total_entries = entry.second.size();
    std::cout << ndecayToString(entry.first) << " total: " << total_entries
	      << " percent: " << 100*((double)total_entries/(double)total_decays) << std::endl;
    
    // initialize map that counts total #ppmedium for each ndecay
    for ( auto const& entry_2: fppmediumCodeMap )
      m_ppmedium_total[entry_2.first] = 0;
    
    // get that total number of ppmed codes for each one
    for ( auto const& ppmed_code : entry.second ) {
      m_ppmedium_total[ppmed_code]++;
    }

    // loop through the total ppmed code map to get percentages
    for ( auto const& ppmed_counter : m_ppmedium_total ) {
      std::cout << "  ** " << ppmed_counter.first  << " "
		<< ppmediumToString(ppmed_counter.first) << " percent: "
		<< 100*((double)ppmed_counter.second/(double)total_entries) << std::endl;
      
    }
  }  

}

/// ____________________________________________________________________________________

void Ana::Print_ppmediumndecay(const std::vector< std::pair<int,int> >& ana_data)
{
  // map (ppmedium code, vector of ndecay codes with that ppmedium)
  std::map< int, std::vector<int> > m_ppmedium_vndecay;
  // fill the map
  for ( auto const& entry : ana_data ) {
    m_ppmedium_vndecay[entry.first].push_back(entry.second);
  }
  
  // get the total # neutrinos in the ntuple
  unsigned int total_media = 0;
  for ( auto const& entry : m_ppmedium_vndecay) {
    total_media += entry.second.size();
  }
  
  // print the ppmedium code with the percentage of the total # events with that code
  for ( auto const& entry : m_ppmedium_vndecay ) {
    auto total_entries = entry.second.size();
    std::cout << ppmediumToString(entry.first) << " total: " << total_entries
	      << " percent: " << 100*((double)total_entries/(double)total_media) << std::endl;
  }

}
