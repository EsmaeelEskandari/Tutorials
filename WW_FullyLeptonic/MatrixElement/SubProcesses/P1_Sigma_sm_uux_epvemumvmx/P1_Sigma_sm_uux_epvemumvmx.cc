// 
// *  This file was automatically generated by MoMEMta-MaGMEE,
// *  A MadGraph Matrix Element Exporter plugin for MoMEMta.
// *
// *  It is subject to MoMEMta-MaGMEE's license and copyright:
// *
// *  Copyright (C) 2016  Universite catholique de Louvain (UCL), Belgium
// *
// *  This program is free software: you can redistribute it and/or modify
// *  it under the terms of the GNU General Public License as published by
// *  the Free Software Foundation, either version 3 of the License, or
// *  (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// *  GNU General Public License for more details.
// *
// *  You should have received a copy of the GNU General Public License
// *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 

#include <string> 
#include <utility> 
#include <vector> 
#include <map> 

#include <P1_Sigma_sm_uux_epvemumvmx.h> 
#include <HelAmps_sm.h> 

#include <momemta/ParameterSet.h> 
#include <momemta/SLHAReader.h> 

namespace pp_WW_fully_leptonic_sm 
{

//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: u u~ > w+ w- WEIGHTED<=4 @1
// *   Decay: w+ > e+ ve WEIGHTED<=2
// *   Decay: w- > mu- vm~ WEIGHTED<=2
// Process: c c~ > w+ w- WEIGHTED<=4 @1
// *   Decay: w+ > e+ ve WEIGHTED<=2
// *   Decay: w- > mu- vm~ WEIGHTED<=2
// Process: d d~ > w+ w- WEIGHTED<=4 @1
// *   Decay: w+ > e+ ve WEIGHTED<=2
// *   Decay: w- > mu- vm~ WEIGHTED<=2
// Process: s s~ > w+ w- WEIGHTED<=4 @1
// *   Decay: w+ > e+ ve WEIGHTED<=2
// *   Decay: w- > mu- vm~ WEIGHTED<=2

//--------------------------------------------------------------------------

// Initialize process.

P1_Sigma_sm_uux_epvemumvmx::P1_Sigma_sm_uux_epvemumvmx(const ParameterSet&
    configuration)
{

  std::string param_card = configuration.get < std::string > ("card"); 
  params.reset(new Parameters_sm(SLHA::Reader(param_card))); 

  // Set external particle masses for this matrix element
  mME.push_back(params->ZERO); 
  mME.push_back(params->ZERO); 
  mME.push_back(params->ZERO); 
  mME.push_back(params->ZERO); 
  mME.push_back(params->ZERO); 
  mME.push_back(params->ZERO); 

  mapFinalStates[{-11, 12, 13, -14}] = 
  {
    {
      &P1_Sigma_sm_uux_epvemumvmx::matrix_1_uux_wpwm_wp_epve_wm_mumvmx, 
      true, 
      {
        std::make_pair(2, -2), std::make_pair(4, -4)
      }, 
      64, 
      36
    }
    , 
    {
      &P1_Sigma_sm_uux_epvemumvmx::matrix_1_ddx_wpwm_wp_epve_wm_mumvmx, 
      true, 
      {
        std::make_pair(1, -1), std::make_pair(3, -3)
      }, 
      64, 
      36
    }
  }; 

}

//--------------------------------------------------------------------------
// Evaluate |M|^2, return a map of final states

std::map < std::pair < int, int > , double >
    P1_Sigma_sm_uux_epvemumvmx::compute(const std::pair < std::vector<double> ,
    std::vector<double> > &initialMomenta, const std::vector < std::pair < int,
    std::vector<double> > > &finalState)
{

  // Set initial particle momenta
  momenta[0] = (double * ) (&initialMomenta.first[0]); 
  momenta[1] = (double * ) (&initialMomenta.second[0]); 

  // Suppose final particles are passed in the "correct" order
  std::vector<int> selectedFinalState(6 - 2); 
  for (size_t index = 0; index < (6 - 2); index++ )
  {
    selectedFinalState[index] = finalState[index].first; 
    momenta[index + 2] = (double * ) (&finalState[index].second[0]); 
  }

  // Set the event specific parameters
  params->updateParameters(); 
  params->updateCouplings(); 

  // Initialise result object
  std::map < std::pair < int, int > , double > result; 

  // Define permutation
  int perm[6]; 
  for(int i = 0; i < 6; i++ )
  {
    perm[i] = i; 
  }

  for(auto &me: mapFinalStates[selectedFinalState])
  {

    double me_sum = 0; 
    double me_mirror_sum = 0; 

    for(int ihel = 0; ihel < 64; ihel++ )
    {

      if(me.goodHel[ihel])
      {

        double sum = 0.; 
        calculate_wavefunctions(perm, helicities[ihel]); 
        double meTemp = me.callback( * this); 
        sum += meTemp; 
        me_sum += meTemp/me.denominator; 

        if(me.hasMirrorProcess)
        {
          perm[0] = 1; 
          perm[1] = 0; 
          // Calculate wavefunctions
          calculate_wavefunctions(perm, helicities[ihel]); 
          // Mirror back
          perm[0] = 0; 
          perm[1] = 1; 
          meTemp = me.callback( * this); 
          sum += meTemp; 
          me_mirror_sum += meTemp/me.denominator; 
        }

        if( !sum)
          me.goodHel[ihel] = false; 
      }
    }

    for (auto const &initialState: me.initialStates)
    {
      result[initialState] = me_sum; 
      if (me.hasMirrorProcess)
        result[std::make_pair(initialState.second, initialState.first)] =
            me_mirror_sum;
    }
  }


  return result; 
}

//==========================================================================
// Private class member functions

//--------------------------------------------------------------------------
// Evaluate |M|^2 for each subprocess

void P1_Sigma_sm_uux_epvemumvmx::calculate_wavefunctions(const int perm[],
    const int hel[])
{
  // Calculate wavefunctions for all processes
  static std::complex<double> w[14][18]; 

  // Calculate all wavefunctions
  ixxxxx(&momenta[perm[0]][0], mME[0], hel[0], +1, w[0]); 
  oxxxxx(&momenta[perm[1]][0], mME[1], hel[1], -1, w[1]); 
  ixxxxx(&momenta[perm[2]][0], mME[2], hel[2], -1, w[2]); 
  oxxxxx(&momenta[perm[3]][0], mME[3], hel[3], +1, w[3]); 
  FFV2_3(w[2], w[3], params->GC_100, params->mdl_MW, params->mdl_WW, w[4]); 
  oxxxxx(&momenta[perm[4]][0], mME[4], hel[4], +1, w[5]); 
  ixxxxx(&momenta[perm[5]][0], mME[5], hel[5], -1, w[6]); 
  FFV2_3(w[6], w[5], params->GC_100, params->mdl_MW, params->mdl_WW, w[7]); 
  FFV1P0_3(w[0], w[1], params->GC_2, params->ZERO, params->ZERO, w[8]); 
  FFV2_5_3(w[0], w[1], params->GC_51, params->GC_58, params->mdl_MZ,
      params->mdl_WZ, w[9]);
  FFV2_2(w[0], w[4], params->GC_100, params->ZERO, params->ZERO, w[10]); 
  FFV1P0_3(w[0], w[1], params->GC_1, params->ZERO, params->ZERO, w[11]); 
  FFV2_3_3(w[0], w[1], params->GC_50, params->GC_58, params->mdl_MZ,
      params->mdl_WZ, w[12]);
  FFV2_2(w[0], w[7], params->GC_100, params->ZERO, params->ZERO, w[13]); 

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  VVV1_0(w[8], w[7], w[4], params->GC_4, amp[0]); 
  VVV1_0(w[7], w[4], w[9], params->GC_53, amp[1]); 
  FFV2_0(w[10], w[1], w[7], params->GC_100, amp[2]); 
  VVV1_0(w[11], w[7], w[4], params->GC_4, amp[3]); 
  VVV1_0(w[7], w[4], w[12], params->GC_53, amp[4]); 
  FFV2_0(w[13], w[1], w[4], params->GC_100, amp[5]); 

}
double P1_Sigma_sm_uux_epvemumvmx::matrix_1_uux_wpwm_wp_epve_wm_mumvmx() 
{

  static std::complex<double> ztemp; 
  static std::complex<double> jamp[1]; 
  // The color matrix
  static const double denom[1] = {1}; 
  static const double cf[1][1] = {{3}}; 

  // Calculate color flows
  jamp[0] = -amp[0] - amp[1] - amp[2]; 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(int i = 0; i < 1; i++ )
  {
    ztemp = 0.; 
    for(int j = 0; j < 1; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  return matrix; 
}

double P1_Sigma_sm_uux_epvemumvmx::matrix_1_ddx_wpwm_wp_epve_wm_mumvmx() 
{

  static std::complex<double> ztemp; 
  static std::complex<double> jamp[1]; 
  // The color matrix
  static const double denom[1] = {1}; 
  static const double cf[1][1] = {{3}}; 

  // Calculate color flows
  jamp[0] = -amp[3] - amp[4] - amp[5]; 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(int i = 0; i < 1; i++ )
  {
    ztemp = 0.; 
    for(int j = 0; j < 1; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  return matrix; 
}



}

// Register matrix element with MoMEMta
#include <momemta/MatrixElementFactory.h>
REGISTER_MATRIX_ELEMENT("pp_WW_fully_leptonic",
    pp_WW_fully_leptonic_sm::P1_Sigma_sm_uux_epvemumvmx);
