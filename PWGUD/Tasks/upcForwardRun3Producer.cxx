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

struct UPCForwardRun3Producer {
  // defining histograms using histogram registry
  //HistogramRegistry registry{"registry", {}, OutputObjHandlingPolicy::AnalysisObject};
  Produces<aod::UDFWDTracks> fwdTracks;



  void init(o2::framework::InitContext&)
  {

  }


  void process(aod::Collisions::iterator const& collision, aod::BCs const& bcs, aod::FwdTracks const& tracksMuon)

  //{
    //fullSkimming<gkEventFillMap, gkTrackFillMap, gkMuonFillMap>(collision, bcs, tracksBarrel, tracksMuon);
  //}
  //void process(aod::BC::iterator const& bc, aod::FwdTracks const& tracksMuon)//,soa::Join<aod::BCs,aod::BcSels> const& bcs)
  //void process(soa::Join<aod::BCs, aod::Run2BCInfos, aod::BcSels>::iterator const& bc, soa::Filtered<aod::FwdTracks> const& tracksMuon)
  {
    auto bc = collision.bc_as<soa::Join<aod::BCs,aod::BcSels>>();







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
    auto muon1 = tracksMuon.begin();
    auto muon2 = muon1+1;

    fwdTracks(muon1.pt(), muon1.eta(), muon1.phi(), muon1.sign(),muon2.pt(), muon2.eta(), muon2.phi(), muon2.sign());



  } // end of process

}; // end of struct

WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
  return WorkflowSpec{
    adaptAnalysisTask<UPCForwardRun3Producer>(cfgc)};
}
