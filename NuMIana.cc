#include "NuMIana.hh"

namespace simple {

  NuMIana::NuMIana() {}

  NuMIana::NuMIana(const std::string& file_name)
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

    fPlotTitle = new TPaveText(0.6485149,0.9311224,0.8778878,0.9821429,"brNDC");
    fPlotTitle->SetTextSize(20);
    fPlotTitle->SetTextFont(63);
    fPlotTitle->SetFillColor(0);
    fPlotTitle->SetBorderSize(0);
  }

  NuMIana::~NuMIana()
  {}

  void NuMIana::PrintDecays()
  {
    std::cout << "====================================" << std::endl
	      << "          Printing ndecays          " << std::endl
	      << "====================================" << std::endl;

    int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0, d7 = 0,
      d8 = 0, d9 = 0, d10 = 0, d11 = 0, d12 = 0, d13 = 0, d14 = 0;
    int counter = 0; int unk = 0;
    for ( int n : fndecay ) {
      counter++;
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
	unk++;
	break;
      }
    }
    std::cout << "1   K0L -> nue pi- e+      : " << d1  
	      << " :: " << 100*(double)d1/(double)counter  << std::endl
	      << "2   K0L -> nuebar pi+ e-   : " << d2  
	      << " :: " << 100*(double)d2/(double)counter  << std::endl 
	      << "3   K0L -> numu pi- mu+    : " << d3  
	      << " :: " << 100*(double)d3/(double)counter  << std::endl
	      << "4   K0L -> numubar pi+ mu- : " << d4  
	      << " :: " << 100*(double)d4/(double)counter  << std::endl
	      << "5   K+  -> numu mu+        : " << d5  
	      << " :: " << 100*(double)d5/(double)counter  << std::endl
	      << "6   K+  -> nue pi0 e+      : " << d6  
	      << " :: " << 100*(double)d6/(double)counter  << std::endl
	      << "7   K+  -> numu pi0 mu+    : " << d7  
	      << " :: " << 100*(double)d7/(double)counter  << std::endl
	      << "8   K-  -> numubar mu-     : " << d8  
	      << " :: " << 100*(double)d8/(double)counter  << std::endl
	      << "9   K-  -> nuebar pi0 e-   : " << d9  
	      << " :: " << 100*(double)d9/(double)counter  << std::endl
	      << "10  K-  -> numubar pi0 mu- : " << d10 
	      << " :: " << 100*(double)d10/(double)counter << std::endl
	      << "11  mu+ -> numubar nue e+  : " << d11 
	      << " :: " << 100*(double)d11/(double)counter << std::endl
	      << "12  mu- -> numu nuebar e-  : " << d12 
	      << " :: " << 100*(double)d12/(double)counter << std::endl
	      << "13  pi+ -> numu mu+        : " << d13 
	      << " :: " << 100*(double)d13/(double)counter << std::endl
	      << "14  pi- -> numubar mu-     : " << d14 
	      << " :: " << 100*(double)d14/(double)counter << std::endl
	      << "999 unkown                 : " << unk 
	      << " :: " << 100*(double)unk/(double)counter << std::endl;
  }

  void NuMIana::PrintNeutrinos()
  {
    std::cout << " ** NEUTRINOS ** " << std::endl;
    int numu = 0, numubar = 0, nue = 0, nuebar = 0;
    int counter = 0;
    for ( int n : fpdg ) {
      counter++;
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
    std::cout << " numu    : " << numu    << " :: " 
	      << 100*(double)numu/(double)counter    << std::endl;
    std::cout << " numubar : " << numubar << " :: " 
	      << 100*(double)numubar/(double)counter << std::endl;
    std::cout << " nue     : " << nue     << " :: " 
	      << 100*(double)nue/(double)counter     << std::endl;
    std::cout << " nuebar  : " << nuebar  << " :: " 
	      << 100*(double)nuebar/(double)counter  << std::endl;
  }

  void NuMIana::PrintDecayLocations()
  {
    // target hall
    int target_hall = 0;
    int target = 0;
    int horn_1 = 0;
    int horn_2 = 0;
    // decay pipe
    int decay_pipe = 0;
    int decay_pipe_pre_ub = 0;
    int decay_pipe_post_ub = 0;
    // int absorber_etc
    int absorber_etc = 0;

    std::cout << "** DECAY LOCATIONS **" << std::endl;
    std::cout << std::endl;
  }
}
