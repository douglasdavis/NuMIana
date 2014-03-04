from ROOT import *

file_2013_numu    = TFile('2013/numu/hadded_out_file.root')
file_2013_numubar = TFile('2013/numubar/hadded_out_file.root')

flux_2013_numu    = file_2013_numu.Get('FluxTotal')
flux_2013_numubar = file_2013_numubar.Get('FluxTotal')

c = TCanvas()
c.SetLogy()
flux_2013_numu.Draw()
flux_2013_numubar.Draw('same')

raw_input('')
