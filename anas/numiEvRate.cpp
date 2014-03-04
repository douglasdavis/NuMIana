#include <iostream>
#include <fstream>
#include "EvRate.hh"

int main(int argc, char *argv[])
{
  std::string dir_bottom = argv[1];
  std::string dir_length = argv[2];
  std::string dir_normal = argv[3];
  std::string genie_file = argv[4];
  Int_t       nu_pdg     = atoi(argv[5]);
  
  std::vector< std::string > file_list;
  std::ifstream infiles;
  infiles.open("file_list.txt");
  std::string holder;
  while ( infiles >> holder )
    file_list.push_back(holder);
  infiles.close();

  /*
  numi::EvRate *bottom = new numi::EvRate(dir_bottom,
					  genie_file,
					  file_list,
					  nu_pdg,
					  true,
					  false,
					  false);

  bottom->MakeHists("bottom_out_file.root");
  delete bottom;
  
  numi::EvRate *length = new numi::EvRate(dir_length,
					  genie_file,
					  file_list,
					  nu_pdg,
					  false,
					  true,
					  false);

  length->MakeHists("length_out_file.root");
  delete length;
  */

  numi::EvRate *normal = new numi::EvRate(dir_normal,
					  genie_file,
					  file_list,
					  nu_pdg,
					  false,
					  false,
					  true);

  normal->MakeHists("normal_test_file.root",normal->NormalArea());
  delete normal;

  return 0;

}
