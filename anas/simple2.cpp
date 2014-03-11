#include "simpleAna2.hh"
#include "TH1D.h"
#include "TCanvas.h"
#include "TApplication.h"
#include <vector>

using namespace numi;

int main(int argc, char *argv[])
{
  std::string file_name = argv[1];
  simpleAna2 *j = new simpleAna2(file_name);
  
  auto k = j->VectorOfV("pz");

  TH1D *h = new TH1D("h","histogram test",100,1,0);
  for ( auto const& i : k )
    h->Fill(i);

  TApplication tapp("tapp",&argc,argv);
  TCanvas *c = new TCanvas("c","c");
  h->Draw();
  tapp.Run();
  return 0;
}
