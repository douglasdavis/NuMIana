#include "LArTree.hh"
#include <iostream>
#include "TApplication.h"

int main(int argc, char *argv[])
{
  std::string file_name = argv[1];
  TApplication tapp("tapp",&argc,argv);
  numi::LArTree *lt = new numi::LArTree(0,file_name);
  lt->Loop();
  tapp.Run();
  return 0;
}
