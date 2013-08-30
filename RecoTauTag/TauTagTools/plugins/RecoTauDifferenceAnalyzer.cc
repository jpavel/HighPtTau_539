#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/TauReco/interface/PFTauFwd.h"
#include "DataFormats/TauReco/interface/PFTauDiscriminator.h"
#include "DataFormats/TrackReco/interface/Track.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"

#include <vector>
#include <string>
#include <sstream>

// histograms
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH1D.h"

typedef edm::View<reco::GenJet> GenJetView;

class RecoTauDifferenceAnalyzer : public edm::EDFilter {
  public:
  explicit RecoTauDifferenceAnalyzer(const edm::ParameterSet& pset);
    virtual ~RecoTauDifferenceAnalyzer() {}
    virtual bool filter(edm::Event& evt, const edm::EventSetup& es);
    virtual void endJob();
  private:
    edm::InputTag src1_;
    edm::InputTag src2_;
    edm::InputTag disc1_;
    edm::InputTag disc2_;
    edm::InputTag genSrc_;
    edm::InputTag genJetSrc_;
    edm::InputTag genTauSrc_;
    double maxDeltaR_;
    size_t eventsExamined_;
    size_t tausExamined_;
    size_t tausMatched_;
    size_t differences_;
    size_t passed1_;
    size_t passed2_;
    size_t allPassed1_;
    size_t allPassed2_;
    bool filter_;
    bool mcMatch_;
    bool useGenTaus_;
    double matchingDistance_;
  bool matchToJets_;
  bool verboseOutput_;
  bool verboseOutputMC_;
  bool background_;
  bool Zmumu_;
  bool onlyHadronic_;
  int requireDecayMode_;
  bool checkMother_;
  bool useOldDM_;
  edm::InputTag vertexTag_;
  edm::InputTag rhoProducer_;
  edm::InputTag discLoose_;
  edm::InputTag discMedium_;
  edm::InputTag discTight_;
  
  edm::InputTag discLoose_2_;
  edm::InputTag discMedium_2_;
  edm::InputTag discTight_2_;

  edm::InputTag discLoose_3_;
  edm::InputTag discMedium_3_;
  edm::InputTag discTight_3_;


    TProfile* h_eff_pt_1;
    TProfile* h_eff_pt_2;
    TProfile* h_eff_eta_1;
    TProfile* h_eff_eta_2;
    TProfile* h_eff_vx_1;
    TProfile* h_eff_vx_2;
    TProfile* h_eff_phi_1;
    TProfile* h_eff_phi_2;
  TProfile* h_eff_id_pt_1;
  TProfile* h_eff_id_pt_2;
  TProfile* h_eff_id_eta_1;
  TProfile* h_eff_id_eta_2;
  TProfile* h_eff_id_vx_1;
  TProfile* h_eff_id_vx_2;
  TProfile* h_eff_id_phi_1;
  TProfile* h_eff_id_phi_2;

  
  TProfile* h_eff_id_pt_loose;
  TProfile* h_eff_id_eta_loose;
  TProfile* h_eff_id_vx_loose;
  TProfile* h_eff_id_pt_medium;
  TProfile* h_eff_id_eta_medium;
  TProfile* h_eff_id_vx_medium;
  TProfile* h_eff_id_pt_tight;
  TProfile* h_eff_id_eta_tight;
  TProfile* h_eff_id_vx_tight;
  TProfile* h_eff_id_phi_loose;
  TProfile* h_eff_id_phi_medium;
  TProfile* h_eff_id_phi_tight;

  TProfile* h_eff_id_pt_loose_2;
  TProfile* h_eff_id_eta_loose_2;
  TProfile* h_eff_id_vx_loose_2;
  TProfile* h_eff_id_pt_medium_2;
  TProfile* h_eff_id_eta_medium_2;
  TProfile* h_eff_id_vx_medium_2;
  TProfile* h_eff_id_pt_tight_2;
  TProfile* h_eff_id_eta_tight_2;
  TProfile* h_eff_id_vx_tight_2;
  TProfile* h_eff_id_phi_loose_2;
  TProfile* h_eff_id_phi_medium_2;
  TProfile* h_eff_id_phi_tight_2;


  TProfile* h_eff_id_pt_loose_3;
  TProfile* h_eff_id_eta_loose_3;
  TProfile* h_eff_id_vx_loose_3;
  TProfile* h_eff_id_pt_medium_3;
  TProfile* h_eff_id_eta_medium_3;
  TProfile* h_eff_id_vx_medium_3;
  TProfile* h_eff_id_pt_tight_3;
  TProfile* h_eff_id_eta_tight_3;
  TProfile* h_eff_id_vx_tight_3;
  TProfile* h_eff_id_phi_loose_3;
  TProfile* h_eff_id_phi_medium_3;
  TProfile* h_eff_id_phi_tight_3;



    TH1D* h_nVx;
    TH1D* h_summary;
    std::vector<TH2D*> h_discComparison;
    std::vector<TH2D*> h_discComparisonRaw;
    std::vector<TH2D*> h_discComparisonRawN;
    std::vector<TH2D*> h_discComparisonRawCH;
  std::vector<TH1D*> h_discRaw;
  std::vector<TH1D*> h_discRawN;
  std::vector<TH1D*> h_discRawCH;
  std::vector<TH1D*> h_discMVA;
   std::vector<double> pt_cut;
    int nHist;
  TH2D* h_discComparisonRaw_sum;
  TH2D* h_discComparisonRawN_sum;
  TH2D* h_discComparisonRawCH_sum;
  TH1D* h_discRaw_sum;
  TH1D* h_discRawN_sum;
  TH1D* h_discRawCH_sum;
  TH1D* h_discMVA_sum;
  
  TH1D* h_discRaw_sum_pass;
  TH1D* h_discRawN_sum_pass;
  TH1D* h_discRawCH_sum_pass;


  TProfile* h_discRaw_pt;
  TProfile* h_discRawN_pt;
  TProfile* h_discRawCH_pt;
  TProfile* h_discMVA_pt;

  TProfile* h_discRaw_eta;
  TProfile* h_discRawN_eta;
  TProfile* h_discRawCH_eta;
  TProfile* h_discMVA_eta;

  TProfile* h_discRaw_rho;
  TProfile* h_discRawN_rho;
  TProfile* h_discRawCH_rho;
  TProfile* h_discMVA_rho;

  TProfile* h_discRaw_nVx;
  TProfile* h_discRawN_nVx;
  TProfile* h_discRawCH_nVx;
  TProfile* h_discMVA_nVx;

  TProfile2D* h_discRaw_pt_rho;
  TProfile2D* h_discRawN_pt_rho;
  TProfile2D* h_discRawCH_pt_rho;
  TProfile2D* h_discMVA_pt_rho;

  TProfile2D* h_discRaw_pt_nVx;
  TProfile2D* h_discRawN_pt_nVx;
  TProfile2D* h_discRawCH_pt_nVx;
  TProfile2D* h_discMVA_pt_nVx;
  
  TProfile2D* h_discRaw_eta_rho;
  TProfile2D* h_discRawN_eta_rho;
  TProfile2D* h_discRawCH_eta_rho;
  TProfile2D* h_discMVA_eta_rho;

  TProfile2D* h_discRaw_eta_nVx;
  TProfile2D* h_discRawN_eta_nVx;
  TProfile2D* h_discRawCH_eta_nVx;
  TProfile2D* h_discMVA_eta_nVx;



  std::vector<TProfile*> h_discRaw_rho_vec;
  std::vector<TProfile*> h_discRawN_rho_vec;
  std::vector<TProfile*> h_discRawCH_rho_vec;
  std::vector<TProfile*> h_discMVA_rho_vec;

  std::vector<TProfile*> h_discRaw_nVx_vec;
  std::vector<TProfile*> h_discRawN_nVx_vec;
  std::vector<TProfile*> h_discRawCH_nVx_vec;
  std::vector<TProfile*> h_discMVA_nVx_vec;

  //MVA histos
  std::vector<TH1D*>            h_niso;
  std::vector<std::vector<TH1D*> > h_rings;
  std::vector<std::vector<TH1D*> > h_shapes;
  TH1D* h_mva_rho;
  std::vector<TH1D*>  h_rings_sum;

  std::vector<TH1D*>            h_niso_mva_pass;
  std::vector<std::vector<TH1D*> > h_rings_mva_pass;
  std::vector<std::vector<TH1D*> > h_shapes_mva_pass;
  TH1D* h_mva_rho_mva_pass;

  std::vector<TH1D*>            h_niso_mva_fail;
  std::vector<std::vector<TH1D*> > h_rings_mva_fail;
  std::vector<std::vector<TH1D*> > h_shapes_mva_fail;
  TH1D* h_mva_rho_mva_fail;

  std::vector<std::vector<TH1D*> > h_rings_new;
  std::vector<std::vector<TH1D*> > h_rings_new_mva_pass;
  std::vector<std::vector<TH1D*> > h_rings_new_mva_fail;
  
  std::vector<std::vector<TH1D*> > h_rings_new_rel;
  std::vector<std::vector<TH1D*> > h_rings_new_rel_mva_pass;
  std::vector<std::vector<TH1D*> > h_rings_new_rel_mva_fail;

    TH1D* h_pt_1;
    TH1D* h_eta_1;
    TH1D* h_pt_2;
    TH1D* h_eta_2;
    TH1D* h_mc_pt;
  TH1D* h_mc_eta;
  TH1D* h_mc_pt_vis_had;
  TH1D* h_mc_pt_vis_el;
  TH1D* h_mc_pt_vis_mu;
  TH1D* h_mc_eta_vis_had;
  TH1D* h_mc_eta_vis_el;
  TH1D* h_mc_eta_vis_mu;
  TH1D* h_decayMode;
  TH1D* h_rho;
  TH2D* h_nVx_rho;
  TH1D* h_trkAvgDist;
  TH1D* h_trkAvgDist_pass;
  TH1D* h_trkAvgDist_n;
  TH1D* h_trkAvgDist_n_pass;
  TH1D* h_trkAvgDist_ch;
  TH1D* h_trkAvgDist_ch_pass;

};

