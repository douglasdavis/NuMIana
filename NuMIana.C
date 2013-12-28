#include "NuMIana.h"

NuMIana::NuMIana() {}

NuMIana::NuMIana(std::string file_name)
{
  fFile      = new TFile(file_name.c_str(),"READ");
  fEntryTree = (TTree*)fFile->Get("EntryTree");
  fNuMI_Tree = (TTree*)fFile->Get("NuMI_Tree");

  double wgt, vtxx, vtxy, vtxz;
  double dist, px, py, pz, E;
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

NuMIana::~NuMIana() {}
