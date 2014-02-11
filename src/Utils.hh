#include "TH1D.h"
#include "TPaveText.h"
#include "TTree.h"
#include <vector>
#include <map>
#include <iostream>
#include <utility>

#ifndef UTILS_HH
#define UTILS_HH

void FillTH1DFromVec(TH1D& histogram, const std::vector<double>& values);

void FillTH1DFromVec(TH1D& histogram, const std::vector<double>& values, const double& cut);

void max_min(const std::string& var, const std::vector<double>& vec, double& max, double& min);

void max_min(const std::string& var, const std::vector<int>& vec, int& max, int& min);

void FixTitle(TPaveText& pave, const std::string& title);

std::string ndecayToString(int n, std::map< int, std::string > code_map);

std::string ppmediumToString(int n, std::map< int, std::string > code_map);

void PrintDecays(const std::vector<int>& ndecay_vec,
		 const std::map< int, std::string >& code_map);

void Print_ndecayppmedium(const std::vector< std::pair<int,int> >& ana_data,
			  const std::map< int, std::string >& n_code_map,
			  const std::map< int, std::string >& p_code_map);

void Print_ppmediumndecay(const std::vector< std::pair<int,int> >& ana_data,
			  const std::map< int, std::string >& p_code_map,
			  const std::map< int, std::string >& n_code_map);


void FillHistogramFromTree(TH1D *hist, TTree *the_tree, const std::string var_name);

void FillVectorFromTree(std::vector<double>& vec, const std::string& var_name);

#endif
