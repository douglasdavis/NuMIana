#include <iostream>
#include <fstream>
#include "FullDistEnergy.hh"

int main(int argc, char *argv[])
{
  std::string file_input = argv[1];
  std::string dir_bottom = argv[2];
  std::string dir_length = argv[3];
  std::string dir_normal = argv[4];
  std::string genie_file = argv[5];

  std::vector< std::string > file_list;
  std::ifstream infiles;
  infiles.open(file_input.c_str());
  std::string holder;
  while ( infiles >> holder )
    file_list.push_back(holder);
  infiles.close();

  numi::FullDistEnergy *bottom = new numi::FullDistEnergy(dir_bottom,genie_file,file_list,true,false,false);
  bottom->MakeHists("histogram_files/full_de_bottom.root",bottom->BottomArea());
  delete bottom;

  numi::FullDistEnergy *length = new numi::FullDistEnergy(dir_length,genie_file,file_list,false,true,false);
  length->MakeHists("histogram_files/full_de_length.root",length->LengthArea());
  delete length;

  numi::FullDistEnergy *normal = new numi::FullDistEnergy(dir_normal,genie_file,file_list,true,false,false);
  normal->MakeHists("histogram_files/full_de_normal.root",normal->NormalArea());
  delete normal;

  return 0;
}
