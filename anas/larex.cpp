#include "LArAna.hh"
#include "WindowAna.hh"
#include "DAnaLibs.hh"
#include <iostream>
#include "TApplication.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "looks.h"

int main(int argc, char *argv[])
{
  looks();
  std::string file_name1 = argv[1];
  std::string file_name2 = argv[2];

  lar::LArAna       *lar_ana    = new lar::LArAna(file_name1);
  simple::WindowAna *window_ana = new simple::WindowAna(file_name2);

  
  return 0;
}