RecoTauDifferenceAnalyzer::RecoTauDifferenceAnalyzer(
						     const edm::ParameterSet& pset) {
  src1_ = pset.getParameter<edm::InputTag>("src1");
  src2_ = pset.getParameter<edm::InputTag>("src2");
  disc1_ = pset.getParameter<edm::InputTag>("disc1");
  disc2_ = pset.getParameter<edm::InputTag>("disc2");
  eventsExamined_ = 0;
  tausExamined_ = 0;
  tausMatched_ = 0;
  differences_ = 0;
  passed1_ = 0;
  passed2_ = 0;
  allPassed2_ = 0;
  allPassed1_ = 0;
  filter_ = pset.exists("filter") ? pset.getParameter<bool>("filter") : false;
  mcMatch_ = pset.exists("mcMatch") ? pset.getParameter<bool>("mcMatch"): true;
  if( mcMatch_ && pset.exists("genSrc")) genSrc_= pset.getParameter<edm::InputTag>("genSrc");
  if( mcMatch_ && pset.exists("genJetSrc")) genJetSrc_= pset.getParameter<edm::InputTag>("genJetSrc");
  if(mcMatch_ && pset.exists("genTauSrc")) genTauSrc_ = pset.getParameter<edm::InputTag>("genTauSrc");
  matchingDistance_ = pset.exists("matchingDistance") ? pset.getParameter<double>("matchingDistance"): 0.1 ;
  matchToJets_ = pset.exists("matchToJets") ? pset.getParameter<bool>("matchToJets"): false;
  useGenTaus_ = pset.exists("useGenTaus") ? pset.getParameter<bool>("useGenTaus"): true;
  vertexTag_ = edm::InputTag("offlinePrimaryVertices", "");
  if (pset.exists("primaryVertexSrc")) vertexTag_ = pset.getParameter<edm::InputTag>("primaryVertexSrc");
  
  verboseOutput_= pset.exists("verboseOutput") ? pset.getParameter<bool>("verboseOutput"): true;
  verboseOutputMC_= pset.exists("verboseOutputMC") ? pset.getParameter<bool>("verboseOutputMC"): true;
  background_=pset.exists("background") ? pset.getParameter<bool>("background"): false;
  onlyHadronic_ = pset.exists("onlyHadronic") ? pset.getParameter<bool>("onlyHadronic"): true;
  rhoProducer_ = pset.getParameter<edm::InputTag>("rhoProducer");
  requireDecayMode_ = pset.exists("requireDecayMode") ? pset.getParameter<int>("requireDecayMode"): 0; // -1 No requirement; 0 = any DM; 1 = 1p; 2 = 1p+X; 3=3p
  checkMother_ = pset.exists("checkMother") ? pset.getParameter<bool>("checkMother"): 1;
  Zmumu_ = pset.exists("Zmumu") ? pset.getParameter<bool>("Zmumu"): false;
  useOldDM_ = pset.exists("useOldDM") ? pset.getParameter<bool>("useOldDM"): true;  
  discLoose_ = pset.exists("discLoose") ? pset.getParameter<edm::InputTag>("discLoose"): pset.getParameter<edm::InputTag>("disc1");
  discMedium_ = pset.exists("discMedium") ? pset.getParameter<edm::InputTag>("discMedium"): pset.getParameter<edm::InputTag>("disc1");
  discTight_ = pset.exists("discTight") ? pset.getParameter<edm::InputTag>("discTight"): pset.getParameter<edm::InputTag>("disc1");
  
  discLoose_2_ = pset.exists("discLoose_2") ? pset.getParameter<edm::InputTag>("discLoose_2"): pset.getParameter<edm::InputTag>("disc2");
  discMedium_2_ = pset.exists("discMedium_2") ? pset.getParameter<edm::InputTag>("discMedium_2"): pset.getParameter<edm::InputTag>("disc2");
  discTight_2_ = pset.exists("discTight_2") ? pset.getParameter<edm::InputTag>("discTight_2"): pset.getParameter<edm::InputTag>("disc2");

  discLoose_3_ = pset.exists("discLoose_3") ? pset.getParameter<edm::InputTag>("discLoose_3"): pset.getParameter<edm::InputTag>("disc1");
  discMedium_3_ = pset.exists("discMedium_3") ? pset.getParameter<edm::InputTag>("discMedium_3"): pset.getParameter<edm::InputTag>("disc1");
  discTight_3_ = pset.exists("discTight_3") ? pset.getParameter<edm::InputTag>("discTight_3"): pset.getParameter<edm::InputTag>("disc1");


  edm::Service<TFileService> fs;
  h_eff_pt_1 = fs->make<TProfile>("h_eff_pt_1" , "Efficiency w.r.t truth; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_pt_2 = fs->make<TProfile>("h_eff_pt_2" , "Efficiency w.r.t truth; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_eta_1 = fs->make<TProfile>("h_eff_eta_1" , "Efficiency w.r.t truth; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_eta_2 = fs->make<TProfile>("h_eff_eta_2" , "Efficiency w.r.t truth; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_vx_1 = fs->make<TProfile>("h_eff_vx_1" , "Efficiency w.r.t truth; Reconstructed vertices" , 40 , -0.5 , 39.5 );
  h_eff_vx_2 = fs->make<TProfile>("h_eff_vx_2" , "Efficiency w.r.t truth; Reconstructed vertices" , 40 , -0.5 , 39.5 );
  h_eff_phi_1 = fs->make<TProfile>("h_eff_phi_1" , "Efficiency w.r.t truth; true visible #phi" , 100 , -3.2 , 3.2 );
  h_eff_phi_2 = fs->make<TProfile>("h_eff_phi_2" , "Efficiency w.r.t truth; true visible #phi" , 100 , -3.2 , 3.2 );

  
  h_eff_id_pt_1 = fs->make<TProfile>("h_eff_id_pt_1" , "Efficiency w.r.t reco; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_id_pt_2 = fs->make<TProfile>("h_eff_id_pt_2" , "Efficiency w.r.t reco; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_id_eta_1 = fs->make<TProfile>("h_eff_id_eta_1" , "Efficiency w.r.t reco; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_id_eta_2 = fs->make<TProfile>("h_eff_id_eta_2" , "Efficiency w.r.t reco; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_id_vx_1 = fs->make<TProfile>("h_eff_id_vx_1" , "Efficiency w.r.t reco; Reconstructed vertices" , 40 , -0.5 , 39.5 );
  h_eff_id_vx_2 = fs->make<TProfile>("h_eff_id_vx_2" , "Efficiency w.r.t reco; Reconstructed vertices" , 40 , -0.5 , 39.5 );
  h_eff_id_phi_1 = fs->make<TProfile>("h_eff_id_phi_1" , "Efficiency w.r.t truth; true visible #phi" , 100 , -3.2 , 3.2 );
  h_eff_id_phi_2 = fs->make<TProfile>("h_eff_id_phi_2" , "Efficiency w.r.t truth; true visible #phi" , 100 , -3.2 , 3.2 );


  h_eff_id_pt_loose = fs->make<TProfile>("h_eff_id_pt_loose" , "Efficiency w.r.t reco; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_id_eta_loose = fs->make<TProfile>("h_eff_id_eta_loose" , "Efficiency w.r.t reco; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_id_vx_loose = fs->make<TProfile>("h_eff_id_vx_loose" , "Efficiency w.r.t reco; Reconstructed vertices" , 40 , -0.5 , 39.5 );

  h_eff_id_pt_medium = fs->make<TProfile>("h_eff_id_pt_medium" , "Efficiency w.r.t reco; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_id_eta_medium = fs->make<TProfile>("h_eff_id_eta_medium" , "Efficiency w.r.t reco; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_id_vx_medium = fs->make<TProfile>("h_eff_id_vx_medium" , "Efficiency w.r.t reco; Reconstructed vertices" , 40 , -0.5 , 39.5 );
  
  h_eff_id_pt_tight = fs->make<TProfile>("h_eff_id_pt_tight" , "Efficiency w.r.t reco; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_id_eta_tight = fs->make<TProfile>("h_eff_id_eta_tight" , "Efficiency w.r.t reco; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_id_vx_tight = fs->make<TProfile>("h_eff_id_vx_tight" , "Efficiency w.r.t reco; Reconstructed vertices" , 40 , -0.5 , 39.5 );
  
  h_eff_id_phi_loose = fs->make<TProfile>("h_eff_id_phi_loose" , "Efficiency w.r.t reco; true visible #phi" , 100 , -3.2 , 3.2 );
  h_eff_id_phi_medium = fs->make<TProfile>("h_eff_id_phi_medium" , "Efficiency w.r.t reco; true visible #phi" , 100 , -3.2 , 3.2 );
  h_eff_id_phi_tight = fs->make<TProfile>("h_eff_id_phi_tight" , "Efficiency w.r.t reco; true visible #phi" , 100 , -3.2 , 3.2 );
  
  h_eff_id_pt_loose_2 = fs->make<TProfile>("h_eff_id_pt_loose_2" , "Efficiency w.r.t reco; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_id_eta_loose_2 = fs->make<TProfile>("h_eff_id_eta_loose_2" , "Efficiency w.r.t reco; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_id_vx_loose_2 = fs->make<TProfile>("h_eff_id_vx_loose_2" , "Efficiency w.r.t reco; Reconstructed vertices" , 40 , -0.5 , 39.5 );

  h_eff_id_pt_medium_2 = fs->make<TProfile>("h_eff_id_pt_medium_2" , "Efficiency w.r.t reco; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_id_eta_medium_2 = fs->make<TProfile>("h_eff_id_eta_medium_2" , "Efficiency w.r.t reco; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_id_vx_medium_2 = fs->make<TProfile>("h_eff_id_vx_medium_2" , "Efficiency w.r.t reco; Reconstructed vertices" , 40 , -0.5 , 39.5 );

  h_eff_id_pt_tight_2 = fs->make<TProfile>("h_eff_id_pt_tight_2" , "Efficiency w.r.t reco; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_id_eta_tight_2 = fs->make<TProfile>("h_eff_id_eta_tight_2" , "Efficiency w.r.t reco; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_id_vx_tight_2 = fs->make<TProfile>("h_eff_id_vx_tight_2" , "Efficiency w.r.t reco; Reconstructed vertices" , 40 , -0.5 , 39.5 );
 
  h_eff_id_phi_loose_2 = fs->make<TProfile>("h_eff_id_phi_loose_2" , "Efficiency w.r.t reco; true visible #phi" , 100 , -3.2 , 3.2 );
  h_eff_id_phi_medium_2 = fs->make<TProfile>("h_eff_id_phi_medium_2" , "Efficiency w.r.t reco; true visible #phi" , 100 , -3.2 , 3.2 );
  h_eff_id_phi_tight_2 = fs->make<TProfile>("h_eff_id_phi_tight_2" , "Efficiency w.r.t reco; true visible #phi" , 100 , -3.2 , 3.2 );


  h_eff_id_pt_loose_3 = fs->make<TProfile>("h_eff_id_pt_loose_3" , "Efficiency w.r.t reco; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_id_eta_loose_3 = fs->make<TProfile>("h_eff_id_eta_loose_3" , "Efficiency w.r.t reco; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_id_vx_loose_3 = fs->make<TProfile>("h_eff_id_vx_loose_3" , "Efficiency w.r.t reco; Reconstructed vertices" , 40 , -0.5 , 39.5 );

  h_eff_id_pt_medium_3 = fs->make<TProfile>("h_eff_id_pt_medium_3" , "Efficiency w.r.t reco; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_id_eta_medium_3 = fs->make<TProfile>("h_eff_id_eta_medium_3" , "Efficiency w.r.t reco; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_id_vx_medium_3 = fs->make<TProfile>("h_eff_id_vx_medium_3" , "Efficiency w.r.t reco; Reconstructed vertices" , 40 , -0.5 , 39.5 );

  h_eff_id_pt_tight_3 = fs->make<TProfile>("h_eff_id_pt_tight_3" , "Efficiency w.r.t reco; true visible p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eff_id_eta_tight_3 = fs->make<TProfile>("h_eff_id_eta_tight_3" , "Efficiency w.r.t reco; true visible #eta" , 100 , -3.0 , 3.0 );
  h_eff_id_vx_tight_3 = fs->make<TProfile>("h_eff_id_vx_tight_3" , "Efficiency w.r.t reco; Reconstructed vertices" , 40 , -0.5 , 39.5 );

  h_eff_id_phi_loose_3 = fs->make<TProfile>("h_eff_id_phi_loose_3" , "Efficiency w.r.t reco; true visible #phi" , 100 , -3.2 , 3.2 );
  h_eff_id_phi_medium_3 = fs->make<TProfile>("h_eff_id_phi_medium_3" , "Efficiency w.r.t reco; true visible #phi" , 100 , -3.2 , 3.2 );
  h_eff_id_phi_tight_3 = fs->make<TProfile>("h_eff_id_phi_tight_3" , "Efficiency w.r.t reco; true visible #phi" , 100 , -3.2 , 3.2 );


  h_nVx = fs->make<TH1D>("h_nVx" , "Number of vertices; Reconstructed vertices" , 40 , -0.5 , 39.5 );
  h_rho = fs->make<TH1D>("h_rho" , "Rho; #rho" , 500 , 0.0 , 50.0 );
  h_nVx_rho = fs->make<TH2D>("h_nVx_rho" , "Number of vertices vs rho; Reconstructed vertices;#rho" , 40 , -0.5 , 39.5, 500, 0.0, 50.0 );
  h_summary = fs->make<TH1D>("h_summary","Summary of results",7,-0.5,6.5);

  h_summary->GetXaxis()->SetBinLabel(1,"Examined");
  h_summary->GetXaxis()->SetBinLabel(2,"Matched");
  h_summary->GetXaxis()->SetBinLabel(3,"Differences");
  h_summary->GetXaxis()->SetBinLabel(4,"Pass 1");
  h_summary->GetXaxis()->SetBinLabel(5,"Exclusive 1");
  h_summary->GetXaxis()->SetBinLabel(6,"Pass 2");
  h_summary->GetXaxis()->SetBinLabel(7,"Exclusive 2");


  pt_cut={20.0,25.0,30.0,40.0,60.0,120.0} ;
  nHist = pt_cut.size()-1;
  for(int iHist=0; iHist <nHist; iHist++)
    {
      std::stringstream ss,sss;
      ss << pt_cut[iHist];
      sss << pt_cut[iHist+1];
      std::string hist_name="h_discComparison_pt"+sss.str();
      std::string histRaw_name="h_discComparisonRaw_pt"+sss.str();
      std::string histRawCH_name="h_discComparisonRawCH_pt"+sss.str();
      std::string histRawN_name="h_discComparisonRawN_pt"+sss.str();
      std::string hist_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;disc1;disc2";
      std::string histRaw_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;MVA score;combined isolation [GeV]";
      std::string histRawCH_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;MVA score;charged isolation [GeV]";
      std::string histRawN_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;MVA score;neutral isolation [GeV]";

      std::string histSingle_name="h_discMVA_pt"+sss.str();
      std::string histSingleRaw_name="h_discRaw_pt"+sss.str();
      std::string histSingleRawCH_name="h_discRawCH_pt"+sss.str();
      std::string histSingleRawN_name="h_discRawN_pt"+sss.str();
      std::string histSingle_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;MVA score";
      std::string histSingleRaw_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;combined isolation [GeV]";
      std::string histSingleRawCH_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;charged isolation [GeV]";
      std::string histSingleRawN_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;neutral isolation [GeV]";

      std::string hist_rho_MVA_name="h_discMVA_rho_pt"+sss.str();
      std::string hist_rho_Raw_name="h_discRaw_rho_pt"+sss.str();
      std::string hist_rho_RawCH_name="h_discRawCH_rho_pt"+sss.str();
      std::string hist_rho_RawN_name="h_discRawN_rho_pt"+sss.str();
      std::string hist_rho_MVA_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;#rho;MVA score";
      std::string hist_rho_Raw_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;#rho;combined isolation [GeV]";
      std::string hist_rho_RawCH_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;#rho;charged isolation [GeV]";
      std::string hist_rho_RawN_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;#rho;neutral isolation [GeV]";

      std::string hist_nVx_MVA_name="h_discMVA_nVx_pt"+sss.str();
      std::string hist_nVx_Raw_name="h_discRaw_nVx_pt"+sss.str();
      std::string hist_nVx_RawCH_name="h_discRawCH_nVx_pt"+sss.str();
      std::string hist_nVx_RawN_name="h_discRawN_nVx_pt"+sss.str();
      std::string hist_nVx_MVA_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;reconstructed vertices;MVA score";
      std::string hist_nVx_Raw_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;reconstructed vertices;combined isolation [GeV]";
      std::string hist_nVx_RawCH_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;reconstructed vertices;charged isolation [GeV]";
      std::string hist_nVx_RawN_title=ss.str()+" GeV < Tau p_{T} < "+sss.str()+" GeV;reconstructed vertices;neutral isolation [GeV]";


      h_discComparison.push_back(fs->make<TH2D>(TString(hist_name),TString(hist_title),2,-0.5,1.5,2,-0.5,1.5));
      h_discComparison.at(iHist)->GetXaxis()->SetBinLabel(1,"rejected");
      h_discComparison.at(iHist)->GetXaxis()->SetBinLabel(2,"accepted");
      h_discComparison.at(iHist)->GetYaxis()->SetBinLabel(1,"rejected");
      h_discComparison.at(iHist)->GetYaxis()->SetBinLabel(2,"accepted");

      h_discComparisonRaw.push_back(fs->make<TH2D>(TString(histRaw_name),TString(histRaw_title),100,-1.0,1.0,500,0.0,50.0));
      h_discComparisonRawCH.push_back(fs->make<TH2D>(TString(histRawCH_name),TString(histRawCH_title),100,-1.0,1.0,500,0.0,50.0));
      h_discComparisonRawN.push_back(fs->make<TH2D>(TString(histRawN_name),TString(histRawN_title),100,-1.0,1.0,500,0.0,50.0));

      h_discMVA.push_back(fs->make<TH1D>(TString(histSingle_name),TString(histSingle_title),100,-1.0,1.0));
      h_discRaw.push_back(fs->make<TH1D>(TString(histSingleRaw_name),TString(histSingleRaw_title),500,0.0,50.0));
      h_discRawCH.push_back(fs->make<TH1D>(TString(histSingleRawCH_name),TString(histSingleRawCH_title),500,0.0,50.0));
      h_discRawN.push_back(fs->make<TH1D>(TString(histSingleRawN_name),TString(histSingleRawN_title),500,0.0,50.0));

      h_discMVA_rho_vec.push_back(fs->make<TProfile>(TString(hist_rho_MVA_name),TString(hist_rho_MVA_title),500,0.0,50.0));
      h_discRaw_rho_vec.push_back(fs->make<TProfile>(TString(hist_rho_Raw_name),TString(hist_rho_Raw_title),500,0.0,50.0));
      h_discRawCH_rho_vec.push_back(fs->make<TProfile>(TString(hist_rho_RawCH_name),TString(hist_rho_RawCH_title),500,0.0,50.0));
      h_discRawN_rho_vec.push_back(fs->make<TProfile>(TString(hist_rho_RawN_name),TString(hist_rho_RawN_title),500,0.0,50.0));

      h_discMVA_nVx_vec.push_back(fs->make<TProfile>(TString(hist_nVx_MVA_name),TString(hist_nVx_MVA_title),50,-0.5,49.5));
      h_discRaw_nVx_vec.push_back(fs->make<TProfile>(TString(hist_nVx_Raw_name),TString(hist_nVx_Raw_title),50,-0.5,49.5));
      h_discRawCH_nVx_vec.push_back(fs->make<TProfile>(TString(hist_nVx_RawCH_name),TString(hist_nVx_RawCH_title),50,-0.5,49.5));
      h_discRawN_nVx_vec.push_back(fs->make<TProfile>(TString(hist_nVx_RawN_name),TString(hist_nVx_RawN_title),50,-0.5,49.5));

    }
  h_discComparisonRaw_sum = fs->make<TH2D>("h_discComparisonRaw","All p_{T};MVA score;combined isolation [GeV]",100,-1.0,1.0,500,0.0,50.0);
  h_discComparisonRawN_sum = fs->make<TH2D>("h_discComparisonRawN","All p_{T};MVA score;neutral isolation [GeV]",100,-1.0,1.0,500,0.0,50.0);
  h_discComparisonRawCH_sum = fs->make<TH2D>("h_discComparisonRawCH","All p_{T};MVA score;charged isolation [GeV]",100,-1.0,1.0,500,0.0,50.0);
 
  h_discMVA_sum = fs->make<TH1D>("h_discMVA","All p_{T};MVA score",100,-1.0,1.0);
  h_discRaw_sum = fs->make<TH1D>("h_discRaw","All p_{T};combined isolation [GeV]",500,0.0,50.0);
  h_discRawN_sum = fs->make<TH1D>("h_discRawN","All p_{T};neutral isolation [GeV]",500,0.0,50.0);
  h_discRawCH_sum = fs->make<TH1D>("h_discRawCH","All p_{T};charged isolation [GeV]",500,0.0,50.0);

  h_discRaw_sum_pass = fs->make<TH1D>("h_discRaw_pass","All p_{T};combined isolation [GeV]",500,0.0,50.0);
  h_discRawN_sum_pass = fs->make<TH1D>("h_discRawN_pass","All p_{T};neutral isolation [GeV]",500,0.0,50.0);
  h_discRawCH_sum_pass = fs->make<TH1D>("h_discRawCH_pass","All p_{T};charged isolation [GeV]",500,0.0,50.0);


  h_discMVA_pt = fs->make<TProfile>("h_discMVA_pt","MVA;tau p_{T} [GeV];MVA score",100,0.0,100.0);
  h_discRaw_pt = fs->make<TProfile>("h_discRaw_pt","Combined;tau p_{T} [GeV];combined isolation [GeV]",100,0.0,100.0);
  h_discRawN_pt = fs->make<TProfile>("h_discRawN_pt","Neutral;tau p_{T} [GeV];neutral isolation [GeV]",100,0.0,100.0);
  h_discRawCH_pt = fs->make<TProfile>("h_discRawCH_pt","Charged;tau p_{T} [GeV];charged isolation [GeV]",100,0.0,100.0);

  h_discMVA_eta = fs->make<TProfile>("h_discMVA_eta","MVA;tau #eta;MVA score",100,-3.0,3.0);
  h_discRaw_eta = fs->make<TProfile>("h_discRaw_eta","Combined;tau #eta;combined isolation [GeV]",100,-3.0,3.0);
  h_discRawN_eta = fs->make<TProfile>("h_discRawN_eta","Neutral;tau #eta;neutral isolation [GeV]",100,-3.0,3.0);
  h_discRawCH_eta = fs->make<TProfile>("h_discRawCH_eta","Charged;tau #eta;charged isolation [GeV]",100,-3.0,3.0);

  h_discMVA_rho = fs->make<TProfile>("h_discMVA_rho","MVA;tau #rho;MVA score",500,0.0,50.0);
  h_discRaw_rho = fs->make<TProfile>("h_discRaw_rho","Combined;tau #rho;combined isolation [GeV]",500,0.0,50.0);
  h_discRawN_rho = fs->make<TProfile>("h_discRawN_rho","Neutral;tau #rho;neutral isolation [GeV]",500,0.0,50.0);
  h_discRawCH_rho = fs->make<TProfile>("h_discRawCH_rho","Charged;tau #rho;charged isolation [GeV]",500,0.0,50.0);
 
  h_discMVA_nVx = fs->make<TProfile>("h_discMVA_nVx","MVA;tau reconstructed vertices;MVA score",50,-0.5,49.5);
  h_discRaw_nVx = fs->make<TProfile>("h_discRaw_nVx","Combined;tau reconstructed vertices;combined isolation [GeV]",50,-0.5,49.5);
  h_discRawN_nVx = fs->make<TProfile>("h_discRawN_nVx","Neutral;tau reconstructed vertices;neutral isolation [GeV]",50,-0.5,49.5);
  h_discRawCH_nVx = fs->make<TProfile>("h_discRawCH_nVx","Charged;tau reconstructed vertices;charged isolation [GeV]",50,-0.5,49.5);

  h_discMVA_pt_rho = fs->make<TProfile2D>("h_discMVA_pt_rho","MVA;#tau p_{T} [GeV];tau #rho;MVA score",100,0.0,100.0,500,0.0,50.0);
  h_discRaw_pt_rho = fs->make<TProfile2D>("h_discRaw_pt_rho","Combined;#tau p_{T} [GeV];tau #rho;combined isolation [GeV]",100,0.0,100.0,500,0.0,50.0);
  h_discRawN_pt_rho = fs->make<TProfile2D>("h_discRawN_pt_rho","Neutral;#tau p_{T} [GeV];tau #rho;neutral isolation [GeV]",100,0.0,100.0,500,0.0,50.0);
  h_discRawCH_pt_rho = fs->make<TProfile2D>("h_discRawCH_pt_rho","Charged;#tau p_{T} [GeV];tau #rho;charged isolation [GeV]",100,0.0,100.0,500,0.0,50.0);
 
  h_discMVA_pt_nVx = fs->make<TProfile2D>("h_discMVA_pt_nVx","MVA;#tau p_{T} [GeV];tau reconstructed vertices;MVA score",100,0.0,100.0,50,-0.5,49.5);
  h_discRaw_pt_nVx = fs->make<TProfile2D>("h_discRaw_pt_nVx","Combined;#tau p_{T} [GeV];tau reconstructed vertices;combined isolation [GeV]",100,0.0,100.0,50,-0.5,49.5);
  h_discRawN_pt_nVx = fs->make<TProfile2D>("h_discRawN_pt_nVx","Neutral;#tau p_{T} [GeV];tau reconstructed vertices;neutral isolation [GeV]",100,0.0,100.0,50,-0.5,49.5);
  h_discRawCH_pt_nVx = fs->make<TProfile2D>("h_discRawCH_pt_nVx","Charged;#tau p_{T} [GeV];tau reconstructed vertices;charged isolation [GeV]",100,0.0,100.0,50,-0.5,49.5);

  h_discMVA_eta_rho = fs->make<TProfile2D>("h_discMVA_eta_rho","MVA;#tau #eta;tau #rho;MVA score",100,-3.0,3.0,500,0.0,50.0);
  h_discRaw_eta_rho = fs->make<TProfile2D>("h_discRaw_eta_rho","Combined;#tau #eta;tau #rho;combined isolation [GeV]",100,-3.0,3.0,500,0.0,50.0);
  h_discRawN_eta_rho = fs->make<TProfile2D>("h_discRawN_eta_rho","Neutral;#tau #eta;tau #rho;neutral isolation [GeV]",100,-3.0,3.0,500,0.0,50.0);
  h_discRawCH_eta_rho = fs->make<TProfile2D>("h_discRawCH_eta_rho","Charged;#tau #eta;tau #rho;charged isolation [GeV]",100,-3.0,3.0,500,0.0,50.0);
 
  h_discMVA_eta_nVx = fs->make<TProfile2D>("h_discMVA_eta_nVx","MVA;#tau #eta;tau reconstructed vertices;MVA score",100,-3.0,3.0,50,-0.5,49.5);
  h_discRaw_eta_nVx = fs->make<TProfile2D>("h_discRaw_eta_nVx","Combined;#tau #eta;tau reconstructed vertices;combined isolation [GeV]",100,-3.0,3.0,50,-0.5,49.5);
  h_discRawN_eta_nVx = fs->make<TProfile2D>("h_discRawN_eta_nVx","Neutral;#tau #eta;tau reconstructed vertices;neutral isolation [GeV]",100,-3.0,3.0,50,-0.5,49.5);
  h_discRawCH_eta_nVx = fs->make<TProfile2D>("h_discRawCH_eta_nVx","Charged;#tau #eta;tau reconstructed vertices;charged isolation [GeV]",100,-3.0,3.0,50,-0.5,49.5);


  h_pt_1 = fs->make<TH1D>("h_pt_1" , "Reconstructed p_{T}" , 1500 , 0.0 , 1500.0 );
  h_pt_2 = fs->make<TH1D>("h_pt_2" , "Reconstructed p_{T}" , 1500 , 0.0 , 1500.0 );
  h_eta_1 = fs->make<TH1D>("h_eta_1" , "Reconstructed #eta" , 100 , -3.0 , 3.0 );
  h_eta_2 = fs->make<TH1D>("h_eta_2" , "Reconstructed #eta" , 100 , -3.0 , 3.0 );

  h_mc_pt = fs->make<TH1D>("h_mc_pt", "True tau p_{T}; True #tau p_{T}[GeV]", 150, 0.0, 150.0);
  h_mc_pt_vis_had = fs->make<TH1D>("h_mc_pt_vis_had", "True tau visible p_{T}:hadronic modes; True #tau visible p_{T}[GeV]", 1500, 0.0, 1500.0);
  h_mc_pt_vis_el = fs->make<TH1D>("h_mc_pt_vis_el", "True tau visible p_{T}:electron; True #tau visible p_{T}[GeV]", 1500, 0.0, 1500.0);
  h_mc_pt_vis_mu = fs->make<TH1D>("h_mc_pt_vis_mu", "True tau visible p_{T}:muon; True #tau visible p_{T}[GeV]", 1500, 0.0, 1500.0);

  h_mc_eta = fs->make<TH1D>("h_mc_eta", "True tau #eta; True #tau #eta", 100, -3.0, 3.0);
  h_mc_eta_vis_had = fs->make<TH1D>("h_mc_eta_vis_had", "True tau visible #eta:hadronic modes; True #tau visible #eta", 100, -3.0, 3.0);
  h_mc_eta_vis_el = fs->make<TH1D>("h_mc_eta_vis_el", "True tau visible #eta:electron; True #tau visible #eta", 100, -3.0, 3.0);
  h_mc_eta_vis_mu = fs->make<TH1D>("h_mc_eta_vis_mu", "True tau visible #eta:muon; True #tau visible #eta", 100, -3.0, 3.0);


  h_decayMode = fs->make<TH1D>("h_decayMode","Tau Decay Modes", 4, -1.5, 2.5);

  h_decayMode->GetXaxis()->SetBinLabel(1,"Other");
  h_decayMode->GetXaxis()->SetBinLabel(2,"Hadronic");
  h_decayMode->GetXaxis()->SetBinLabel(3,"Electron");
  h_decayMode->GetXaxis()->SetBinLabel(4,"Muon");

  //MVA histograms
  
  const size_t pfTypes = 3;
  TString TypeNames[pfTypes]={"charged","gamma","other"};
  TString TypeNames_new[pfTypes]={"charged","gamma","sum"};

  TString ShapeNames[5]={"#Delta#eta","#Delta#phi","(#Delta#eta)^{2}","(#Delta#phi)^{2}","#Delta#eta#Delta#phi"};
  for(size_t iType = 0; iType < pfTypes; iType++)
    {
      
      h_niso.push_back(fs->make<TH1D>("h_niso_"+TypeNames[iType],"Number of "+TypeNames[iType]+" isolation candidates; "+TypeNames[iType]+" iso cands",50,-0.5,49.5));
      h_niso_mva_pass.push_back(fs->make<TH1D>("h_niso_mva_pass_"+TypeNames[iType],"Number of "+TypeNames[iType]+" isolation candidates passing MVA; "+TypeNames[iType]+" iso cands",50,-0.5,49.5));
      h_niso_mva_fail.push_back(fs->make<TH1D>("h_niso_mva_fail_"+TypeNames[iType],"Number of "+TypeNames[iType]+" isolation candidates failing MVA; "+TypeNames[iType]+" iso cands",50,-0.5,49.5));
      h_rings_sum.push_back(fs->make<TH1D>("h_rings_sum_"+TypeNames[iType],"Ptsum of all "+TypeNames[iType]+" isolation candidates",500,0.0,50.0));
      std::vector<TH1D*> h_rings_temp;
      std::vector<TH1D*> h_shapes_temp;

      std::vector<TH1D*> h_rings_temp_mva_pass;
      std::vector<TH1D*> h_shapes_temp_mva_pass;
      std::vector<TH1D*> h_rings_temp_mva_fail;     
      std::vector<TH1D*> h_shapes_temp_mva_fail;    

      std::vector<TH1D*> h_rings_new_temp;
      std::vector<TH1D*> h_rings_new_temp_mva_pass;
      std::vector<TH1D*> h_rings_new_temp_mva_fail;

      std::vector<TH1D*> h_rings_new_rel_temp;
      std::vector<TH1D*> h_rings_new_rel_temp_mva_pass;
      std::vector<TH1D*> h_rings_new_rel_temp_mva_fail;

      for(size_t iRing = 0; iRing < 5; iRing++)
	{
	  std::stringstream ss;
	  std::stringstream sss;
	  std::stringstream ssss;
	  ss << TypeNames[iType] << "_" << iRing;
	  sss << TypeNames[iType] << " iso candidates in ring no. " << iRing;
	  ssss << ShapeNames[iRing] <<" of " << TypeNames[iType] << " iso candidates; #Sigma (p_{T}"<<ShapeNames[iRing] << ")/#Sigma p_{T}";
	  std::string hist_name="h_rings_"+ss.str();
	  std::string hist_title="Ptsum of "+sss.str()+"; p_{T}[GeV]";
	  std::string hist_name2="h_shapes_"+ss.str();
	  std::string hist_title2="Average "+ssss.str();

	  std::string hist_name_mva_pass="h_rings_mva_pass_"+ss.str();
	  std::string hist_title_mva_pass="Ptsum of "+sss.str()+" passing MVA; p_{T}[GeV]";
	  std::string hist_name2_mva_pass="h_shapes_mva_pass_"+ss.str();
	  std::string hist_title2_mva_pass="Average "+ssss.str();

	  std::string hist_name_mva_fail="h_rings_mva_fail_"+ss.str();
	  std::string hist_title_mva_fail="Ptsum of "+sss.str()+" failing MVA; p_{T}[GeV]";
	  std::string hist_name2_mva_fail="h_shapes_mva_fail_"+ss.str();
	  std::string hist_title2_mva_fail="Average "+ssss.str();


	  h_rings_temp.push_back(fs->make<TH1D>(TString(hist_name),TString(hist_title),500,0.0,50.0));
	  h_shapes_temp.push_back(fs->make<TH1D>(TString(hist_name2),TString(hist_title2),100,0.0,1.0));
	  
	  h_rings_temp_mva_pass.push_back(fs->make<TH1D>(TString(hist_name_mva_pass),TString(hist_title_mva_pass),500,0.0,50.0));
          h_shapes_temp_mva_pass.push_back(fs->make<TH1D>(TString(hist_name2_mva_pass),TString(hist_title2_mva_pass),100,0.0,1.0));
	  
	  h_rings_temp_mva_fail.push_back(fs->make<TH1D>(TString(hist_name_mva_fail),TString(hist_title_mva_fail),500,0.0,50.0));
          h_shapes_temp_mva_fail.push_back(fs->make<TH1D>(TString(hist_name2_mva_fail),TString(hist_title2_mva_fail),100,0.0,1.0));
	}
      for(size_t iRing = 0; iRing < 3; iRing++)
	{
	  std::stringstream ss;
	  std::stringstream sss;
	  std::stringstream ssss;
          ss << TypeNames_new[iType] << "_" << iRing;
          sss << TypeNames_new[iType] << " iso candidates in ring no. " << iRing;
	  std::string hist_name="h_rings_new_"+ss.str();
	  std::string hist_title="Ptsum of "+sss.str()+"; p_{T}[GeV]";

	  std::string hist_name_mva_pass="h_rings_new_mva_pass_"+ss.str();
	  std::string hist_title_mva_pass="Ptsum of "+sss.str()+" passing MVA; p_{T}[GeV]";

	  std::string hist_name_mva_fail="h_rings_new_mva_fail_"+ss.str();
	  std::string hist_title_mva_fail="Ptsum of "+sss.str()+" failing MVA; p_{T}[GeV]";

          h_rings_new_temp.push_back(fs->make<TH1D>(TString(hist_name),TString(hist_title),500,0.0,50.0));
          h_rings_new_temp_mva_pass.push_back(fs->make<TH1D>(TString(hist_name_mva_pass),TString(hist_title_mva_pass),500,0.0,50.0));
          h_rings_new_temp_mva_fail.push_back(fs->make<TH1D>(TString(hist_name_mva_fail),TString(hist_title_mva_fail),500,0.0,50.0));

	}
      for(size_t iRing = 0; iRing < 3; iRing++)
        {
	  std::stringstream ss;
	  std::stringstream sss;
	  std::stringstream ssss;
          ss << TypeNames_new[iType] << "_" << iRing;
          sss << TypeNames_new[iType] << " iso candidates in ring no. " << iRing;
	  std::string hist_name="h_rings_new_rel_"+ss.str();
	  std::string hist_title="Ptsum of "+sss.str()+"; p_{T}^{(iso)}/#tau p_{T}";

	  std::string hist_name_mva_pass="h_rings_new_rel_mva_pass_"+ss.str();
	  std::string hist_title_mva_pass="Ptsum of "+sss.str()+" passing MVA; p_{T}^{(iso)}/#tau p_{T}";

	  std::string hist_name_mva_fail="h_rings_new_rel_mva_fail_"+ss.str();
	  std::string hist_title_mva_fail="Ptsum of "+sss.str()+" failing MVA; p_{T}^{(iso)}/#tau p_{T}";

          h_rings_new_rel_temp.push_back(fs->make<TH1D>(TString(hist_name),TString(hist_title),500,0.0,5.0));
          h_rings_new_rel_temp_mva_pass.push_back(fs->make<TH1D>(TString(hist_name_mva_pass),TString(hist_title_mva_pass),500,0.0,5.0));
          h_rings_new_rel_temp_mva_fail.push_back(fs->make<TH1D>(TString(hist_name_mva_fail),TString(hist_title_mva_fail),500,0.0,5.0));

        }
      h_rings.push_back(h_rings_temp);
      h_shapes.push_back(h_shapes_temp);
      h_rings_mva_pass.push_back(h_rings_temp_mva_pass);
      h_shapes_mva_pass.push_back(h_shapes_temp_mva_pass);
      h_rings_mva_fail.push_back(h_rings_temp_mva_fail);
      h_shapes_mva_fail.push_back(h_shapes_temp_mva_fail);
      
      h_rings_new.push_back(h_rings_new_temp);
      h_rings_new_mva_pass.push_back(h_rings_new_temp_mva_pass);
      h_rings_new_mva_fail.push_back(h_rings_new_temp_mva_fail);

      h_rings_new_rel.push_back(h_rings_new_rel_temp);
      h_rings_new_rel_mva_pass.push_back(h_rings_new_rel_temp_mva_pass);
      h_rings_new_rel_mva_fail.push_back(h_rings_new_rel_temp_mva_fail);
 }
  h_mva_rho = fs->make<TH1D>("h_mva_rho" , "Average p_{T} per unit area; #rho[GeV]" , 500 , 0.0 , 50.0 );
  h_mva_rho_mva_pass = fs->make<TH1D>("h_mva_rho_mva_pass" , "Average p_{T} per unit area; #rho[GeV]" , 500 , 0.0 , 50.0 );  
  h_mva_rho_mva_fail = fs->make<TH1D>("h_mva_rho_mva_fail" , "Average p_{T} per unit area; #rho[GeV]" , 500 , 0.0 , 50.0 );

  h_trkAvgDist=fs->make<TH1D>("h_trkAvgDist","Average constituent distance", 200, 0.0, 2.0);
  h_trkAvgDist_pass=fs->make<TH1D>("h_trkAvgDist_pass","Average constituent distance", 200, 0.0, 2.0);
  h_trkAvgDist_n=fs->make<TH1D>("h_trkAvgDist_n","Average constituent distance (neutrals)", 200, 0.0, 2.0);
  h_trkAvgDist_n_pass=fs->make<TH1D>("h_trkAvgDist_n_pass","Average constituent distance (neutrals)", 200, 0.0, 2.0);
  h_trkAvgDist_ch=fs->make<TH1D>("h_trkAvgDist_ch","Average constituent distance (charged)", 200, 0.0, 2.0);
  h_trkAvgDist_ch_pass=fs->make<TH1D>("h_trkAvgDist_ch_pass","Average constituent distance (charged)", 200, 0.0, 2.0);

  

}

namespace {
  reco::PFJetRef getJetRef(const reco::PFTau& tau) {
    if (tau.jetRef().isNonnull())
      return tau.jetRef();
    else if (tau.pfTauTagInfoRef()->pfjetRef().isNonnull())
      return tau.pfTauTagInfoRef()->pfjetRef();
    else throw cms::Exception("cant find jet ref");
  }
}

bool RecoTauDifferenceAnalyzer::filter(
    edm::Event& evt, const edm::EventSetup& es) {
  eventsExamined_++;
  unsigned int nMatched = 0;
  // Get taus
  edm::Handle<reco::PFTauCollection> taus1;
  evt.getByLabel(src1_, taus1);
  edm::Handle<reco::PFTauCollection> taus2;
  evt.getByLabel(src2_, taus2);
  edm::Handle<reco::GenParticleCollection> genParticles;
  if(mcMatch_) evt.getByLabel(genSrc_, genParticles);
  edm::Handle<reco::GenJetCollection> genJets;
  if (matchToJets_) evt.getByLabel(genJetSrc_, genJets);
  edm::Handle<std::vector<reco::GenJet> > genTaus;
  if(mcMatch_) evt.getByLabel(genTauSrc_, genTaus);
 // Get discriminators
  edm::Handle<reco::PFTauDiscriminator> disc1;
  evt.getByLabel(disc1_, disc1);
  edm::Handle<reco::PFTauDiscriminator> disc2;
  evt.getByLabel(disc2_, disc2);
  edm::Handle<reco::PFTauDiscriminator> discMVA;
  evt.getByLabel("hpsPFTauDiscriminationByIsolationMVAraw",discMVA);
  edm::Handle<reco::PFTauDiscriminator> discCH;
  evt.getByLabel("hpsPFTauDiscriminationByRawChargedIsolationDBSumPtCorr", discCH);
  edm::Handle<reco::PFTauDiscriminator> discN;
  evt.getByLabel("hpsPFTauDiscriminationByRawGammaIsolationDBSumPtCorr", discN);
  edm::Handle<reco::PFTauDiscriminator> discCOMB;
  evt.getByLabel("hpsPFTauDiscriminationByRawCombinedIsolationDBSumPtCorr", discCOMB);
  edm::Handle<reco::PFTauDiscriminator> discDM;
  evt.getByLabel("hpsPFTauDiscriminationByDecayModeFinding",discDM);
  edm::Handle<reco::PFTauDiscriminator> discAntiEl;
  evt.getByLabel("hpsPFTauDiscriminationByLooseElectronRejection",discAntiEl);
  edm::Handle<reco::PFTauDiscriminator> discAntiMu;
  evt.getByLabel("hpsPFTauDiscriminationByMediumMuonRejection",discAntiMu);
  edm::Handle<reco::PFTauDiscriminator> discLoose;
  evt.getByLabel(discLoose_, discLoose);
  edm::Handle<reco::PFTauDiscriminator> discMedium;
  evt.getByLabel(discMedium_, discMedium);
  edm::Handle<reco::PFTauDiscriminator> discTight;
  evt.getByLabel(discTight_, discTight);
  edm::Handle<reco::PFTauDiscriminator> discLoose_2;
  evt.getByLabel(discLoose_2_, discLoose_2);
  edm::Handle<reco::PFTauDiscriminator> discMedium_2;
  evt.getByLabel(discMedium_2_, discMedium_2);
  edm::Handle<reco::PFTauDiscriminator> discTight_2;
  evt.getByLabel(discTight_2_, discTight_2);
  edm::Handle<reco::PFTauDiscriminator> discLoose_3;
  evt.getByLabel(discLoose_3_, discLoose_3);
  edm::Handle<reco::PFTauDiscriminator> discMedium_3;
  evt.getByLabel(discMedium_3_, discMedium_3);
  edm::Handle<reco::PFTauDiscriminator> discTight_3;
  evt.getByLabel(discTight_3_, discTight_3);


  edm::Handle<reco::VertexCollection> verticesH_;
  evt.getByLabel(vertexTag_, verticesH_);
  int nVx = verticesH_->size();
  h_nVx->Fill(nVx);
  
  bool differenceFound = false;
  // Loop over first collection
  std::vector<int> goodCands;
  std::vector<bool> isHadronic;
  std::vector<double> pt_visible;
  std::vector<double> eta_visible;
  std::vector<double> phi_visible;
  std::vector<bool> isMatched;
  
  edm::Handle<double> hRho;
  evt.getByLabel(rhoProducer_, hRho);
  double rho_ = *hRho;
  h_rho->Fill(rho_);
  h_nVx_rho->Fill(nVx,rho_);

  if(mcMatch_ && !useGenTaus_){
  for(size_t i = 0; i < genParticles->size(); ++ i) {
    const reco::GenParticle & ParticleCand = (*genParticles)[i];
    if(verboseOutputMC_){
    std::cout<<i<<") Particle = "<<ParticleCand.pdgId()<<", Status = "<<ParticleCand.status()<<std::endl;
    if(ParticleCand.pdgId()==15 || ParticleCand.pdgId() == -15 || true){
    const reco::GenParticleRefVector& motherRefs = ParticleCand.motherRefVector();
    for(reco::GenParticleRefVector::const_iterator imr = motherRefs.begin(); imr!= motherRefs.end(); ++imr) {
      std::cout<<"   - Mother "<<(*imr).key()<<" "<<(*imr)->pdgId()<<std::endl;
    }
    }
    }
    if( abs(ParticleCand.pdgId())==15 && ParticleCand.status() == 2 && !Zmumu_)
      {
	if(verboseOutputMC_) std::cout << "  tau candidate!" << std::endl;
	if(background_ || ! checkMother_ ) goodCands.push_back(i);
	else{
	int mother = 0;
	bool final = false;
	int myKey = i;
	while(mother!=23 && !final)
	  {
	    const reco::GenParticleRefVector& mRefs = ((*genParticles)[myKey]).motherRefVector();
	    if(mRefs.size()==0){final=true; break;}
	    for(reco::GenParticleRefVector::const_iterator imr = mRefs.begin(); imr!= mRefs.end(); ++imr) {
	      if((*imr)->pdgId()==23){ mother = 23; break;}
	      if(abs(ParticleCand.pdgId())==15){  myKey =(*imr).key(); break;}
	    }
	  }
	if(mother==23) goodCands.push_back(i);
	}
      }
    if( abs(ParticleCand.pdgId())==13 && ParticleCand.status() == 1 && Zmumu_)
	  {
	    if(verboseOutputMC_) std::cout << "  mu candidate!" << std::endl;
	    if(background_ || ! checkMother_ ) goodCands.push_back(i);
	    else{
	      int mother = 0;
	      bool final = false;
	      int myKey = i;
	      while(mother!=23 && !final)
		{
		  const reco::GenParticleRefVector& mRefs = ((*genParticles)[myKey]).motherRefVector();
		  if(mRefs.size()==0){final=true; break;}
		  for(reco::GenParticleRefVector::const_iterator imr = mRefs.begin(); imr!= mRefs.end(); ++imr) {
		    if((*imr)->pdgId()==23){ mother = 23; break;}
		    if(abs(ParticleCand.pdgId())==13){  myKey =(*imr).key(); break;}
		  }
		}
	      if(mother==23) goodCands.push_back(i);
	    }
	  }
  }
  }
    if(verboseOutputMC_ && !Zmumu_) std::cout << "There were " << goodCands.size() << " good taus." << std::endl; 
    if(verboseOutputMC_ && Zmumu_) std::cout << "There were " << goodCands.size() << " good mus." << std::endl; 
 
if(!background_ && mcMatch_ && !useGenTaus_){
 //calculate visible pt
  for(size_t iMC = 0; iMC < goodCands.size(); ++iMC){
  //daughters                                                                                                                                                                                                                    
  const reco::GenParticleRefVector& mRefs = ((*genParticles)[goodCands.at(iMC)]).daughterRefVector();
  reco::Particle::LorentzVector invisibleP4( 0.0, 0.0, 0.0, 0.0 );
  unsigned int decayMode = -1; // 0 = hadronic, 1=electron, 2=muon                                                                                                                                                               
  unsigned int nNu = 0;
  for(reco::GenParticleRefVector::const_iterator imr = mRefs.begin(); imr!= mRefs.end(); ++imr) {
    if(abs((*imr)->pdgId())==11) decayMode = 1;
    if(abs((*imr)->pdgId())==13) decayMode = 2;
    if(abs((*imr)->pdgId())==16 || abs((*imr)->pdgId())==14 || abs((*imr)->pdgId())==12)
      {
	if(verboseOutputMC_) std::cout << "Found neutrino! " << (*imr)->pdgId() << " momentum is " << (*imr)->p4() << std::endl;
	invisibleP4+=(*imr)->p4();
	nNu++;
      }
  }
  if(verboseOutputMC_) std::cout << "Total invisible momentum is " << invisibleP4 << std::endl;
  if(nNu==1) decayMode = 0;
  h_decayMode->Fill(decayMode);
  h_mc_pt->Fill(((*genParticles)[goodCands.at(iMC)]).pt());
  h_mc_eta->Fill(((*genParticles)[goodCands.at(iMC)]).eta());

 reco::Particle::LorentzVector visibleP4 = ((*genParticles)[goodCands.at(iMC)]).p4()-invisibleP4;
  switch(decayMode){
   case 0:
     h_mc_pt_vis_had->Fill(visibleP4.pt());
     h_mc_eta_vis_had->Fill(visibleP4.eta());
     isHadronic.push_back(true);
     break;
   case 1:
     h_mc_pt_vis_el->Fill(visibleP4.pt());
     h_mc_eta_vis_el->Fill(visibleP4.eta());
     isHadronic.push_back(false);
     break;
   case 2: 
     h_mc_pt_vis_mu->Fill(visibleP4.pt());
     h_mc_eta_vis_mu->Fill(visibleP4.eta());
     isHadronic.push_back(false);
     break;
   default:
     isHadronic.push_back(false);
     break;
  }
  pt_visible.push_back(visibleP4.pt());
  eta_visible.push_back(visibleP4.eta());
  phi_visible.push_back(visibleP4.phi());
  isMatched.push_back(false);
  }
 }
 if(useGenTaus_){
   for(size_t i = 0; i < genTaus->size(); ++ i) {
     const reco::GenJet & TauCand = (*genTaus)[i];
     const std::vector <const reco::GenParticle*> mRefs = TauCand.getGenConstituents();
     unsigned int decayMode = 0; // 0 = hadronic, 1=electron, 2=muon 
     for(size_t igTauD =0; igTauD < mRefs.size(); igTauD++) {
       if(abs(mRefs[igTauD]->pdgId())==11) decayMode = 1;
       if(abs(mRefs[igTauD]->pdgId())==13) decayMode = 2;
     }
     h_decayMode->Fill(decayMode);
     h_mc_pt->Fill(((*genTaus)[i]).pt());
     h_mc_eta->Fill(((*genTaus)[i]).eta());

     reco::Particle::LorentzVector visibleP4 = ((*genTaus)[i]).p4();
     switch(decayMode){
     case 0:
       h_mc_pt_vis_had->Fill(visibleP4.pt());
       h_mc_eta_vis_had->Fill(visibleP4.eta());
       isHadronic.push_back(true);
       break;
     case 1:
       h_mc_pt_vis_el->Fill(visibleP4.pt());
       h_mc_eta_vis_el->Fill(visibleP4.eta());
       isHadronic.push_back(false);
       break;
     case 2: 
       h_mc_pt_vis_mu->Fill(visibleP4.pt());
       h_mc_eta_vis_mu->Fill(visibleP4.eta());
       isHadronic.push_back(false);
       break;
     default:
       isHadronic.push_back(false);
       break;
     }
     pt_visible.push_back(visibleP4.pt());
     eta_visible.push_back(visibleP4.eta());
     phi_visible.push_back(visibleP4.phi());
     isMatched.push_back(false);
   }
 }
  for (size_t iTau1 = 0; iTau1 < taus1->size(); ++iTau1) {
    tausExamined_++;
    reco::PFTauRef tau1(taus1, iTau1);
    // Find the best match in the other collection
    if(verboseOutputMC_ && mcMatch_) std::cout << "Finding true match!" << std::endl;
    bool matched = false;
    if(background_) matched = true;
    if(!background_ && !useGenTaus_){
      if(isHadronic.size()!=goodCands.size() || pt_visible.size()!=goodCands.size() || 
       isMatched.size()!=goodCands.size() || eta_visible.size()!=goodCands.size()){  edm::LogWarning("tauDifferenceAnalyzer") << "Wrong array size! "; break;}
    }
    double pt_vis = -999.;
    double eta_vis = -999.;
    double phi_vis = -999.;
    int matchIndex = -1;
    for(size_t iMC = 0; iMC < goodCands.size(); ++iMC){
      if(!Zmumu_ && !background_ && onlyHadronic_ && !isHadronic.at(iMC))
	{
	  if(verboseOutputMC_) std::cout << "Not hadronic tau!" << std::endl;
	    continue;
	}
      if(!background_ && isMatched.at(iMC)) continue;
        double dR_MC = deltaR(tau1->p4(),((*genParticles)[goodCands.at(iMC)]).p4());
      if(verboseOutputMC_) std::cout << " Tau distance is " << dR_MC << std::endl;
      if(dR_MC < matchingDistance_) 
	{ 
	  if(!background_){
	    matched = true;
	    pt_vis=pt_visible.at(iMC);
	    eta_vis = eta_visible.at(iMC);
	    phi_vis = phi_visible.at(iMC);
	  }
	  else matched = false;
	  matchIndex=iMC;
       	}
    }
    if(useGenTaus_)
      {
	for(size_t iMC = 0; iMC < genTaus->size(); ++ iMC) {
	  if(!Zmumu_ && !background_ && onlyHadronic_ && !isHadronic.at(iMC))
	    {
	      if(verboseOutputMC_) std::cout << "Not hadronic tau!" << std::endl;
	      continue;
	    }
	  if(!background_ && isMatched.at(iMC)) continue;
	  double dR_MC = deltaR(tau1->p4(),((*genTaus)[iMC]).p4());
	  if(verboseOutputMC_) std::cout << " Tau distance is " << dR_MC << std::endl;
	  if(dR_MC < matchingDistance_) 
	    { 
	      if(!background_){
		matched = true;
		pt_vis=pt_visible.at(iMC);
		eta_vis = eta_visible.at(iMC);
		phi_vis = phi_visible.at(iMC);
	      }
	      else matched = false;
	      matchIndex=iMC;
	    }
	}
      }
    if(!background_ && matched) isMatched.at(matchIndex)=true;

    if(matchToJets_){
      matched = false;
    for(size_t iJet=0; iJet < genJets->size(); ++iJet)
    {
	const reco::GenJet & JetCand = (*genJets)[iJet];
	double dR_jet = deltaR(tau1->p4(),JetCand.p4());
	if(dR_jet < matchingDistance_) matched = true;
    }
}


    if((mcMatch_ && !matched)||(matchToJets_&& !matched)) continue;
    tausMatched_++; nMatched++;
    reco::PFTauRef bestMatch;
    double bestDeltaR = -1;
    reco::PFJetRef jet1,jet2;
    for (size_t iTau2 = 0; iTau2 < taus2->size(); ++iTau2) {
      reco::PFTauRef tau2(taus2, iTau2);
      jet1 = getJetRef(*tau1);
      jet2 = getJetRef(*tau2);
      double deltaRVal = deltaR(jet2->p4(), jet1->p4());
      if (bestMatch.isNull() || deltaRVal < bestDeltaR) {
        bestMatch = tau2;
        bestDeltaR = deltaRVal;
      }
    }
    jet2 = getJetRef(*bestMatch);
    // See what's up with the discriminators
    bool result1 = ((*disc1)[tau1] > 0.5);
    bool result2 = ((*disc2)[bestMatch] > 0.5);
    double result2D = (*disc2)[tau1];
    bool resultLoose = ((*discLoose)[tau1] > 0.5);
    bool resultMedium = ((*discMedium)[tau1] > 0.5);
    bool resultTight = ((*discTight)[tau1] > 0.5);
    bool resultLoose_2 = ((*discLoose_2)[tau1] > 0.5);
    bool resultMedium_2 = ((*discMedium_2)[tau1] > 0.5);
    bool resultTight_2 = ((*discTight_2)[tau1] > 0.5);
    bool resultLoose_3 = ((*discLoose_3)[tau1] > 0.5);
    bool resultMedium_3 = ((*discMedium_3)[tau1] > 0.5);
    bool resultTight_3 = ((*discTight_3)[tau1] > 0.5);
    double resultMVA = (*discMVA)[tau1];
    double resultCH = (*discCH)[tau1];
    double resultN = (*discN)[tau1];
    double resultCOMB = (*disc2)[tau1];
    double resultDM = (*discDM)[tau1];
    double pt1 = tau1->pt();
    double pt2 = bestMatch->pt();
    double eta1 = tau1->eta();
    double eta2 = bestMatch->eta();
    double pt_mon, eta_mon, phi_mon;
    size_t nCharged,nPi0;
    bool resultAntiEl = ((*discAntiEl)[tau1]>0.5);
    bool resultAntiMu = ((*discAntiMu)[tau1]>0.5);
    nCharged = tau1->signalPFChargedHadrCands().size();
    nPi0 = tau1->signalPiZeroCandidates().size();


    // MVA observables

    std::vector<int>            niso(3);
    std::vector<std::vector<float> > rings(3, std::vector<float>(5));
    std::vector<std::vector<float> > shapes(3, std::vector<float>(5));
    std::vector<float>          isoptsum(3);
    std::vector<float>        trkAvgDist(3);
    
    // MVA observables getters (from reco::tau::cone::IsoRings PFRecoTauDiscriminationByMVAIsolation::computeIsoRings(const PFTauRef& pfTau) )

    for(uint i = 0; i < tau1->isolationPFCands().size(); i++)
      {
	const edm::Ptr<reco::PFCandidate> pf = tau1->isolationPFCands().at(i);
	
	// Angular distance between PF candidate and tau
	float deta = tau1->eta() - pf->eta();
	float dphi = reco::deltaPhi(tau1->phi(), pf->phi());
	float dr = reco::deltaR(tau1->eta(), tau1->phi(), pf->eta(), pf->phi());
	int pftype = 0;
	
	// Determine PF candidate type
	if(pf->charge() != 0)                           pftype = 0;
	else if(pf->particleId() == reco::PFCandidate::gamma) pftype = 1;
	else                                            pftype = 2;
	// Number of isolation candidates by type
	niso[pftype]++;
	
	// Isolation Rings
	if(dr < 0.1)      rings[pftype][0] += pf->pt();
	else if(dr < 0.2) rings[pftype][1] += pf->pt();
	else if(dr < 0.3) rings[pftype][2] += pf->pt();
	else if(dr < 0.4) rings[pftype][3] += pf->pt();
	else if(dr < 0.5) rings[pftype][4] += pf->pt();

	// Angle Shape Variables
	shapes[pftype][0] += pf->pt() * deta;
	shapes[pftype][1] += pf->pt() * dphi;
	shapes[pftype][2] += pf->pt() * deta*deta;
	shapes[pftype][3] += pf->pt() * dphi*dphi;
	shapes[pftype][4] += pf->pt() * deta*dphi;
	isoptsum[pftype]  += pf->pt();
	trkAvgDist[pftype]+= pf->pt()*dr;
// 	reco::TrackBaseRef trk; 
// 	if ((pf->trackRef()).isNonnull())
// 	  trk = reco::TrackBaseRef(pf->trackRef());
// 	else if ((pf->gsfTrackRef()).isNonnull()) {
// 	  trk = reco::TrackBaseRef(pf->gsfTrackRef());
// 	}
// 	else continue;
	  
// 	std::cout << trk->hitPattern().numberOfValidHits() << std::endl;

      }
    
    // Mean and variance of angle variables are weighted by pT
    for(uint i = 0; i < shapes.size(); i++)
      {
	for(uint j = 0; j < shapes[i].size(); j++)
	  {
	    shapes[i][j] = isoptsum[i] > 0 ? fabs(shapes[i][j]/isoptsum[i]) : 0;
	  }
      }

    trkAvgDist[0] = isoptsum[0] >0 ? trkAvgDist[0]/isoptsum[0] : -1;
    trkAvgDist[1] = isoptsum[1] >0 ? trkAvgDist[1]/isoptsum[1] : -1;
    trkAvgDist[2] = (isoptsum[0] + isoptsum[1]) >0 ? (trkAvgDist[0] + trkAvgDist[1])/(isoptsum[0]+isoptsum[1]) : -1;

    if(background_){
      pt_mon=jet1->pt();
      eta_mon = jet1->eta();
      phi_mon = jet1->phi();
    }else{
      pt_mon=pt_vis;
      eta_mon=eta_vis;
      phi_mon=phi_vis;
    }
    
    if(useOldDM_== true && nCharged ==2 ) continue;
    if(pt_mon < 20.0 || fabs(eta_mon)>2.3) continue;


    if(result1){
      h_eff_pt_1->Fill(pt_mon,1);
      h_eff_eta_1->Fill(eta_mon,1);
      h_eff_vx_1->Fill(nVx,1); 
      h_eff_id_pt_1->Fill(pt_mon,1);
      h_eff_id_eta_1->Fill(eta_mon,1);
      h_eff_id_vx_1->Fill(nVx,1);    
      h_eff_id_phi_1->Fill(phi_mon,1);
    }else{
      h_eff_id_pt_1->Fill(pt_mon,0);
      h_eff_id_eta_1->Fill(eta_mon,0);
      h_eff_id_vx_1->Fill(nVx,0);
      h_eff_pt_1->Fill(pt_mon,0);
      h_eff_eta_1->Fill(eta_mon,0);
      h_eff_vx_1->Fill(nVx,0);
      h_eff_id_phi_1->Fill(phi_mon,0);
    }

  
    if(requireDecayMode_>=0 && resultDM){
      if(requireDecayMode_ == 0 || (requireDecayMode_ == 1 && nCharged == 1 && nPi0 ==0) || (requireDecayMode_ == 2 && nCharged ==1 && nPi0 > 0) || (requireDecayMode_==3 && nCharged == 3)){
	

//     if(result1){
//       h_eff_pt_1->Fill(pt_mon,1);
//       h_eff_eta_1->Fill(eta_mon,1);
//       h_eff_vx_1->Fill(nVx,1); 
//       h_eff_id_pt_1->Fill(pt_mon,1);
//       h_eff_id_eta_1->Fill(eta_mon,1);
//       h_eff_id_vx_1->Fill(nVx,1);    
//       h_eff_id_phi_1->Fill(phi_mon,1);
//     }else{
//       h_eff_id_pt_1->Fill(pt_mon,0);
//       h_eff_id_eta_1->Fill(eta_mon,0);
//       h_eff_id_vx_1->Fill(nVx,0);
//       h_eff_pt_1->Fill(pt_mon,0);
//       h_eff_eta_1->Fill(eta_mon,0);
//       h_eff_vx_1->Fill(nVx,0);
//       h_eff_id_phi_1->Fill(phi_mon,0);
//     }

    if(resultLoose){
      h_eff_id_pt_loose->Fill(pt_mon,1);
      h_eff_id_eta_loose->Fill(eta_mon,1);
      h_eff_id_vx_loose->Fill(nVx,1);    
      h_eff_id_phi_loose->Fill(phi_mon,1);
    }else{
      h_eff_id_pt_loose->Fill(pt_mon,0);
      h_eff_id_eta_loose->Fill(eta_mon,0);
      h_eff_id_vx_loose->Fill(nVx,0);
      h_eff_id_phi_loose->Fill(phi_mon,0);
    }

    if(resultMedium ){
      h_eff_id_pt_medium->Fill(pt_mon,1);
      h_eff_id_eta_medium->Fill(eta_mon,1);
      h_eff_id_vx_medium->Fill(nVx,1);    
      h_eff_id_phi_medium->Fill(phi_mon,1);
    }else{
      h_eff_id_pt_medium->Fill(pt_mon,0);
      h_eff_id_eta_medium->Fill(eta_mon,0);
      h_eff_id_vx_medium->Fill(nVx,0);
      h_eff_id_phi_medium->Fill(phi_mon,0);
    }

    if(resultTight){
      h_eff_id_pt_tight->Fill(pt_mon,1);
      h_eff_id_eta_tight->Fill(eta_mon,1);
      h_eff_id_vx_tight->Fill(nVx,1);    
      h_eff_id_phi_tight->Fill(phi_mon,1);
    }else{
      h_eff_id_pt_tight->Fill(pt_mon,0);
      h_eff_id_eta_tight->Fill(eta_mon,0);
      h_eff_id_vx_tight->Fill(nVx,0);
      h_eff_id_phi_tight->Fill(phi_mon,0);
    }

    if(resultLoose_2){
      h_eff_id_pt_loose_2->Fill(pt_mon,1);
      h_eff_id_eta_loose_2->Fill(eta_mon,1);
      h_eff_id_vx_loose_2->Fill(nVx,1); 
      h_eff_id_phi_loose_2->Fill(phi_mon,1);
    }else{
      h_eff_id_pt_loose_2->Fill(pt_mon,0);
      h_eff_id_eta_loose_2->Fill(eta_mon,0);
      h_eff_id_vx_loose_2->Fill(nVx,0);
      h_eff_id_phi_loose_2->Fill(phi_mon,0);
    }

    if(resultMedium_2){
      h_eff_id_pt_medium_2->Fill(pt_mon,1);
      h_eff_id_eta_medium_2->Fill(eta_mon,1);
      h_eff_id_vx_medium_2->Fill(nVx,1);
      h_eff_id_phi_medium_2->Fill(phi_mon,1);
    }else{
      h_eff_id_pt_medium_2->Fill(pt_mon,0);
      h_eff_id_eta_medium_2->Fill(eta_mon,0);
      h_eff_id_vx_medium_2->Fill(nVx,0);
      h_eff_id_phi_medium_2->Fill(phi_mon,0);
    }

    if(resultTight_2){
      h_eff_id_pt_tight_2->Fill(pt_mon,1);
      h_eff_id_eta_tight_2->Fill(eta_mon,1);
      h_eff_id_vx_tight_2->Fill(nVx,1);    
      h_eff_id_phi_tight_2->Fill(phi_mon,1);
    }else{
      h_eff_id_pt_tight_2->Fill(pt_mon,0);
      h_eff_id_eta_tight_2->Fill(eta_mon,0);
      h_eff_id_vx_tight_2->Fill(nVx,0);
      h_eff_id_phi_tight_2->Fill(phi_mon,0);
    }

    if(resultLoose_3){
      h_eff_id_pt_loose_3->Fill(pt_mon,1);
      h_eff_id_eta_loose_3->Fill(eta_mon,1);
      h_eff_id_vx_loose_3->Fill(nVx,1);
      h_eff_id_phi_loose_3->Fill(phi_mon,1);
    }else{
      h_eff_id_pt_loose_3->Fill(pt_mon,0);
      h_eff_id_eta_loose_3->Fill(eta_mon,0);
      h_eff_id_vx_loose_3->Fill(nVx,0);
      h_eff_id_phi_loose_3->Fill(phi_mon,0);
    }

    if(resultMedium_3){
      h_eff_id_pt_medium_3->Fill(pt_mon,1);
      h_eff_id_eta_medium_3->Fill(eta_mon,1);
      h_eff_id_vx_medium_3->Fill(nVx,1);  
      h_eff_id_phi_medium_3->Fill(phi_mon,1);
    }else{
      h_eff_id_pt_medium_3->Fill(pt_mon,0);
      h_eff_id_eta_medium_3->Fill(eta_mon,0);
      h_eff_id_vx_medium_3->Fill(nVx,0);
      h_eff_id_phi_medium_3->Fill(phi_mon,0);
    }

    if(resultTight_3){
      h_eff_id_pt_tight_3->Fill(pt_mon,1);
      h_eff_id_eta_tight_3->Fill(eta_mon,1);
      h_eff_id_vx_tight_3->Fill(nVx,1);    
      h_eff_id_phi_tight_3->Fill(phi_mon,1);
    }else{
      h_eff_id_pt_tight_3->Fill(pt_mon,0);
      h_eff_id_eta_tight_3->Fill(eta_mon,0);
      h_eff_id_vx_tight_3->Fill(nVx,0);
      h_eff_id_phi_tight_3->Fill(phi_mon,0);
    }

    if(background_){
      pt_mon=jet2->pt();
      eta_mon=jet2->eta();
      phi_mon=jet2->eta();
    }
    if(pt_mon < 20.0 || fabs(eta_mon) > 2.3) continue;
      h_eff_pt_2->Fill(pt_mon,result2D);
      h_eff_eta_2->Fill(eta_mon,result2D);
      h_eff_vx_2->Fill(nVx,result2D);
      h_eff_id_pt_2->Fill(pt_mon,result2D);
      h_eff_id_eta_2->Fill(eta_mon,result2D);
      h_eff_id_vx_2->Fill(nVx,result2D);
      h_eff_id_phi_2->Fill(phi_mon,result2D);

    int ptRange = -1;

    if(pt1<pt_cut[nHist] && pt1 > pt_cut[0])
      {
	for(int iCut=1; iCut < nHist && ptRange < 0; iCut++)
	  {
	    if(pt1<pt_cut[iCut]) ptRange=iCut-1;
	  }
	if(ptRange < 0) ptRange=nHist-1;
      }
    h_pt_1->Fill(pt1);
    h_pt_2->Fill(pt2);
    h_eta_1->Fill(eta1);
    h_eta_2->Fill(eta2);
    
    h_discComparisonRaw_sum->Fill(resultMVA,resultCOMB);
    h_discComparisonRawN_sum->Fill(resultMVA,resultN);
    h_discComparisonRawCH_sum->Fill(resultMVA,resultCH);

    h_discMVA_sum->Fill(resultMVA);
    h_discRaw_sum->Fill(resultCOMB);
    h_discRawN_sum->Fill(resultN);
    h_discRawCH_sum->Fill(resultCH);

    h_discMVA_pt->Fill(pt1,resultMVA);
    h_discRaw_pt->Fill(pt1,resultCOMB);
    h_discRawN_pt->Fill(pt1,resultN);
    h_discRawCH_pt->Fill(pt1,resultCH);

    h_discMVA_eta->Fill(eta1,resultMVA);
    h_discRaw_eta->Fill(eta1,resultCOMB);
    h_discRawN_eta->Fill(eta1,resultN);
    h_discRawCH_eta->Fill(eta1,resultCH);

    h_discMVA_rho->Fill(rho_,resultMVA);
    h_discRaw_rho->Fill(rho_,resultCOMB);
    h_discRawN_rho->Fill(rho_,resultN);
    h_discRawCH_rho->Fill(rho_,resultCH);

    h_discMVA_nVx->Fill(nVx,resultMVA);
    h_discRaw_nVx->Fill(nVx,resultCOMB);
    h_discRawN_nVx->Fill(nVx,resultN);
    h_discRawCH_nVx->Fill(nVx,resultCH);

    h_discMVA_pt_rho->Fill(pt1,rho_,resultMVA);
    h_discRaw_pt_rho->Fill(pt1,rho_,resultCOMB);
    h_discRawN_pt_rho->Fill(pt1,rho_,resultN);
    h_discRawCH_pt_rho->Fill(pt1,rho_,resultCH);

    h_discMVA_pt_nVx->Fill(pt1,nVx,resultMVA);
    h_discRaw_pt_nVx->Fill(pt1,nVx,resultCOMB);
    h_discRawN_pt_nVx->Fill(pt1,nVx,resultN);
    h_discRawCH_pt_nVx->Fill(pt1,nVx,resultCH);

    h_discMVA_eta_rho->Fill(eta1,rho_,resultMVA);
    h_discRaw_eta_rho->Fill(eta1,rho_,resultCOMB);
    h_discRawN_eta_rho->Fill(eta1,rho_,resultN);
    h_discRawCH_eta_rho->Fill(eta1,rho_,resultCH);

    h_discMVA_eta_nVx->Fill(eta1,nVx,resultMVA);
    h_discRaw_eta_nVx->Fill(eta1,nVx,resultCOMB);
    h_discRawN_eta_nVx->Fill(eta1,nVx,resultN);
    h_discRawCH_eta_nVx->Fill(eta1,nVx,resultCH);

    h_trkAvgDist->Fill(trkAvgDist[2]);
    h_trkAvgDist_n->Fill(trkAvgDist[1]);
    h_trkAvgDist_ch->Fill(trkAvgDist[0]);

    if(ptRange >= 0)
      {
	if(result1)
	  {
	    if(result2) h_discComparison[ptRange]->Fill(1.0,1.0);
	    else h_discComparison[ptRange]->Fill(1.0,0.0);
	  }else{
	    if(result2) h_discComparison[ptRange]->Fill(0.0,1.0);
	    else h_discComparison[ptRange]->Fill(0.0,0.0);
	  }
	h_discComparisonRaw[ptRange]->Fill(resultMVA,resultCOMB);
	h_discComparisonRawN[ptRange]->Fill(resultMVA,resultN);
	h_discComparisonRawCH[ptRange]->Fill(resultMVA,resultCH);
	h_discMVA[ptRange]->Fill(resultMVA);
	h_discRaw[ptRange]->Fill(resultCOMB);
	h_discRawN[ptRange]->Fill(resultN);
	h_discRawCH[ptRange]->Fill(resultCH);
	h_discMVA_rho_vec[ptRange]->Fill(rho_,resultMVA);
        h_discRaw_rho_vec[ptRange]->Fill(rho_,resultCOMB);
        h_discRawN_rho_vec[ptRange]->Fill(rho_,resultN);
        h_discRawCH_rho_vec[ptRange]->Fill(rho_,resultCH);
	h_discMVA_nVx_vec[ptRange]->Fill(nVx,resultMVA);
        h_discRaw_nVx_vec[ptRange]->Fill(nVx,resultCOMB);
        h_discRawN_nVx_vec[ptRange]->Fill(nVx,resultN);
        h_discRawCH_nVx_vec[ptRange]->Fill(nVx,resultCH);

      }
    // MVA fillers
    if(pt1>20. && pt1 < 40. && fabs(eta1) < 2.3 && result1 && resultAntiEl && resultAntiMu)
      {
	
	h_trkAvgDist_pass->Fill(trkAvgDist[2]);
	h_trkAvgDist_n_pass->Fill(trkAvgDist[1]);
	h_trkAvgDist_ch_pass->Fill(trkAvgDist[0]);

	h_discRaw_sum_pass->Fill(resultCOMB);
	h_discRawN_sum_pass->Fill(resultN);
	h_discRawCH_sum_pass->Fill(resultCH);

	for(uint iType =0; iType < 3; iType++)
	  {
	    h_niso[iType]->Fill(niso[iType]);
	    double sum[3]={0.0,0.0,0.0};
	    for(uint iRing = 0; iRing < 5; iRing++)
	      {
		h_rings[iType][iRing]->Fill(rings[iType][iRing]);
		h_shapes[iType][iRing]->Fill(shapes[iType][iRing]);
		sum[iType]+=rings[iType][iRing];
	      }
	    h_rings_sum[iType]->Fill(sum[iType]);
	  }
	h_mva_rho->Fill(rho_);

	if(resultMVA>0.863)
	  {
	    for(uint iType =0; iType < 3; iType++)
	      {
		h_niso_mva_pass[iType]->Fill(niso[iType]);
		for(uint iRing = 0; iRing < 5; iRing++)
		  {
		    h_rings_mva_pass[iType][iRing]->Fill(rings[iType][iRing]);
		    h_shapes_mva_pass[iType][iRing]->Fill(shapes[iType][iRing]);
		  }
	      }
	    h_mva_rho_mva_pass->Fill(rho_);
	  }else{
	  for(uint iType =0; iType < 3; iType++)
	    {
	      h_niso_mva_fail[iType]->Fill(niso[iType]);
	      for(uint iRing = 0; iRing < 5; iRing++)
		{
		  h_rings_mva_fail[iType][iRing]->Fill(rings[iType][iRing]);
		  h_shapes_mva_fail[iType][iRing]->Fill(shapes[iType][iRing]);
		}
	    }
	  h_mva_rho_mva_fail->Fill(rho_);
	}

	for(uint iType =0; iType < 2; iType++)
          {
                h_rings_new[iType][0]->Fill(rings[iType][0]);
		h_rings_new[iType][1]->Fill(rings[iType][1]+rings[iType][2]);
		h_rings_new[iType][2]->Fill(rings[iType][3]+rings[iType][4]);
          }
	for(uint iRing=0; iRing < 3; iRing++)
	  {
	    h_rings_new[2][0]->Fill(rings[0][0]+rings[1][0]);
	    h_rings_new[2][1]->Fill(rings[0][1]+rings[0][2]+rings[1][1]+rings[1][2]);
	    h_rings_new[2][2]->Fill(rings[0][3]+rings[0][4]+rings[1][3]+rings[1][4]);
	  }
	
	if(resultMVA>0.863)
	  {
	    for(uint iType =0; iType < 2; iType++)
	      {
                h_rings_new_mva_pass[iType][0]->Fill(rings[iType][0]);
                h_rings_new_mva_pass[iType][1]->Fill(rings[iType][1]+rings[iType][2]);
                h_rings_new_mva_pass[iType][2]->Fill(rings[iType][3]+rings[iType][4]);
	      }
	    for(uint iRing=0; iRing < 3; iRing++)
	      {
		h_rings_new_mva_pass[2][0]->Fill(rings[0][0]+rings[1][0]);
		h_rings_new_mva_pass[2][1]->Fill(rings[0][1]+rings[0][2]+rings[1][1]+rings[1][2]);
		h_rings_new_mva_pass[2][2]->Fill(rings[0][3]+rings[0][4]+rings[1][3]+rings[1][4]);
	      }
	  }else{
	  for(uint iType =0; iType < 2; iType++)
	    {
	      h_rings_new_mva_fail[iType][0]->Fill(rings[iType][0]);
	      h_rings_new_mva_fail[iType][1]->Fill(rings[iType][1]+rings[iType][2]);
	      h_rings_new_mva_fail[iType][2]->Fill(rings[iType][3]+rings[iType][4]);
	    }
	  for(uint iRing=0; iRing < 3; iRing++)
	    {
	      h_rings_new_mva_fail[2][0]->Fill(rings[0][0]+rings[1][0]);
	      h_rings_new_mva_fail[2][1]->Fill(rings[0][1]+rings[0][2]+rings[1][1]+rings[1][2]);
	      h_rings_new_mva_fail[2][2]->Fill(rings[0][3]+rings[0][4]+rings[1][3]+rings[1][4]);
	    }
	}

	if(pt1>1e-8){
 	for(uint iType =0; iType < 2; iType++)
          {
	    h_rings_new_rel[iType][0]->Fill((rings[iType][0])/pt1);
	    h_rings_new_rel[iType][1]->Fill((rings[iType][1]+rings[iType][2])/pt1);
	    h_rings_new_rel[iType][2]->Fill((rings[iType][3]+rings[iType][4])/pt1);
          }
        for(uint iRing=0; iRing < 3; iRing++)
          {
            h_rings_new_rel[2][0]->Fill((rings[0][0]+rings[1][0])/pt1);
            h_rings_new_rel[2][1]->Fill((rings[0][1]+rings[0][2]+rings[1][1]+rings[1][2])/pt1);
            h_rings_new_rel[2][2]->Fill((rings[0][3]+rings[0][4]+rings[1][3]+rings[1][4])/pt1);
          }
        
        if(resultMVA>0.863)
          {
            for(uint iType =0; iType < 2; iType++)
              {
                h_rings_new_rel_mva_pass[iType][0]->Fill((rings[iType][0])/pt1);
                h_rings_new_rel_mva_pass[iType][1]->Fill((rings[iType][1]+rings[iType][2])/pt1);
                h_rings_new_rel_mva_pass[iType][2]->Fill((rings[iType][3]+rings[iType][4])/pt1);
              }
            for(uint iRing=0; iRing < 3; iRing++)
              {
                h_rings_new_rel_mva_pass[2][0]->Fill((rings[0][0]+rings[1][0])/pt1);
                h_rings_new_rel_mva_pass[2][1]->Fill((rings[0][1]+rings[0][2]+rings[1][1]+rings[1][2])/pt1);
                h_rings_new_rel_mva_pass[2][2]->Fill((rings[0][3]+rings[0][4]+rings[1][3]+rings[1][4])/pt1);
              }
          }else{
          for(uint iType =0; iType < 2; iType++)
            {
              h_rings_new_rel_mva_fail[iType][0]->Fill((rings[iType][0])/pt1);
              h_rings_new_rel_mva_fail[iType][1]->Fill((rings[iType][1]+rings[iType][2])/pt1);
              h_rings_new_rel_mva_fail[iType][2]->Fill((rings[iType][3]+rings[iType][4])/pt1);
            }
          for(uint iRing=0; iRing < 3; iRing++)
            {
              h_rings_new_rel_mva_fail[2][0]->Fill((rings[0][0]+rings[1][0])/pt1);
              h_rings_new_rel_mva_fail[2][1]->Fill((rings[0][1]+rings[0][2]+rings[1][1]+rings[1][2])/pt1);
              h_rings_new_rel_mva_fail[2][2]->Fill((rings[0][3]+rings[0][4]+rings[1][3]+rings[1][4])/pt1);
            }
	}
       }
  
      } 
    
      }
    }
    allPassed1_ += result1;
    allPassed2_ += result2;
    if (result1 ^ result2) {
      differenceFound = true;
      passed1_ += result1;
      passed2_ += result2;
      differences_++;
      if(verboseOutput_){
      std::cout << "********* RecoTau difference detected! *************"
          << std::endl;
      std::cout << " Tau1 InputTag: " << src1_ << " discriminator: " << disc1_ << " result: " << result1 << " mva: " << resultMVA << " rho: " << rho_ << " DM: " << resultDM
          << std::endl;
      std::cout << " Tau2 InputTag: " << src2_ << " discriminator: " << disc2_ << " result: " << result2 << " charged: " << resultCH << " neutral: " << resultN << " combined: " << resultCOMB
        << std::endl;
      std::cout << "---------       Tau 1                  -------------"
          << std::endl;
      std::cout << *tau1 << std::endl;
      tau1->dump(std::cout);
      if (tau1->leadPFChargedHadrCand().isNonnull() &&
          tau1->leadPFChargedHadrCand()->trackRef().isNonnull()) {
        std::cout << "lead track vz: "
          << tau1->leadPFChargedHadrCand()->trackRef()->vz()
          << std::endl;
      } else
        std::cout << "lead track ref is null!" << std::endl;

      std::cout << "---------       Tau 2                  -------------"
          << std::endl;
      std::cout << *bestMatch << std::endl;

      if (bestMatch->leadPFChargedHadrCand().isNonnull() &&
          bestMatch->leadPFChargedHadrCand()->trackRef().isNonnull()) {
        std::cout << "lead track vz: "
          << bestMatch->leadPFChargedHadrCand()->trackRef()->vz()
          << std::endl;

      } else
        std::cout << "lead track ref is null!" << std::endl;
      bestMatch->dump(std::cout);}
    }
  }
  if(nMatched < goodCands.size())
    {
      if(verboseOutput_) std::cout<< "Not all true taus matched!" << std::endl;
      for( size_t iMatch = 0; iMatch < isMatched.size(); ++iMatch)
	{
	  if(!isMatched.at(iMatch) && ((onlyHadronic_ && isHadronic.at(iMatch)) || !onlyHadronic_) ){
	    h_eff_pt_1->Fill(pt_visible.at(iMatch),0);
	    h_eff_pt_2->Fill(pt_visible.at(iMatch),0);
	    h_eff_eta_1->Fill(eta_visible.at(iMatch),0);
            h_eff_eta_2->Fill(eta_visible.at(iMatch),0);
	    h_eff_vx_1->Fill(nVx,0);
            h_eff_vx_2->Fill(nVx,0);
	  }
	}
    }
  return (filter_ ? differenceFound : true);
}

void RecoTauDifferenceAnalyzer::endJob() {
  if(verboseOutput_){
  std::cout <<  " RECO TAU DIFFERENCE SUMMARY: " << std::endl;
  std::cout <<  " Examined " << tausExamined_ << " taus in "
    << eventsExamined_ << " events." << std::endl;
  std::cout << " There were " << tausMatched_ << " taus matched to MC." << std::endl; 
  std::cout << " There were " << differences_ << " differences." << std::endl;
  std::cout << src1_ << "," << disc1_ << " had "
    << allPassed1_ << " total passes and "
    << passed1_ << " exclusive passes." << std::endl;
  std::cout << src2_ << "," << disc2_ << " had "
    << allPassed2_ << " total passes and "
    << passed2_ << " exclusive passes." << std::endl;
  }
  h_summary->SetBinContent(1,tausExamined_);
  h_summary->SetBinContent(2,tausMatched_);
  h_summary->SetBinContent(3,differences_);
  h_summary->SetBinContent(4,allPassed1_);
  h_summary->SetBinContent(5,passed1_);
  h_summary->SetBinContent(6,allPassed2_);
  h_summary->SetBinContent(7,passed2_);
}


#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(RecoTauDifferenceAnalyzer);
