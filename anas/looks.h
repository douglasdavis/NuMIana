#include "TGaxis.h"
#include "TH1D.h"
#include <iostream>

void fix_hist(std::vector<TH1D*> hvec)
{
  for ( auto j : hvec ) {
    j->GetXaxis()->CenterTitle();
    j->GetYaxis()->CenterTitle();
  }
}

void looks()
{
    TGaxis::SetMaxDigits(3);    
    TStyle *DStyle = new TStyle("DStyle","Doug Style");
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFrameFillColor(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetPadColor(0);
    gStyle->SetStatColor(0);
    gStyle->SetTitleFont(63,"");
    gStyle->SetLabelFont(63,"x");
    gStyle->SetTitleFont(63,"x");
    gStyle->SetLabelFont(63,"y");
    gStyle->SetTitleFont(63,"y");
    gStyle->SetLabelFont(63,"z");
    gStyle->SetTitleFont(63,"z");
    gStyle->SetLabelSize(20,"x");
    gStyle->SetTitleSize(22,"x");
    gStyle->SetLabelSize(20,"y");
    gStyle->SetTitleSize(22,"y");
    gStyle->SetLabelSize(18,"z");
    gStyle->SetTitleSize(18,"z");
    gStyle->SetTitleSize(0.050,"");
    gStyle->SetTitleAlign(23);
    gStyle->SetTitleX(0.5);
    gStyle->SetTitleBorderSize(0);
    gStyle->SetTitleFillColor(0);
    gStyle->SetTitleStyle(0);
    gStyle->SetOptStat("emr");
    gStyle->SetStatBorderSize(0);
    gStyle->SetStatFont(63);
    gStyle->SetStatFontSize(16);
    gStyle->SetStatY(0.9);
    gStyle->SetStatX(0.86);
    gStyle->SetHistLineColor(kBlue+2);
    gStyle->SetLegendBorderSize(0);
    gStyle->SetLegendFillColor(0);
    gStyle->SetFuncWidth(2);
    gStyle->SetFuncColor(2);
    gStyle->SetPadTopMargin(0.08);
    gStyle->SetPadBottomMargin(0.142);
    gStyle->SetPadLeftMargin(0.12);
    gStyle->SetPadRightMargin(0.12);  
    gStyle->SetCanvasDefX(400);
    gStyle->SetCanvasDefY(20);
    gStyle->SetCanvasDefH(420);
    gStyle->SetCanvasDefW(610);
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFrameLineWidth(2);
    gStyle->SetHistLineWidth(2);
    gStyle->SetTitleOffset(1.07,"y");
    gStyle->SetTitleOffset(1.14,"x");
}
