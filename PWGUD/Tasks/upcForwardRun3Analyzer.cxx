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
/// \author Amrit Gautam <agautam@cern.ch>, CERN


#include "Framework/runDataProcessing.h"
#include "Framework/AnalysisTask.h"
#include "Framework/AnalysisDataModel.h"
#include "Common/DataModel/EventSelection.h"
#include "iostream"
#include "Common/DataModel/EventSelection.h"
#include "PWGUD/DataModel/UDForwardDerived.h"
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


struct UPCForwardRun3Analyzer {
  // defining histograms using histogram registry
  HistogramRegistry registry{"registry", {}, OutputObjHandlingPolicy::AnalysisObject};



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
  Configurable<float> etalow{"etalow", -4.0f, ""};   //
  Configurable<float> etahigh{"etahigh", -2.5f, ""}; //
  Configurable<bool> v0select{"v0select", 0, ""};   //
  Configurable<bool> fdselect{"fdselect", 0, ""}; //
  //Filter etaFilter = ((aod::udfwdtrack::eta1> etalow) && (aod::udfwdtrack::eta1< etahigh)
    //                && (aod::udfwdtrack::eta2 > etalow) && (aod::udfwdtrack::eta2 < etahigh));

  //Filter trackFilter = (aod::fwdtrack::size == 2);
  // new
  //void process(soa::Join<aod::BCs, aod::Run2BCInfos, aod::BcSels >::iterator const& bc, aod::FwdTracks const& tracksMuon)
  //using MyEvents = soa::Join<aod::Collisions, aod::EvSels>

  void process(aod::UDFWDTrack const& trackMuon)


  {
    registry.fill(HIST("hSelectionCounter"), 0);


    TLorentzVector p1, p2, p;

    //bool isV0Selection = trackMuon.isbeambeamv0a() || trackMuon.isbeamgasv0a() || trackMuon.isbeamgasv0c();
    //bool isFDSelection = trackMuon.isbeambeamfda() || trackMuon.isbeamgasfda() || trackMuon.isbeambeamfdc() || trackMuon.isbeamgasfdc();

    /*if(v0select) {

      if(isV0Selection) return;
    }

    if(fdselect){

      if(isFDSelection) return;

    }*/






    if (trackMuon.sign1() * trackMuon.sign2() >= 0) {
        return;
    }



    p1.SetPtEtaPhiM(trackMuon.pt1(),trackMuon.eta1(),trackMuon.phi1(),mmuon);
    p2.SetPtEtaPhiM(trackMuon.pt2(),trackMuon.eta2(),trackMuon.phi2(),mmuon);

    if (p1.Eta()<etalow || p1.Eta()>etahigh) return;
    if (p2.Eta()<etalow || p2.Eta()>etahigh) return;

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
    adaptAnalysisTask<UPCForwardRun3Analyzer>(cfgc)};
}
