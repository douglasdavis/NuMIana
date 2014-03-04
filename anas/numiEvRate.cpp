#include <iostream>
#include <fstream>
#include "EvRate.hh"

int main(int argc, char *argv[])
{
  std::string file_input = argv[1];
  std::string dir_bottom = argv[2];
  std::string dir_length = argv[3];
  std::string dir_normal = argv[4];
  std::string genie_file = argv[5];
  Int_t       nu_pdg     = atoi(argv[6]);
  
  std::vector< std::string > file_list;
  std::ifstream infiles;
  infiles.open(file_input.c_str());
  std::string holder;
  while ( infiles >> holder )
    file_list.push_back(holder);
  infiles.close();

  numi::EvRate *bottom = new numi::EvRate(dir_bottom,genie_file,file_list,nu_pdg,true,false,false);
  bottom->MakeHists("bottom_out_file.root",bottom->BottomArea());
  delete bottom;

  numi::EvRate *length = new numi::EvRate(dir_length,genie_file,file_list,nu_pdg,false,true,false);
  length->MakeHists("length_out_file.root",length->LengthArea());
  delete length;
  
  numi::EvRate *normal = new numi::EvRate(dir_normal,genie_file,file_list,nu_pdg,false,false,true);
  normal->MakeHists("normal_out_file.root",normal->NormalArea());
  delete normal;

  return 0;
}
