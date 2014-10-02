/**
 *
 * @author : Yuta Takahashi
 * @goal : create trees to be used for the HO efficiency study
 * @email : Yuta.Takahashi@cern.ch
 * @date : 24 Apr 2014
 *
 * Extrapolate muon track to the HO plane
 *
 **/

#include "TVectorD.h"
#include "TMath.h"

#ifndef __CINT__
#include "Math/Point3D.h"
#include "Math/Vector3D.h"
#include "Math/Plane3D.h"

using namespace ROOT::Math;

#endif

int judgeOnHOplane() { 

  // define plane by 3 points from HO
  XYZPoint p1(1,2,3);
  XYZPoint p2(-2,-1,4);
  XYZPoint p3(-1,3,2);
  Plane3D plane(p1,p2,p3);
  
  // extrapolate muon track to the extreme case, based on innermost XYZ
  XYZPoint muon_in(10,10,10);
  XYZPoint muon_out(-10,-10,-10);

  // retrieve the normal vector to the HO plane
  XYZVector n = plane.Normal();
  
  // check dot product to see if the muon line cross the HO plane
  Double_t n_in = n.Dot(muon_in-p1);
  Double_t n_out = n.Dot(muon_out-p1);  

  if(n_out*n_in > 0) return -1;
  std::cout << "HO and muon trajectory has a cross-point" << std::endl;

  // evaluate the cross-point
  XYZVector muon = muon_out - muon_in;
  Double_t ratio = TMath::Abs(n_in) / (TMath::Abs(n_in) + TMath::Abs(n_out));

  // starting from muon_in and extend the muon line with the ratio above
  Double_t x_cross = muon_in.X() + muon.X()*ratio;
  Double_t y_cross = muon_in.Y() + muon.Y()*ratio;
  Double_t z_cross = muon_in.Z() + muon.Z()*ratio;

  XYZPoint crosspoint(x_cross, y_cross, z_cross);

  if(TMath::Abs(n.Dot(crosspoint-p1)) > 0.0000000001) std::cout << "You are wrong !" << std::endl;

  std::cout << x_cross << " " << y_cross << " " << z_cross << std::endl;
}



void HO_efficiency() {

#ifdef __CINT__
  gSystem->Load("libMathCore");
  using namespace ROOT::Math;
#endif
 
  judgeOnHOplane();

}

