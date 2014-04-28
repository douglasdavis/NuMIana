#ifndef UTILS_HH
#define UTILS_HH

#include "TROOT.h"
#include "TH1D.h"
#include "TPaveText.h"
#include "TTree.h"
#include <vector>
#include <map>
#include <iostream>
#include <utility>

namespace numi {

  namespace utils {

    void FillTH1DFromVec(TH1D& histogram, const std::vector<Double_t>& values);

    void FillTH1DFromVec(TH1D& histogram, const std::vector<Double_t>& values, const Double_t& cut);

    void max_min(const std::string& var, const std::vector<Double_t>& vec, Double_t& max, Double_t& min);

    void max_min(const std::string& var, const std::vector<Int_t>& vec, Int_t& max, Int_t& min);

    void FixTitle(TPaveText& pave, const std::string& title);

    std::string ndecayToString(Int_t n, std::map< Int_t, std::string > code_map);

    std::string ppmediumToString(Int_t n, std::map< Int_t, std::string > code_map);

    void PrintDecays(const std::vector<Int_t>& ndecay_vec,
		     const std::map< Int_t, std::string >& code_map);

    void Print_ndecayppmedium(const std::vector< std::pair<Int_t,Int_t> >& ana_data,
			      const std::map< Int_t, std::string >& n_code_map,
			      const std::map< Int_t, std::string >& p_code_map);

    void Print_ppmediumndecay(const std::vector< std::pair<Int_t,Int_t> >& ana_data,
			      const std::map< Int_t, std::string >& p_code_map,
			      const std::map< Int_t, std::string >& n_code_map);
    
    Double_t OscProb(const Double_t& LoverE,
		     const Double_t& dm2,
		     const Double_t& s22theta);
    
  }
}

#endif
