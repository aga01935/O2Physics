// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.
/*
Code will evantually developed into UPC forward dimuons.
I ran this code using following:
o2-analysis-event-selection|o2-analysis-timestamp| o2-analysis-upc-forward --aod-file <path to ao2d.txt> [--isPbPb] -b
for now AO2D.root I am using is
alien:///alice/data/2015/LHC15o/000246392/pass5_lowIR/PWGZZ/Run3_Conversion/148_20210304-0829_child_1/AOD/001/AO2D.root
*/
#include "Framework/runDataProcessing.h"
#include "Framework/AnalysisTask.h"
#include "Framework/AnalysisDataModel.h"
#include "Common/DataModel/EventSelection.h"
#include "iostream"
#include "Common/DataModel/EventSelection.h"
#include <TH1D.h>
#include <TH2D.h>
#include <TString.h>
#include "TLorentzVector.h"
//#include "Common/CCDB/TriggerAliases.h"
using namespace std;
using namespace o2;
using namespace o2::framework;
using namespace o2::framework::expressions;
#define mmuon 0.1057 // mass of muon

// some table definition for skimmed Data
namespace o2::aod
{

namespace udfwdtrack
{
DECLARE_SOA_COLUMN(Pt, pt, float);
DECLARE_SOA_COLUMN(Eta, eta, float);
DECLARE_SOA_COLUMN(Phi, phi, float);
DECLARE_SOA_COLUMN(Sign, sign, int);
//DECLARE_SOA_TABLE(nFwdTrack,nFwdTrack,int);

} // namespace udfwdtrack
DECLARE_SOA_TABLE(UDFWDTracks, "AOD", "UDFWDTRACK", o2::soa::Index<>,
                  udfwdtrack::Pt, udfwdtrack::Eta, udfwdtrack::Phi,
                  udfwdtrack::Sign);//,udfwdtrack::nFwdTrack);
using UDFWDTrack = UDFWDTracks::iterator;

} // namespace o2::aod

struct UPCForwardRun3 {
  // defining histograms using histogram registry
  HistogramRegistry registry{"registry", {}, OutputObjHandlingPolicy::AnalysisObject};
  Produces<aod::UDFWDTracks> fwdTracks;



  void init(o2::framework::InitContext&)
  {

    auto hSelectionCounter = registry.add<TH1>("hSelectionCounter", "hSelectionCounter;;NEvents", HistType::kTH1I, {{30, 0., 30.}});

  registry.add("hMass", "Mass of Mother;#it{m_{#mu#mu}}, GeV/c^{2};", kTH1D, {{500, 0., 10.}});
  registry.add("hPt", "Pt of Mother;#it{p_{t}}, GeV/c;", kTH1D, {{500, 0., 5.}});
  //registry.add("hPtsingle_muons", "Pt of Daughters;#it{p_{t}}, GeV/c;", kTH1D, {{500, 0., 5.}});
  registry.add("hPx", "Px;#it{P_{x}}, GeV/c;", kTH1D, {{500, -5., 5.}});
  registry.add("hPy", "Py;#it{P_{y}}, GeV/c;", kTH1D, {{500, -5., 5.}});
  registry.add("hPz", "Pz;#it{P_{z}}, GeV/c;", kTH1D, {{500, -5., 5.}});
  registry.add("hRap", "Rapidity of Mother;#it{y};", kTH1D, {{500, -10., 10.}});
  registry.add("hEta", "Eta;#it{#eta};", kTH1D, {{500, -10., 10.}});
  //registry.add("hCharge", "Charge;#it{charge};", kTH1D, {{500, -10., 10.}});
  registry.add("hPhi", "Phi;#it{#Phi};", kTH1D, {{500, -6., 6.}});



  }
  //Configurable<float> etalow{"etalow", -1.0f, ""};   //
  //Configurable<float> etahigh{"etahigh", 1.0f, ""}; //
  //Configurable<int> ntracks{"ntracks",2,""};//
  //Filter etaFilter = (aod::fwdtrack::eta > etalow) && (aod::fwdtrack::eta < etahigh);
  //Filter trackFilter = (aod::fwdtrack::size == 2);
  // new
  //void process(soa::Join<aod::BCs, aod::Run2BCInfos, aod::BcSels >::iterator const& bc, aod::FwdTracks const& tracksMuon)
  //using MyEvents = soa::Join<aod::Collisions, aod::EvSels>

