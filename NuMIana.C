#include "NuMIana.h"

NuMIana::NuMIana() {}

NuMIana::NuMIana(std::string file_name)
{
  fFile      = new TFile(file_name.c_str(),"READ");
  fEntryTree = (TTree*)fFile->Get("EntryTree");
  fNuMI_Tree = (TTree*)fFile->Get("NuMI_Tree");

  double wgt, vtxx, vtxy, vtxz;
  double dist, px, py, pz, E;
  int pdg;
  double tpx, tpy, tpz, vx, vy, vz;
  int ndecay, ptype, ppmedium, tptype;
  int run, evtno, entryno;
  
  fEntryTree->SetBranchAddress("wgt", &wgt);
  fEntryTree->SetBranchAddress("vtxx",&vtxx);
  fEntryTree->SetBranchAddress("vtxy",&vtxy);
  fEntryTree->SetBranchAddress("vtxz",&vtxz);
  fEntryTree->SetBranchAddress("dist",&dist);
  fEntryTree->SetBranchAddress("px",  &px);
  fEntryTree->SetBranchAddress("py",  &py);
  fEntryTree->SetBranchAddress("pz",  &pz);
  fEntryTree->SetBranchAddress("E",   &E);
  fEntryTree->SetBranchAddress("pdg", &pdg);

  fNuMI_Tree->SetBranchAddress("tpx",&tpx);
  fNuMI_Tree->SetBranchAddress("tpy",&tpy);
  fNuMI_Tree->SetBranchAddress("tpz",&tpz);
  fNuMI_Tree->SetBranchAddress("vx", &vx);
  fNuMI_Tree->SetBranchAddress("vy", &vy);
  fNuMI_Tree->SetBranchAddress("vz", &vz);

  fNuMI_Tree->SetBranchAddress("ndecay",  &ndecay);
  fNuMI_Tree->SetBranchAddress("ppmedium",&ppmedium);
  fNuMI_Tree->SetBranchAddress("tptype",  &tptype);
  fNuMI_Tree->SetBranchAddress("run",     &run);
  fNuMI_Tree->SetBranchAddress("evtno",   &evtno);
  fNuMI_Tree->SetBranchAddress("entryno", &entryno);

  for ( int i = 0; i < fEntryTree->GetEntries(); i++ ) {
    fEntryTree->GetEntry(i);
    fwgt.push_back(wgt);
    fvtxx.push_back(vtxx);
    fvtxy.push_back(vtxy);
    fvtxz.push_back(vtxz);
    fdist.push_back(dist);
    fpx.push_back(px);
    fpy.push_back(py);
    fpz.push_back(pz);
    fE.push_back(E);
    fpdg.push_back(pdg);
  }
  for ( int i = 0; i < fNuMI_Tree->GetEntries(); i++ ) {
    fNuMI_Tree->GetEntry(i);
    ftpx.push_back(tpx);
    ftpy.push_back(tpy);
    ftpz.push_back(tpz);
    fvx.push_back(vx);
    fvy.push_back(vy);
    fvz.push_back(vz);
    fndecay.push_back(ndecay);
    fppmedium.push_back(ppmedium);
    ftptype.push_back(tptype);
    frun.push_back(run);
    fevtno.push_back(evtno);
    fentryno.push_back(entryno);
  }

}

NuMIana::~NuMIana()
{
  delete fFile;
  delete fNuMI_Tree;
  delete fEntryTree;
}

void NuMIana::PrintDecays()
{
  std::cout << "====================================" << std::endl
	    << "          Printing ndecays          " << std::endl
	    << "====================================" << std::endl;

  int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0, d7 = 0,
    d8 = 0, d9 = 0, d10 = 0, d11 = 0, d12 = 0, d13 = 0, d14 = 0;
  for ( int n : fndecay ) {
    switch(n) {
    case 1:  d1++;  break;
    case 2:  d2++;  break;
    case 3:  d3++;  break;
    case 4:  d4++;  break;    
    case 5:  d5++;  break;
    case 6:  d6++;  break;
    case 7:  d7++;  break;
    case 8:  d8++;  break;
    case 9:  d9++;  break;
    case 10: d10++; break;
    case 11: d11++; break;
    case 12: d12++; break;
    case 13: d13++; break;
    case 14: d14++; break;
    default:
      std::cout << "Warning in NuMIana::PrintDecays() unkown decay number: " << n << std::endl;
      break;
    }
  }
  std::cout << "1   K0L -> nue pi- e+      : " << d1  << std::endl
	    << "2   K0L -> nuebar pi+ e-   : " << d2  << std::endl 
	    << "3   K0L -> numu pi- mu+    : " << d3  << std::endl
	    << "4   K0L -> numubar pi+ mu- : " << d4  << std::endl
	    << "5   K+  -> numu mu+        : " << d5  << std::endl
	    << "6   K+  -> nue pi0 e+      : " << d6  << std::endl
	    << "7   K+  -> numu pi0 mu+    : " << d7  << std::endl
	    << "8   K-  -> numubar mu-     : " << d8  << std::endl
	    << "9   K-  -> nuebar pi0 e-   : " << d9  << std::endl
	    << "10  K-  -> numubar pi0 mu- : " << d10 << std::endl
	    << "11  mu+ -> numubar nue e+  : " << d11 << std::endl
	    << "12  mu- -> numu nuebar e-  : " << d12 << std::endl
	    << "13  pi+ -> numu mu+        : " << d13 << std::endl
	    << "14  pi- -> numubar mu-     : " << d14 << std::endl;
}

void NuMIana::PrintNeutrinos()
{
  int numu = 0, numubar = 0, nue = 0, nuebar = 0;
  for ( int n : fpdg ) {
    switch(n) {
    case 14:  numu++;    break;
    case -14: numubar++; break;
    case 12:  nue++;     break;
    case -12: nuebar++;  break;
    default:
      std::cout << "Warning in NuMIana::PrintNeutrinos(): Unkown pdg code: " << n << std::endl;
      break;
    }
  }
  std::cout << " numu    : " << numu    << std::endl;
  std::cout << " numubar : " << numubar << std::endl;
  std::cout << " nue     : " << nue     << std::endl;
  std::cout << " nuebar  : " << nuebar  << std::endl;
}
