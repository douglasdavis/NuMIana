#include <iostream>
#include <fstream>
#include <cmath>
#include "TFile.h"
#include "TTree.h"

int main()
{
  std::string flugg_prefix="/nusoft/data/flux/flugg/flugg_fluka2008_2013.11.15/mn_000z200i/flugg/flugg_mn000z200i_lowth_";
  std::string simpB_prefix="/uboone/data/numi_gsimple_fluxes_02.27.2014/zDF/bottom/filt_gsimple_microboone-numi_mn000z200i_lowth_";
  std::string simpL_prefix="/uboone/data/numi_gsimple_fluxes_02.27.2014/zDF/length/filt_gsimple_microboone-numi_mn000z200i_lowth_";
  std::string simpN_prefix="/uboone/data/numi_gsimple_fluxes_02.27.2014/zDF/normal/filt_gsimple_microboone-numi_mn000z200i_lowth_";

  std::string   trash_string;
  std::string   tfile_string;

  std::ifstream file_numbers;
  file_numbers.open("/uboone/app/users/ddavis/NuMIana/file_lists/numbers_2013_cut2.txt");

  double vx_flugg, vy_flugg, vz_flugg;
  double vx_simpB, vy_simpB, vz_simpB;
  double vx_simpL, vy_simpL, vz_simpL;
  double vx_simpN, vy_simpN, vz_simpN;

  //  while ( file_numbers >> trash_string ) {
  trash_string = "001";
  tfile_string = flugg_prefix+trash_string+".root";
  TFile *flugg_file = new TFile(tfile_string.c_str());
  TTree *flugg_tree = (TTree*)flugg_file->Get("h10");

  tfile_string = simpB_prefix+trash_string+"_00001.root";
  TFile *simpB_file = new TFile(tfile_string.c_str());
  TTree *simpB_tree = (TTree*)simpB_file->Get("NuMI");

  flugg_tree->SetBranchAddress("Vx",&vx_flugg);
  flugg_tree->SetBranchAddress("Vy",&vy_flugg);
  flugg_tree->SetBranchAddress("Vz",&vz_flugg);

  simpB_tree->SetBranchAddress("vx",&vx_simpB);
  simpB_tree->SetBranchAddress("vx",&vy_simpB);
  simpB_tree->SetBranchAddress("vx",&vz_simpB);

  for ( auto i = 0; i < flugg_tree->GetEntries(); ++i ) {
    flugg_tree->GetEntry(i);
    if ( i%1000 == 0 ) std::cout << i << std::endl;
    for ( auto j = 0; j < simpB_tree->GetEntries(); ++j ) {
      //	std::cout << " ok " << i << " " << j << std::endl;
      simpB_tree->GetEntry(j);
      if ( ( std::fabs(vx_flugg - vx_simpB) < 0.0001 ) && ( std::fabs(vy_flugg - vy_simpB) < 0.0001 ) && ( std::fabs(vz_flugg - vz_simpB) < 0.0001 ) )
	std::cout << "ok ya " << i << " " << j << std::endl;
    }
  }

  delete flugg_file;
  delete simpB_file;

  //  }

  file_numbers.close();
  
  return 0;
}

