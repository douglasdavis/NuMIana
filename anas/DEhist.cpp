#include <iostream>
#include <fstream>
#include "DistEnergy.hh"

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

  numi::DistEnergy *bottom = new numi::DistEnergy(dir_bottom,genie_file,file_list,true,false,false);
  bottom->MakeHists("histogram_files/de_bottom.root",bottom->BottomArea(),3.14,.002,0.043,0.88);
  delete bottom;

  numi::DistEnergy *length = new numi::DistEnergy(dir_length,genie_file,file_list,false,true,false);
  length->MakeHists("histogram_files/de_length.root",length->LengthArea(),3.14,.002,0.043,0.88);
  delete length;

  numi::DistEnergy *normal = new numi::DistEnergy(dir_normal,genie_file,file_list,true,false,false);
  normal->MakeHists("histogram_files/de_normal.root",normal->NormalArea(),3.14,.002,0.043,0.88);
  delete normal;

  return 0;
}


