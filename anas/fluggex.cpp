#include <iostream>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include "DAnaLibs.hh"
#include <algorithm>

int main(int argc, char *argv[])
{
  std::string afile = argv[1];
  TFile the_file(afile.c_str());
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
