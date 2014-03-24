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
  bottom->MakeHists("histogram_files/bottom_2013.root",bottom->BottomArea());
  delete bottom;

  numi::EvRate *length = new numi::EvRate(dir_length,genie_file,file_list,false,true,false);
  length->MakeHists("histogram_files/length_2013.root",length->LengthArea());
  delete length;
  
  numi::EvRate *normal = new numi::EvRate(dir_normal,genie_file,file_list,false,false,true);
  normal->MakeHists("histogram_files/normal_2013.root",normal->NormalArea());
  delete normal;

  numi::EvRate *bcut = new numi::EvRate(dir_bottom,genie_file,file_list,true,false,false);
  bcut->SetLowerVzLimit(7e4);
  bcut->MakeHists("histogram_files/bottom_2013_absorber_cut.root",bcut->BottomArea());
  delete bcut;

  numi::EvRate *lcut = new numi::EvRate(dir_length,genie_file,file_list,false,true,false);
  lcut->SetLowerVzLimit(7e4);
  lcut->MakeHists("histogram_files/length_2013_absorber_cut.root",lcut->LengthArea());
  delete lcut;

  numi::EvRate *bottomt = new numi::EvRate(dir_bottom,genie_file,file_list,true,false,false);
  bottomt->SetUpperVzLimit(1e4);
  bottomt->MakeHists("histogram_files/bottom_2013_target_cut.root",bottom->BottomArea());
  delete bottomt;

  numi::EvRate *lengtht = new numi::EvRate(dir_length,genie_file,file_list,false,true,false);
  lengtht->SetUpperVzLimit(1e4);
  lengtht->MakeHists("histogram_files/length_2013_target_cut.root",length->LengthArea());
  delete lengtht;

  numi::EvRate *normalt = new numi::EvRate(dir_normal,genie_file,file_list,false,false,true);
  normalt->SetUpperVzLimit(1e4);
  normalt->MakeHists("histogram_files/normal_2013_target_cut.root",normal->NormalArea());
  delete normalt;

  numi::EvRate *bottomp = new numi::EvRate(dir_bottom,genie_file,file_list,true,false,false);
  bottomp->SetUpperVzLimit(7e4);
  bottomp->SetLowerVzLimit(1e4);
  bottomp->MakeHists("histogram_files/bottom_2013_pipe_cut.root",bottom->BottomArea());
  delete bottomp;

  numi::EvRate *lengthp = new numi::EvRate(dir_length,genie_file,file_list,false,true,false);
  lengthp->SetUpperVzLimit(7e4);
  lengthp->SetLowerVzLimit(1e4);
  lengthp->MakeHists("histogram_files/length_2013_pipe_cut.root",length->LengthArea());
  delete lengthp;

  numi::EvRate *normalp = new numi::EvRate(dir_normal,genie_file,file_list,false,false,true);
  normalp->SetUpperVzLimit(7e4);
  normalp->SetLowerVzLimit(1e4);
  normalp->MakeHists("histogram_files/normal_2013_pipe_cut.root",normal->NormalArea());
  delete normalp;

  return 0;
}
