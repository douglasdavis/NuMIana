#include <iostream>
#include "NuMIana.h"
#include "TH3D.h"
#include "TApplication.h"
#include "TCanvas.h"

int main(int argc, char *argv[])
{
  if ( argc < 4 )
    return 0;

  std::string file_name1 = argv[1];
  std::string file_name2 = argv[2];
  std::string file_name3 = argv[3];
  NuMIana my_ana1(file_name1.c_str());
  NuMIana my_ana2(file_name2.c_str());
  NuMIana my_ana3(file_name3.c_str());
  std::vector<double> vtxx1 = my_ana1.vtxx();
  std::vector<double> vtxy1 = my_ana1.vtxy();
  std::vector<double> vtxz1 = my_ana1.vtxz();
  std::vector<double> vtxx2 = my_ana2.vtxx();
  std::vector<double> vtxy2 = my_ana2.vtxy();
  std::vector<double> vtxz2 = my_ana2.vtxz();
  std::vector<double> vtxx3 = my_ana3.vtxx();
  std::vector<double> vtxy3 = my_ana3.vtxy();
  std::vector<double> vtxz3 = my_ana3.vtxz();

  TH3D *h1 = new TH3D("h1","hist;x;y;z",100,1,0,100,1,0,100,1,0);
  TH3D *h2 = new TH3D("h2","hist;x;y;z",100,1,0,100,1,0,100,1,0);
  TH3D *h3 = new TH3D("h3","hist;x;y;z",100,1,0,100,1,0,100,1,0);
  
  for ( int i = 0; i < vtxx1.size(); i++ )
    h1->Fill(vtxx1[i],vtxy1[i],vtxz1[i]);
  for ( int i = 0; i < vtxx2.size(); i++ )
    h1->Fill(vtxx2[i],vtxy2[i],vtxz2[i]);
  for ( int i = 0; i < vtxx3.size(); i++ )
    h1->Fill(vtxx3[i],vtxy3[i],vtxz3[i]);

  TApplication *app = new TApplication("app",&argc,argv);
  TCanvas *c = new TCanvas();
  h1->Draw();
  //h2->Draw("same");
  //h3->Draw("same");
  app->Run();

  /*
  int counter = 0;
  //  std::vector<double>::iterator myitr = test_vector.begin();
  while ( counter < 20 ) {
    std::cout << (*myitr) << std::endl;
    myitr++;
    counter++;
  }
  */

  return 0;
}
