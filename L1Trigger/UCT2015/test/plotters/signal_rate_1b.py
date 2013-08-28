### Compares the normalized rate (QCD) and signal distributions of the rlxStage1B taus

#####################
#  Author: Aaron Levine,  UW Madison

from sys import argv, stdout, stderr
import ROOT

canvas = ROOT.TCanvas("asdf", "adsf", 800, 800)

ntuple_file_signal = ROOT.TFile("../data/feb_26_stage1B/uct_tau_efficiency.root")
ntuple_file_rate = ROOT.TFile("../data/feb_26_stage1B/uct_rates_eic3.root")
signal_ntuple = ntuple_file_signal.Get("rlxTauEfficiencyStage1B/Ntuple")
rate_ntuple = ntuple_file_rate.Get("rlxTauUCTRateStage1B/Ntuple")
var = 'l1gRegionEtEM'
binning = [20,0,100]
draw_string = "%s >>htemp(%s)" % (var, ", ".join(str(x) for x in binning))
signal_ntuple.Draw(draw_string,"l1gPt > 20 && l1gMatch && recoPt > 20")
signal = ROOT.gDirectory.Get("htemp").Clone()
rate_ntuple.Draw(draw_string,"l1gPt > 20")
rate = ROOT.gDirectory.Get("htemp").Clone()
signal.Scale(1.0/signal.Integral())
rate.Scale(1.0/rate.Integral())
signal.SetLineColor(ROOT.EColor.kRed)
rate.SetLineColor(ROOT.EColor.kBlue)
legend=ROOT.TLegend(0.4,0.8,0.89,0.9,'','brNDC')
legend.AddEntry(signal,'signal')
legend.AddEntry(rate,'rate')
legend.SetFillColor(0)
legend.SetBorderSize(0)
binning = [20,0,100]
frame = ROOT.TH1F("frame","frame",*binning)
frame.SetMaximum(1.1)
frame.Draw('')
signal.Draw('Sames')
rate.Draw('Sames')
legend.Draw('Sames')
frame.GetXaxis().SetTitle(var)
canvas.SaveAs("signal_rate_cmp"+var+".png")
