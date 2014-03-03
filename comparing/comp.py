from ROOT import *

file2010 = TFile('fluxhists2010.root','read')
file2013 = TFile('fluxhists2013.root','read')

gROOT.ProcessLine('gSystem->Load("../src/looks.hh");')
gROOT.ProcessLine('looks();')

numu2010 = file2010.Get('numu_total')
nue2010  = file2010.Get('nue_total')

numu2013 = file2013.Get('numu_total')
nue2013  = file2013.Get('nue_total')

numu2010.SetLineColor(kRed-2)
nue2013.SetLineColor(kGray+2)

tl = TLegend(.7,.7,.9,.9)
tl.AddEntry(numu2013,'#nu_{#mu} 2013','l')
tl.AddEntry(numu2010,'#nu_{#mu} 2010','l')
tl.AddEntry(nue2013,'#nu_{e} 2013','l')
tl.AddEntry(nue2010,'#nu_{e} 2010','l')
tl.SetTextFont(22)
tl.SetFillColor(0)

c = TCanvas()
c.SetLogy()

numu2010.Draw()
numu2013.Draw('same')
nue2010.Draw('same')
nue2013.Draw('same')
tl.Draw('same')

raw_input('')
