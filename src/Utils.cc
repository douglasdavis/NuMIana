#include "Utils.hh"
#include <algorithm>

void FillTH1DFromVec(TH1D& histogram, const std::vector<Double_t>& values)
{
  for ( auto const &val : values )
    histogram.Fill(val);
}

void FillTH1DFromVec(TH1D& histogram, const std::vector<Double_t>& values, const Double_t& cut)
{
  for ( auto const &val : values )
    if ( val >= cut ) 
      histogram.Fill(val);
}

void max_min(const std::string& var, const std::vector<Double_t>& vec, Double_t& max, Double_t& min)
{
  std::cout << var << std::endl;
  std::cout << "Max: " << *(std::max_element(vec.begin(),vec.end())) << std::endl;
  std::cout << "Min: " << *(std::min_element(vec.begin(),vec.end())) << std::endl;
  max = *(std::max_element(vec.begin(),vec.end()));
  min = *(std::min_element(vec.begin(),vec.end()));
}

void max_min(const std::string& var, const std::vector<Int_t>& vec, Int_t& max, Int_t& min)
{
  std::cout << var << std::endl;
  std::cout << "Max: " << *(std::max_element(vec.begin(),vec.end())) << std::endl;
  std::cout << "Min: " << *(std::min_element(vec.begin(),vec.end())) << std::endl;
  max = *(std::max_element(vec.begin(),vec.end()));
  min = *(std::min_element(vec.begin(),vec.end()));
}

std::string ndecayToString(Int_t n, std::map< Int_t, std::string > code_map)
{
  std::string return_me = code_map[n];
  return return_me;
}

std::string ppmediumToString(Int_t n, std::map< Int_t, std::string > code_map)
{
  std::string return_me = code_map[n];
  return return_me;
}

void FixTitle(TPaveText& pave, const std::string& title)
{
  pave.SetTextSize(0.048);
  pave.SetTextFont(102);
  pave.SetFillColor(0);
  pave.SetBorderSize(0);
  pave.AddText(title.c_str());
}

void PrintDecays(const std::vector<Int_t>& ndecay_vec,
		 const std::map< Int_t, std::string >& code_map)
{
  Int_t d[15] = {0};
  Int_t counter = 0;
  Int_t unk = 0;
  for ( Int_t n : ndecay_vec ) {
    counter++;
    if ( n != 999 )
      d[n]++;
    else
      d[0]++;
  }
  
  for ( auto const& entry : code_map ) {
    if ( entry.first != 999 ) {
      std::cout << entry.first << " " << entry.second << " "
		<< d[entry.first] << " percent: " << 100*(Double_t)d[entry.first]/(Double_t)counter
		<< std::endl;
    }
    else { 
      std::cout << entry.first << " " << entry.second << " "
		<< d[0] << " percent: " << 100*(Double_t)d[0]/(Double_t)counter
		<< std::endl;
    }
  }
}

/// ____________________________________________________________________________________

//////////////////////////////////////////////////////////////////////////////////////////////
/// The following two functions are pretty much identical and confusing
/// Synopsis:
/// First we declare two maps, one which has key that is ndecay and entry
/// that is a vector containing all the ppmedium codes for events that had the ndecay
/// The second map has key which is ppmedium code and value which is total # of events
/// with that ppmedium code. (this is for each ndecay, will explain later here).
/// We then fill the first map by looping through the vector of pairs which is
/// each event's ndecay and ppmedium. Now we have the map which contains each ndecay
/// and the the vector of ppmediums for each ndecay
/// Then we loop through that map to get the total number of neutrinos in the ntuple
/// so we can then loop through the map again and start calculating percentages.
/// The first percentage we calculate is the percentage of each ndecay for the entire ntuple
/// we then loop through the ppmedium codes map to intialize the second map described above
/// (key is ppmedium code, value is total number for each ndecay that we're looping through)
/// we erase this map during each iteration to clear it for the next ndecay to show the
/// percentages for. We have to loop through the vector which is the value of the first map
/// to fill define the value of the second map. This then allows us to calculate the percentage
/// of each ppmedium for each ndecay. Then it starts all over with a fresh count of each
/// ppmedium for each ndecay. Everything gets printed.
/// Same thing is done switching ndecay and ppmedium places in next function
//////////////////////////////////////////////////////////////////////////////////////////////

void Print_ndecayppmedium(const std::vector< std::pair< Int_t,Int_t > >& ana_data,
			  const std::map< Int_t, std::string >& n_code_map,
			  const std::map< Int_t, std::string >& p_code_map)
{
  std::map< Int_t, std::vector<Int_t> > m_ndecay_vppmedium;
  std::map< Int_t, Int_t > m_ppmedium_total;

  for ( auto const& entry : ana_data )
    m_ndecay_vppmedium[entry.second].push_back(entry.first);

  UInt_t total_decays = 0;
  for ( auto const& entry : m_ndecay_vppmedium ) {
    total_decays += entry.second.size();
  }

  std::cout << "total_decays = " << total_decays << std::endl;

  for ( auto const& entry : m_ndecay_vppmedium ) {
    auto total_entries = entry.second.size();
    std::cout << entry.first << " " << ndecayToString(entry.first,n_code_map) << " total: " << total_entries
	      << " percent: " << 100*((Double_t)total_entries/(Double_t)total_decays) << std::endl;
    
    for ( auto const& entry_2: p_code_map )
      m_ppmedium_total[entry_2.first] = 0;
    
    for ( auto const& ppmed_code : entry.second )
      m_ppmedium_total[ppmed_code]++;

    for ( auto const& ppmed_counter : m_ppmedium_total )
      std::cout << "  ** " << ppmed_counter.first  << " "
		<< ppmediumToString(ppmed_counter.first,p_code_map) << " " << ppmed_counter.second  << " percent: "
		<< 100*((Double_t)ppmed_counter.second/(Double_t)total_entries) << std::endl;
      
  }  
}

/// ____________________________________________________________________________________

void Print_ppmediumndecay(const std::vector< std::pair<Int_t,Int_t> >& ana_data,
			  const std::map< Int_t, std::string >& p_code_map,
			  const std::map< Int_t, std::string >& n_code_map)
{
  std::map< Int_t, std::vector<Int_t> > m_ppmedium_vndecay;
  std::map< Int_t, Int_t > m_ndecay_total;

  for ( auto const& entry : ana_data ) {
    m_ppmedium_vndecay[entry.first].push_back(entry.second);
  }
  
  UInt_t total_media = 0;
  for ( auto const& entry : m_ppmedium_vndecay) {
    total_media += entry.second.size();
  }

  std::cout << "total decays: " << total_media << std::endl;
  
  for ( auto const& entry : m_ppmedium_vndecay ) {
    auto total_entries = entry.second.size();
    std::cout << entry.first << " " << ppmediumToString(entry.first,p_code_map) << " total: " << total_entries
	      << " percent: " << 100*((Double_t)total_entries/(Double_t)total_media) << std::endl;

    for ( auto const& entry_2: n_code_map )
      m_ndecay_total[entry_2.first] = 0;

    for ( auto const& ndec_code : entry.second )
      m_ndecay_total[ndec_code]++;

    for ( auto const& ndec_counter : m_ndecay_total )
      std::cout << "  ** " << ndec_counter.first  << " "
		<< ndecayToString(ndec_counter.first,n_code_map) << " " << ndec_counter.second << " percent: "
		<< 100*((Double_t)ndec_counter.second/(Double_t)total_entries) << std::endl;
    
  }
}
