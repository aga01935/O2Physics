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

#ifndef O2_ANALYSIS_UDFORWARDDERIVED_H
#define O2_ANALYSIS_UDFORWARDDERIVED_H

#include "Framework/ASoA.h"
#include "Framework/AnalysisDataModel.h"

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

  DECLARE_SOA_COLUMN(isBeamBeamV0A, isbeambeamv0a, bool);
  DECLARE_SOA_COLUMN(isBeamBeamV0C, isbeambeamv0c, bool);
  DECLARE_SOA_COLUMN(isBeamGasV0A, isbeamgasv0a, bool);
  DECLARE_SOA_COLUMN(isBeamGasV0C, isbeamgasv0c, bool);

  DECLARE_SOA_COLUMN(isBeamBeamFDA, isbeambeamfda, bool);
  DECLARE_SOA_COLUMN(isBeamBeamFDC, isbeambeamfdc, bool);
  DECLARE_SOA_COLUMN(isBeamGasFDA, isbeamgasfda, bool);
  DECLARE_SOA_COLUMN(isBeamgasFDC, isbeamgasfdc, bool);





  } // namespace udfwdtrack
  DECLARE_SOA_TABLE(UDFWDTracks, "AOD", "UDFWDTRACK", o2::soa::Index<>,
                    udfwdtrack::Pt1, udfwdtrack::Eta1, udfwdtrack::Phi1,
                    udfwdtrack::Sign1,
                    udfwdtrack::Pt2, udfwdtrack::Eta2, udfwdtrack::Phi2,
                    udfwdtrack::Sign2,
                    udfwdtrack::isBeamBeamV0A,udfwdtrack::isBeamBeamV0C,
                    udfwdtrack::isBeamGasV0A,udfwdtrack::isBeamGasV0C,
                    udfwdtrack::isBeamBeamFDA,udfwdtrack::isBeamBeamFDC,
                    udfwdtrack::isBeamGasFDA,udfwdtrack::isBeamgasFDC);
  using UDFWDTrack = UDFWDTracks::iterator;

} // namespace o2::aod

#endif // O2_ANALYSIS_UDFORWARDDERIVED_H
