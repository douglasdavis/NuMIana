#include "LNA.hh"
#include <iostream>
#include "TApplication.h"

int main(int argc, char *argv[])
{
  std::string file_name = argv[1];
  TApplication tapp("tapp",&argc,argv);
  numi::LNA *lna = new numi::LNA(0,file_name);
  lna->Loop();
  tapp.Run();
  return 0;
}