  void process(aod::Collisions::iterator const& collision, aod::BCs const& bcs, aod::FwdTracks const& tracksMuon)

  //{
    //fullSkimming<gkEventFillMap, gkTrackFillMap, gkMuonFillMap>(collision, bcs, tracksBarrel, tracksMuon);
  //}
  //void process(aod::BC::iterator const& bc, aod::FwdTracks const& tracksMuon)//,soa::Join<aod::BCs,aod::BcSels> const& bcs)
  //void process(soa::Join<aod::BCs, aod::Run2BCInfos, aod::BcSels>::iterator const& bc, soa::Filtered<aod::FwdTracks> const& tracksMuon)
  {
    auto bc = collision.bc_as<soa::Join<aod::BCs,aod::BcSels>>();
    registry.fill(HIST("hSelectionCounter"), 0);

    //int iMuonTracknumber = 0;
    TLorentzVector p1, p2, p;
    //bool ispositive = kFALSE;
    //bool isnegative = kFALSE;






    // V0 and FD information
    /*bool isBeamBeamV0A = bc.bbV0A();
    bool isBeamGasV0A = bc.bgV0A();
    // bool isBeamBeamV0C = bc.bbV0C();
    bool isBeamGasV0C = bc.bgV0C();

    bool isBeamBeamFDA = bc.bbFDA();
    bool isBeamGasFDA = bc.bgFDA();
    bool isBeamBeamFDC = bc.bbFDC();
    bool isBeamGasFDC = bc.bgFDC();

    // offline V0 and FD selection
    bool isV0Selection = isBeamBeamV0A || isBeamGasV0A || isBeamGasV0C;
    bool isFDSelection = isBeamBeamFDA || isBeamGasFDA || isBeamBeamFDC || isBeamGasFDC;*/
    if (tracksMuon.size()!=2) {
      //cout << "no fwd tracks"<< endl;
      return;}
  //  registry.fill(HIST("hSelectionCounter"), 0);
    cout << tracksMuon.size()<< "........"<<endl;



    for (auto& muon : tracksMuon) {
          cout << "this process is started"<< muon.pt()<< endl;

          fwdTracks(muon.pt(), muon.eta(), muon.phi(), muon.sign());


        }

      auto   muon1 = tracksMuon.begin();
      auto   muon2 = muon1+1;
      if (muon1.sign() * muon2.sign() >= 0) {
          return;
      }
      p1.SetPtEtaPhiM(muon1.pt(),muon1.eta(),muon1.phi(),mmuon);
      p2.SetPtEtaPhiM(muon2.pt(),muon2.eta(),muon2.phi(),mmuon);

      p = p1+p2;
      //registry.fill(HIST("hSelectionCounter"), 7);
      registry.fill(HIST("hPt"), p.Pt());
      registry.fill(HIST("hPx"), p.Px());
      registry.fill(HIST("hPy"), p.Py());
      registry.fill(HIST("hPz"), p.Pz());
      registry.fill(HIST("hRap"), p.Rapidity());
      registry.fill(HIST("hMass"), p.M());
      registry.fill(HIST("hPhi"), p.Phi());
      registry.fill(HIST("hEta"), p1.Eta());
      registry.fill(HIST("hEta"), p2.Eta());
      //registry.fill(HIST("hPtsingle_muons"), p1.Pt());
      //registry.fill(HIST("hPtsingle_muons"), p2.Pt());



  } // end of process

}; // end of struct

WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
  return WorkflowSpec{
    adaptAnalysisTask<UPCForwardRun3>(cfgc)};
}
