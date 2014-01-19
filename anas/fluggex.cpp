#include <iostream>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <algorithm>

void max_min(const std::string& var, const std::vector<double>& vec);

int main()
{
  TFile the_file("FluxFLUGG.root");
  TTree *the_tree = (TTree*)the_file.Get("h10");

  double Vx, Vy, Vz, tvx, tvy, tvz;
  std::vector<double> _Vx, _Vy, _Vz, _tvx, _tvy, _tvz;

  the_tree->SetBranchAddress("Vx", &Vx);
  the_tree->SetBranchAddress("Vy", &Vy);
  the_tree->SetBranchAddress("Vz", &Vz);
  the_tree->SetBranchAddress("tvx",&tvx);
  the_tree->SetBranchAddress("tvy",&tvy);
  the_tree->SetBranchAddress("tvz",&tvz);

  for ( auto entry = 0; entry < the_tree->GetEntries(); entry++ ) {
    the_tree->GetEntry(entry);
    _Vx.push_back(Vx);
    _Vy.push_back(Vy);
    _Vz.push_back(Vz);
    _tvx.push_back(tvx);
    _tvy.push_back(tvy);
    _tvz.push_back(tvz);
  }
  
  max_min("tvz",_tvz);

  return 0;
  
}

void max_min(const std::string& var, const std::vector<double>& vec)
{
  std::cout << var << std::endl;
  std::cout << "Max: " << *(std::max_element(vec.begin(),vec.end())) << std::endl;
  std::cout << "Min: " << *(std::min_element(vec.begin(),vec.end())) << std::endl;
}
