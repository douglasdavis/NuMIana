#include "LArAna.hh"
#include <iostream>
#include "TApplication.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "looks.h"

int main(int argc, char *argv[])
{
  looks();
  std::string file_name = argv[1];
  lar::LArAna *my_ana = new lar::LArAna(file_name);
  
  return 0;
}
