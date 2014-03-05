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
  
  std::vector< std::string > file_list;
  std::ifstream infiles;
  infiles.open(file_input.c_str());
  std::string holder;
  while ( infiles >> holder )
    file_list.push_back(holder);
  infiles.close();

  numi::EvRate *bottom = new numi::EvRate(dir_bottom,genie_file,file_list,true,false,false);
  bottom->SetLowerVzCut(70000);
  bottom->MakeHists("bottom_dump_cut_out_file.root",bottom->BottomArea());
  delete bottom;

  numi::EvRate *length = new numi::EvRate(dir_length,genie_file,file_list,false,true,false);
  length->SetLowerVzCut(70000);
  length->MakeHists("length_dump_cut_out_file.root",length->LengthArea());
  delete length;

  /*
  numi::EvRate *normal = new numi::EvRate(dir_normal,genie_file,file_list,false,false,true);
  normal->MakeHists("normal_out_file.root",normal->NormalArea());
  delete normal;
  */

  return 0;
}
