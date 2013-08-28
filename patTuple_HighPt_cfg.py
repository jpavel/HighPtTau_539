import FWCore.ParameterSet.Config as cms

procName="highPtVal"

eMax = 100

sEvents=0


discName='DecayModeFinding'
discriminator="hpsPFTauDiscriminationBy"+discName

discName2='RawCombinedIsolationDBSumPtCorr3Hits'
discriminator2="hpsPFTauDiscriminationBy"+discName2


discNameLoose3='LooseIsolationMVA2'
discriminatorLoose3="hpsPFTauDiscriminationBy"+discNameLoose3

discNameLoose2='LooseCombinedIsolationDBSumPtCorr'
discriminatorLoose2="hpsPFTauDiscriminationBy"+discNameLoose2

discNameLoose='LooseCombinedIsolationDBSumPtCorr3Hits'
discriminatorLoose="hpsPFTauDiscriminationBy"+discNameLoose

#medium

discNameMedium3='MediumIsolationMVA2'
discriminatorMedium3="hpsPFTauDiscriminationBy"+discNameMedium3

discNameMedium2='MediumCombinedIsolationDBSumPtCorr'
discriminatorMedium2="hpsPFTauDiscriminationBy"+discNameMedium2

discNameMedium='MediumCombinedIsolationDBSumPtCorr3Hits'
discriminatorMedium="hpsPFTauDiscriminationBy"+discNameMedium

#tight

discNameTight3='TightIsolationMVA2'
discriminatorTight3="hpsPFTauDiscriminationBy"+discNameTight3

discNameTight2='TightCombinedIsolationDBSumPtCorr'
discriminatorTight2="hpsPFTauDiscriminationBy"+discNameTight2

discNameTight='TightCombinedIsolationDBSumPtCorr3Hits'
discriminatorTight="hpsPFTauDiscriminationBy"+discNameTight


decayMode = 0

DMname=""
if decayMode == 0:
    DMname="DMall"
elif decayMode == 1:
    DMname="DM1p"
elif decayMode == 2:
    DMname="DM1pX"
elif decayMode == 3:
    DMname="DM3p"

#process definition'
procName=procName+DMname
process = cms.Process(procName)

process.load("FWCore.MessageLogger.MessageLogger_cfi")
## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(eMax) )

#### included from standard pat template
## Geometry and Detector Conditions (needed for a few patTuple production steps)
#process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.autoCond import autoCond
process.GlobalTag.globaltag = cms.string( autoCond[ 'startup' ] )
process.load("Configuration.StandardSequences.MagneticField_cff")

## Standard PAT Configuration File
#process.load("PhysicsTools.PatAlgos.patSequences_cff")

## Output Module Configuration (expects a path 'p')
# from PhysicsTools.PatAlgos.patEventContent_cff import patEventContent
# process.out = cms.OutputModule("PoolOutputModule",
#                                fileName = cms.untracked.string('patTuple.root'),
#                                # save only events passing the full path
#                                SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
#                                # save PAT Layer 1 output; you need a '*' to
#                                # unpack the list of commands 'patEventContent'
#                                outputCommands = cms.untracked.vstring('drop *',
#                                                                       'keep *_tauGenJets*_*_*'
#                                                                       )
#                                )

# process.outpath = cms.EndPath(process.out)


process.source = cms.Source("PoolSource",
                            fileNames =  cms.untracked.vstring(
'file:/afs/cern.ch/work/j/jez/ntuples/tauID/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0002/2C1FBAB2-C1D4-E111-A89A-001E6739815B.root'
#'/store/relval/CMSSW_5_3_6-START53_V14/RelValProdTTbar/AODSIM/v2/00000/76ED0FA6-1E2A-E211-B8F1-001A92971B72.root'
#'file:/afs/cern.ch/work/j/jez/ntuples/tauID/mc/Summer12/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S7_START52_V9-v2/0001/CC6B5A91-2E98-E111-9093-003048D47724.root'
#    'file:/afs/cern.ch/work/j/jez/ntuples/tauID/mc/Summer12/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S7_START52_V9-v2/0003/F41D7301-BE9B-E111-9C03-002481E0D6A0.root'
    #    '/store/mc/Summer12/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S7_START52_V9-v1/0001/FE8F81B3-C494-E111-B50D-003048D476BC.root'
                             ),
                            skipEvents = cms.untracked.uint32(0)
                                                        )
