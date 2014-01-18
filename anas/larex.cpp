#include "LArAna.hh"
#include <iostream>
#include "TApplication.h"
#include "TH1D.h"
#include "TCanvas.h"

int main(int argc, char *argv[])
{
  // SETUP
  std::string file_name = argv[1];
  lar::LArAna *my_ana = new lar::LArAna(file_name);
  std::vector< std::vector<double> > startx = my_ana->StartX();



  // GETTING SOME DATA
  TH1D *filler = new TH1D("filler","hist",100,1,0);
  int counter = 0;
  for ( auto const &j : startx ) {
    counter = counter + j.size();
    for ( auto const &k : j )
      filler->Fill(k);
  }
  std::cout << counter << std::endl;
  


  // DRAWING
  TApplication *tapp = new TApplication("tapp",&argc,argv);
  TCanvas *can = new TCanvas();
  filler->Draw();
  tapp->Run();

  return 0;
}
