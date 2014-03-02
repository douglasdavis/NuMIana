///////////////////////////////////////////////////////////////////////////////
///  \brief   Methods of the base Ana class (to analyze LArNuMI events/flux)
///  \author  douglasdavis@utexas.edu
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <fstream>
#include "Ana.hh"

namespace numi {

  Ana::Ana()
  {
    Int_t       int_code;
    std::string str_code;
  
    std::ifstream ppmedium_config;
    ppmedium_config.open("config/ppmediumCodes.dat");
    while ( ppmedium_config >> int_code >> str_code )
      fppmediumCodeMap[int_code] = str_code;
    ppmedium_config.close();
  
    std::ifstream ndecay_config;
    ndecay_config.open("config/ndecayCodes.dat");
    while ( ndecay_config >> int_code >> str_code )
      fndecayCodeMap[int_code] = str_code;
    ndecay_config.close();
  }

  /// ____________________________________________________________________________________

  Ana::~Ana() {}

  /// ____________________________________________________________________________________

  void Ana::SetupTitle(const std::string& title_)
  {
    PlotTitle = new TPaveText(0.6485149,0.9311224,0.8778878,0.9821429,"brNDC");
    PlotTitle->SetTextSize(0.048);
    PlotTitle->SetTextFont(102);
    PlotTitle->SetFillColor(0);
    PlotTitle->SetBorderSize(0);
    PlotTitle->AddText(title_.c_str());
  }

  void Ana::FillHist_FluxNtuple(TH1D *hist,
				const std::string& var_name)
  {
    Double_t jj;
    fFluxNtuple->SetBranchAddress(var_name.c_str(),&jj);
    for ( auto i = 0; i < fFluxNtuple->GetEntries(); ++i ) {
      fFluxNtuple->GetEntry(i);
      hist->Fill(jj);
    }
  }

  void Ana::FillVec_FluxNtuple(std::vector<Double_t>& vec,
			       const std::string& var_name)
  {
    Double_t jj;
    fFluxNtuple->SetBranchAddress(var_name.c_str(),&jj);
    for ( auto i = 0; i < fFluxNtuple->GetEntries(); ++i ) {
      fFluxNtuple->GetEntry(i);
      vec.push_back(jj);
    }
  }

  void Ana::FillHist_SimulationNtuple(TH1D *hist,
				      const std::string& var_name)
  {
    Double_t jj;
    fSimulationNtuple->SetBranchAddress(var_name.c_str(),&jj);
    for ( auto i = 0; i < fSimulationNtuple->GetEntries(); ++i ) {
      fSimulationNtuple->GetEntry(i);
      hist->Fill(jj);
    }
  }

  void Ana::FillVec_SimulationNtuple(std::vector<Double_t>& vec,
				     const std::string& var_name)
  {
    Double_t jj;
    fSimulationNtuple->SetBranchAddress(var_name.c_str(),&jj);
    for ( auto i = 0; i < fSimulationNtuple->GetEntries(); ++i ) {
      fSimulationNtuple->GetEntry(i);
      vec.push_back(jj);
    }
  }

  void Ana::FillHist_EntryTree(TH1D *hist,
			       const std::string& var_name)
  {
    Double_t jj;
    fEntryTree->SetBranchAddress(var_name.c_str(),&jj);
    for ( auto i = 0; i < fEntryTree->GetEntries(); ++i ) {
      fEntryTree->GetEntry(i);
      hist->Fill(jj);
    }
  }

  void Ana::FillVec_EntryTree(std::vector<Double_t>& vec,
			      const std::string& var_name)
  {
    Double_t jj;
    fEntryTree->SetBranchAddress(var_name.c_str(),&jj);
    for ( auto i = 0; i < fEntryTree->GetEntries(); ++i ) {
      fEntryTree->GetEntry(i);
      vec.push_back(jj);
    }  
  }

  void Ana::FillHist_NuMI_Tree(TH1D *hist,
			       const std::string& var_name)
  {
    Double_t jj;
    fNuMI_Tree->SetBranchAddress(var_name.c_str(),&jj);
    for ( auto i = 0; i < fNuMI_Tree->GetEntries(); ++i ) {
      fNuMI_Tree->GetEntry(i);
      hist->Fill(jj);
    }
  }

  void Ana::FillVec_NuMI_Tree(std::vector<Double_t>& vec,
			      const std::string& var_name)
  {
    Double_t jj;
    fNuMI_Tree->SetBranchAddress(var_name.c_str(),&jj);
    for ( auto i = 0; i < fNuMI_Tree->GetEntries(); ++i ) {
      fNuMI_Tree->GetEntry(i);
      vec.push_back(jj);
    }
  }
}