process.load("RecoTauTag.Configuration.RecoPFTauTag_cff")

process.load("PhysicsTools.JetMCAlgos.TauGenJets_cfi")

process.tauDifferenceAnalyzer = cms.EDFilter("RecoTauDifferenceAnalyzer",
                                             src1 = cms.InputTag("hpsPFTauProducer","",procName),
                                             src2 = cms.InputTag("hpsPFTauProducer","",procName),
                                             disc1 = cms.InputTag(discriminator, "", procName),
                                             disc2 = cms.InputTag(discriminator2, "", procName),
                                             discLoose = cms.InputTag(discriminatorLoose, "", procName),
                                             discLoose_2 = cms.InputTag(discriminatorLoose2, "", procName),
                                             discLoose_3 = cms.InputTag(discriminatorLoose3, "", procName),
                                             discMedium = cms.InputTag(discriminatorMedium, "", procName),
                                             discMedium_2 = cms.InputTag(discriminatorMedium2, "", procName),
                                             discMedium_3 = cms.InputTag(discriminatorMedium3, "", procName),
                                             discTight = cms.InputTag(discriminatorTight, "", procName),
                                             discTight_2 = cms.InputTag(discriminatorTight2, "", procName),
                                             discTight_3 = cms.InputTag(discriminatorTight3, "", procName),
                                             genSrc = cms.InputTag("genParticles"),
                                             genTauSrc = cms.InputTag("tauGenJets"),
                                             mcMatch = cms.bool(True),
                                             primaryVertexSrc = cms.InputTag("offlinePrimaryVertices"),
                                             verboseOutput = cms.bool(False),
                                             verboseOutputMC = cms.bool(False),
                                             matchingDistance = cms.double(0.1),
                                             background = cms.bool(False),
                                             rhoProducer = cms.InputTag('kt6PFJetsForRhoComputationVoronoi','rho'),
                                             requireDecayMode = cms.int32(decayMode),
                                             checkMother = cms.bool(True),
                                             Zmumu=cms.bool(False)
                                             )

process.tauBGAnalyzer = process.tauDifferenceAnalyzer.clone ( matchingDistance = cms.double(0.5), background = cms.bool(False), genTauSrc=cms.InputTag("ak5GenJets"), onlyHadronic=cms.bool(False))

from PhysicsTools.PatAlgos.tools.helpers import cloneProcessingSnippet, massSearchReplaceParam
from RecoTauTag.Configuration.HPSPFTaus_cff import *





process.TFileService = cms.Service("TFileService", fileName = cms.string("output.root"))

## let it run
process.p = cms.Path(
    process.tauGenJets*
    process.PFTau *
    process.tauDifferenceAnalyzer
  )

## ------------------------------------------------------
#  In addition you usually want to change the following
#  parameters:
## ------------------------------------------------------
#
#   process.GlobalTag.globaltag =  ...    ##  (according to https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions)
#                                         ##
#   process.source.fileNames =  ...       ##  (e.g. 'file:AOD.root')
#                                         ##
# process.maxEvents.input = 10
#                                         ##
#   process.out.outputCommands = [ ... ]  ##  (e.g. taken from PhysicsTools/PatAlgos/python/patEventContent_cff.py)
#                                         ##
# process.out.fileName = 'patTuple_standard.root'
#                                         ##
#   process.options.wantSummary = False   ##  (to suppress the long output at the end of the job)

