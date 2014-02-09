#include "simpleAna.hh"

simpleAna::simpleAna() {}

simpleAna::simpleAna(const std::string& file_name)
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

  for ( int i = 0; i < fEntryTree->GetEntries(); ++i ) {
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
  for ( int i = 0; i < fNuMI_Tree->GetEntries(); ++i ) {
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

    fppmediumndecay.push_back(std::make_pair(ppmedium,ndecay));
 

  }

}

simpleAna::~simpleAna()
{}

void simpleAna::PrintNeutrinos()
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
      std::cout << "Warning in simpleAna::PrintNeutrinos(): Unkown pdg code: " << n << std::endl;
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

///____________________________________________________________________________

void simpleAna::PrintDecayLocations()
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
