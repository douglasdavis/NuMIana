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
    int         int_code;
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
}
