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
#include "Common/CCDB/TriggerAliases.h"
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
DECLARE_SOA_COLUMN(Pt1, pt1, float);
DECLARE_SOA_COLUMN(Eta1, eta1, float);
DECLARE_SOA_COLUMN(Phi1, phi1, float);
DECLARE_SOA_COLUMN(Sign1, sign1, float);
DECLARE_SOA_COLUMN(Pt2, pt2, float);
DECLARE_SOA_COLUMN(Eta2, eta2, float);
DECLARE_SOA_COLUMN(Phi2, phi2, float);
DECLARE_SOA_COLUMN(Sign2, sign2, float);

} // namespace udfwdtrack
DECLARE_SOA_TABLE(UDFWDTracks, "AOD", "UDFWDTRACK", o2::soa::Index<>,
                  udfwdtrack::Pt1, udfwdtrack::Eta1, udfwdtrack::Phi1,
                  udfwdtrack::Sign1,
                  udfwdtrack::Pt2, udfwdtrack::Eta2, udfwdtrack::Phi2,
                  udfwdtrack::Sign2);
using UDFWDTrack = UDFWDTracks::iterator;

} // namespace o2::aod


// end of table definition


struct UPCForward {
  // defining histograms using histogram registry
  HistogramRegistry registry{"registry", {}, OutputObjHandlingPolicy::AnalysisObject};
  Produces<aod::UDFWDTracks> fwdTracks;

  void init(o2::framework::InitContext&)
  {

    auto hSelectionCounter = registry.add<TH1>("hSelectionCounter", "hSelectionCounter;;NEvents", HistType::kTH1I, {{30, 0., 30.}});

  // THIS IS THE SELECTION CUTS FOR NOW. We will add further cuts
  //  TString SelectionCuts[8] = {"NoSelection", "CMup11and10Trigger", "V0Selection", "FDSelection", "twotracks", "oppositecharge", "-2.5<Eta<-4", "Pt<1"};
  // now we can set BinLabel in histogram Registry
  //  for (int i = 0; i < 6; i++) {
  //    hSelectionCounter->GetXaxis()->SetBinLabel(i + 1, SelectionCuts[i].Data());
  //  }

    /*registry.add("hMass", "Mass of Mother;#it{m_{#mu#mu}}, GeV/c^{2};", kTH1D, {{500, 0., 10.}});
    registry.add("hPt", "Pt of Mother;#it{p_{t}}, GeV/c;", kTH1D, {{500, 0., 5.}});
    registry.add("hPtsingle_muons", "Pt of Daughters;#it{p_{t}}, GeV/c;", kTH1D, {{500, 0., 5.}});
    registry.add("hPx", "Px;#it{P_{x}}, GeV/c;", kTH1D, {{500, -5., 5.}});
    registry.add("hPy", "Py;#it{P_{y}}, GeV/c;", kTH1D, {{500, -5., 5.}});
    registry.add("hPz", "Pz;#it{P_{z}}, GeV/c;", kTH1D, {{500, -5., 5.}});
    registry.add("hRap", "Rapidity of Mother;#it{y};", kTH1D, {{500, -10., 10.}});
    registry.add("hEta", "Eta;#it{#eta};", kTH1D, {{500, -10., 10.}});
    registry.add("hCharge", "Charge;#it{charge};", kTH1D, {{500, -10., 10.}});
    registry.add("hPhi", "Phi;#it{#Phi};", kTH1D, {{500, -6., 6.}});*/
  }
  //Configurable<float> etalow{"etalow", -4.0f, ""};   //
  //Configurable<float> etahigh{"etahigh", -2.5f, ""}; //
  //Filter etaFilter = (aod::fwdtrack::eta > etalow) && (aod::fwdtrack::eta < etahigh);
  //int triggeradd=0;
  // new

  //void process(soa::Join <aod::BcSels,aod::BCs>::iterator const& bc, aod::FwdTracks const& tracksMuon)
  void process(soa::Join <aod::Collisions, aod::EvSels> const& collision, aod::FwdTracks const& tracksMuon)
  {
      registry.fill(HIST("hSelectionCounter"), 0);
      //bool iskMUP11fired =  bc.alias()[kMUP11];
      //bool iskMUP10fired =  bc.alias()[kMUP10];
      //cout << iskMUP10fired<< "....." << iskMUP11fired<< endl;

      //if(iskMUP10fired || iskMUP11fired) {
      //  triggeradd++;
      //}
      //cout << "number of triggers is "<< triggeradd<<endl;
      //if(!iskMUP10fired && !iskMUP11fired) return;
      //registry.fill(HIST("hSelectionCounter"), 1);
      // V0 and FD information
      //bool isBeamBeamV0A = bc.bbV0A();
    //  bool isBeamGasV0A = bc.bgV0A();
      // bool isBeamBeamV0C = bc.bbV0C();
    //  bool isBeamGasV0C = bc.bgV0C();

      //bool isBeamBeamFDA = bc.bbFDA();
      //bool isBeamGasFDA = bc.bgFDA();
      //bool isBeamBeamFDC = bc.bbFDC();
      //bool isBeamGasFDC = bc.bgFDC();

      // offline V0 and FD selection
      //bool isV0Selection = isBeamBeamV0A || isBeamGasV0A || isBeamGasV0C;
      //bool isFDSelection = isBeamBeamFDA || isBeamGasFDA || isBeamBeamFDC || isBeamGasFDC;

      //if(isV0Selection) return;
      //registry.fill(HIST("hSelectionCounter"), 2);

      //if(isFDSelection) return;
      //registry.fill(HIST("hSelectionCounter"), 3);
      int ntracks = 0;

      TLorentzVector fwdtrack1, fwdtrack2;
      //int fwdtrack1sign;
      //int fwdtrack2sign;

      if (tracksMuon.size()!=2)return;
      cout <<"there are two tracks events"<< tracksMuon.size()<<endl;
      registry.fill(HIST("hSelectionCounter"), 4);

      //cout << "number of track is " << tracksMuon.size()<< endl;
      for (auto& muon : tracksMuon) {
          ntracks++;
      //  if (ntracks>2) continue; //selecting two tracks event
         //auto muon1 = muon.begin();
         //auto muon2 = muon1+1;
         //string s = typeid(muon).name();
         cout <<"##########"<< muon.index()<< endl;
        //fwdtrack1.SetXYZM(muon1.px(), muon1.py(), muon1.pz(), mmuon);
        //fwdtrack2.SetXYZM(muon2.px(), muon2.py(), muon2.pz(), mmuon);
        //fwdTracks(muon.pt());


      } //muon iterate
      cout << "number of tracks is "<<ntracks << endl;



      //if (ntracks!=2) return; // selecting two tracks event

      //fwdTracks(fwdtrack1.pt(), fwdtrack1.eta(), fwdtrack1.phi(),fwdtrack1.M(),fwdtrack1sign, fwdtrack2.pt(), fwdtrack2.eta(), fwdtrack2.phi(), fwdtrack2.M(),fwdtrack2sign);



  } // end of process

}; // end of struct

WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
  return WorkflowSpec{
    adaptAnalysisTask<UPCForward>(cfgc)};
}
