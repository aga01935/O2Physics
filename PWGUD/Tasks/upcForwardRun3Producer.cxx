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



struct UPCForwardRun3Producer {

  Produces<aod::UDFWDTracks> fwdTracks;



  void init(o2::framework::InitContext&)
  {

  }

  //bcs with collision
  void process(aod::Collisions::iterator const& collision, soa::Join<aod::BCs,aod::BcSels> const& bcs,aod::FwdTracks const& tracksMuon)

  //{
    //fullSkimming<gkEventFillMap, gkTrackFillMap, gkMuonFillMap>(collision, bcs, tracksBarrel, tracksMuon);
  //}
  //void process(aod::BC::iterator const& bc, aod::FwdTracks const& tracksMuon)//,soa::Join<aod::BCs,aod::BcSels> const& bcs)
  //void process(soa::Join<aod::BCs, aod::Run2BCInfos, aod::BcSels>::iterator const& bc, soa::Filtered<aod::FwdTracks> const& tracksMuon)
  {
    //bc with collisions
    auto bc = collision.bc_as<soa::Join<aod::BCs,aod::BcSels>>();
      //auto bc = collision.bc_as<aod::BCs>();


    if (tracksMuon.size()!=2) {

      return;}
    auto muon1 = tracksMuon.begin();
    auto muon2 = muon1+1;

    fwdTracks(muon1.pt(), muon1.eta(), muon1.phi(), muon1.sign(),muon2.pt(),
    muon2.eta(), muon2.phi(), muon2.sign(),bc.bbV0A(),bc.bbV0C(),bc.bgV0A(),
    bc.bgV0C(),bc.bbFDA(),bc.bbFDC(),bc.bgFDA(),bc.bgFDC());



  } // end of process

}; // end of struct

WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
  return WorkflowSpec{
    adaptAnalysisTask<UPCForwardRun3Producer>(cfgc)};
}
