from rootpy.io import root_open as ropen
from rootpy.plotting import Canvas, Hist, Efficiency, Legend
import rootpy

rootpy.log.basic_config_colorized()

eff_file = ropen("../data/LSB50/uct_tau_efficiency.root")
eff_file_low = ropen("../data/LSB50/uct_mc_efficiency_pu35.root")
eff_file_high = ropen("../data/LSB50/uct_mc_efficiency_pu50.root")


eff_ntuple = eff_file_high["rlxTauEfficiency/Ntuple"]

#binning = (25, 20, 70)
binning = (range(20, 32, 2) + range(32, 45, 1) + range(45, 55, 2)
           + range(55, 70, 5),)


l1_pass_vs_pu = Hist(*binning)
uct_pass_vs_pu = Hist(*binning)
uct_iso_pass_vs_pu = Hist(*binning)
total_vs_pu = Hist(*binning)

eff_ntuple.Draw("nPVs", "recoPt > 40", hist=total_vs_pu)
eff_ntuple.Draw(
    "nPVs",
    "recoPt > 40 && l1gMatch && max(l1gPt, l1gRegionEt) > 25",
    hist=uct_pass_vs_pu)
eff_ntuple.Draw(
    "nPVs",
    "recoPt > 40 && l1gMatch && max(l1gPt, l1gRegionEt) > 25"
    " && l1gJetPt/max(l1gPt, l1gRegionEt) - 1 < 0.5",
    hist=uct_iso_pass_vs_pu)
eff_ntuple.Draw(
    "nPVs",
    "recoPt > 40 && l1Match && l1Pt > 44",
    hist=l1_pass_vs_pu)

canvas = Canvas(800, 800)

l1_efficiency = Efficiency(l1_pass_vs_pu, total_vs_pu).decorate(
    linecolor='red', linewidth=2, markerstyle=20, markercolor='red')

uct_efficiency = Efficiency(uct_pass_vs_pu, total_vs_pu).decorate(
    linecolor='blue', linewidth=2, markerstyle=20, markercolor='blue')

uct_iso_efficiency = Efficiency(uct_iso_pass_vs_pu, total_vs_pu).decorate(
    linecolor='green', linewidth=2, markerstyle=20, markercolor='green')

frame = Hist(*binning)

frame.SetMaximum(1)
frame.SetMinimum(0)
frame.axis().SetTitle("Number of vertices")
frame.axis(2).SetTitle("Efficiency (w.r.t. reco. p_{T}>40 GeV)")

canvas.SetLogy(False)
canvas.SetLeftMargin(0.2)

frame.Draw()
l1_efficiency.Draw('pe same')
uct_efficiency.Draw('pe same')
uct_iso_efficiency.Draw('pe same')

legend = Legend(3, topmargin=0.25, leftmargin=0.25)
legend.AddEntry(l1_efficiency, 'lp', 'Current Tau44')
legend.AddEntry(uct_efficiency, 'lp',
                'Upgrade RlxTau25 Rel. Rate %0.2f' % (9488./9355))
legend.AddEntry(uct_iso_efficiency, 'lp',
                'Upgrade IsoTau25 Rel. Rate %0.2f' %(6224./9355))
legend.SetBorderSize(0)
legend.SetTextSize(0.03)

legend.Draw()

canvas.SaveAs("eff_vs_pu.png")
canvas.SaveAs("eff_vs_pu.pdf")

frame.Draw()
l1_efficiency.Draw('pe same')
uct_efficiency.Draw('pe same')

legend = Legend(2, topmargin=0.25, leftmargin=0.25)
legend.AddEntry(l1_efficiency, 'lp', 'Current Tau44')
legend.AddEntry(uct_efficiency, 'lp',
                'Upgrade RlxTau25 Rel. Rate %0.2f' %(9488./9355))
legend.SetBorderSize(0)
legend.SetTextSize(0.04)

legend.Draw()

canvas.SaveAs("eff_vs_pu_noiso.png")
canvas.SaveAs("eff_vs_pu_noiso.pdf")
