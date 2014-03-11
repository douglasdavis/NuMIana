#include "simpleAna2.hh"
#include "TH1D.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TGaxis.h"
#include <vector>

using namespace numi;

int main(int argc, char *argv[])
{
  TGaxis::SetMaxDigits(3);
  std::string file_name = argv[1];

  // the class which analyzes the file
  simpleAna2 *j = new simpleAna2(file_name);
  
  // a histogram filled with a variable
  // retrieved from the file by the class function
  TH1D *h = new TH1D("h","histogram test",100,1,0);
  auto k = j->Vector_D("pz");
  for ( auto const& i : k )
    h->Fill(i);

  // same as above but now the vector is of pairs
  TH1D *h12  = new TH1D("h12", "nue;E;N",    20,0,6);
  TH1D *ha12 = new TH1D("ha12","nuebar;E;N", 20,0,6); 
  TH1D *h14  = new TH1D("h14", "numu;E;N",   20,0,6);
  TH1D *ha14 = new TH1D("ha14","numubar;E;N",20,0,6);
  auto x = j->VectorPair_I_D("pdg","E");
  for ( auto const& r : x ) {
    if ( r.first == 12 )
      h12->Fill(r.second);
    if ( r.first == 14 )
      h14->Fill(r.second);
    if ( r.first == -12 )
      ha12->Fill(r.second);
    if ( r.first == -14 )
      ha14->Fill(r.second);
  }

  TApplication tapp("tapp",&argc,argv);
  TCanvas *c = new TCanvas("c","c");
  h->Draw();

  TCanvas *c2 = new TCanvas("c2","c2");
  c2->SetLogy();
  h14->Draw();
  ha14->Draw("same");
  h12->Draw("same");
  ha12->Draw("same");

  tapp.Run();
  return 0;
}
