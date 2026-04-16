#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
// 
#include <TRandom3.h>
#include <TFile.h>
#include <TH1.h>
#include <TLorentzVector.h>
#include "HELIOSLibrary/HELIOSLibrary.h"
#include "MyPlotting/MyPlot.C"


using namespace std;

///////////////////////////////////////////////////////////////////////////////
void TestDecayNew(){
//
cout << "Hello word" << endl;
  TRandom3 MyRandy = TRandom3(0);                // Random Generator
  TLorentzVector temp;
  Double_t ww = 0; 
  Int_t id = 0;

  Int_t iopt = 3;                                   

  cout << endl;

  MyPlot plot;
  PHENIXDetector PHENIX;

  Particle pi0("pi0");
  Particle eta("eta");
  Particle omega("omega");
  Particle gamma1("photon");
  Particle gamma2("photon");
  Particle electron("electron");
  Particle positron("positron");
  TLorentzVector eepair,ggpair;
  TLorentzVector reco1,reco2;

  Double_t E1, E2, OpeningAngle;
  Double_t Phi1,Phi2;
  Double_t e1, e2;
  Double_t pt_min = 0.1;
  Double_t pt_max = 35.;
  Double_t pt_low = 0.1;
  Double_t pt_high = 20.;
  Double_t ptcut = 0.2;
  Double_t ecut = 0.5;
  Double_t Dtower = 5.535;
  Int_t nevt = 10000000;
  Bool_t ek  = 1;
  Bool_t out = 0;
  Bool_t g1Found = false;
  Bool_t g2Found = false;
  Bool_t g1Reco  = false;
  Bool_t g2Reco  = false;
  Bool_t DoDecay;
  Double_t weight = 1.;
  Int_t ndecay =0;

  TF1 *piHagedorn      = HagedornYield("piHagedorn", pi0Mass, pt_max, pt_min);
  TF1 *etaHagedorn     = HagedornYield("etaHagedorn", etaMass, pt_max, pt_min);
  TF1 *rho0Hagedorn    = HagedornYield("omegaHagedorn", rho0Mass, pt_max, pt_min);
  TF1 *omegaHagedorn   = HagedornYield("omegaHagedorn", omegaMass, pt_max, pt_min);
  TF1 *etapHagedorn    = HagedornYield("etapHagedorn", etapMass, pt_max, pt_min);
  TF1 *phiHagedorn     = HagedornYield("phiHagedorn", phiMass, pt_max, pt_min);
  TF1 *jpsiHagedorn     = HagedornYield("phiHagedorn", phiMass, pt_max, pt_min);
  TF1 *psipHagedorn     = HagedornYield("phiHagedorn", phiMass, pt_max, pt_min);
//  TF1 *pi0Phi         = new TF1("pi0Phi","1+[0]*x",-2*pi,2*pi);
//  TF1 *pi0Rapidity    = new TF1("pi0Rapidity","1+[0]*x",-.5,.5);

  TH1D *h_ptpi             = new TH1D("h_ptpi","pt",400,pt_low,pt_high);
  TH1D *h_ptpiReco         = new TH1D("h_ptpiReco","pt",400,pt_low,pt_high);
  TH1D *h_pt_gpi           = new TH1D("h_pt_gpi","pt_g",400,pt_low,pt_high);
  TH1D *h_pt_gpi1           = new TH1D("h_pt_gpi1","pt_g",400,pt_low,pt_high);
  TH1D *h_pt_gpi2           = new TH1D("h_pt_gpi2","pt_g",400,pt_low,pt_high);

// oid plot.StyleMe(TH1D *tE, int marker = 20, int color = 1, double msize = 1.2, int lstyle = 1, float lwidth = 2)
  plot.StyleMe(h_ptpi,   20, kBlue, 1., 1, 2); 
  plot.StyleMe(h_ptpiReco,   20, kBlue+3, 1.,1, 2); 
  plot.StyleMe(h_pt_gpi, 20, kBlue, 1., 2, 2); 
  plot.StyleMe(h_pt_gpi1, 20, kBlue+3, 1., 10, 2); 
  plot.StyleMe(h_pt_gpi2, 20, kBlue-9, 1., 6, 2); 
  
  TH1D *h_pteta             = new TH1D("h_pteta","pt",100,pt_low,pt_high);
  TH1D *h_pt_geta           = new TH1D("h_pt_geta","pt_g",100,pt_low,pt_high);
  TH1D *h_pt_geta1           = new TH1D("h_pt_geta1","pt_g",100,pt_low,pt_high);

  plot.StyleMe(h_pteta,   20, kRed, 1., 1, 2); 
  plot.StyleMe(h_pt_geta, 20, kRed, 1., 2, 2); 
  plot.StyleMe(h_pt_geta1, 20, kRed+3, 1., 10, 2); 

  TH1D *h_ptomega             = new TH1D("h_ptomega","pt",100,pt_low,pt_high);
  TH1D *h_pt_gomega           = new TH1D("h_pt_gomega","pt_g",100,pt_low,pt_high);
  TH1D *h_pt_gomega1          = new TH1D("h_pt_gomega1","pt_g",100,pt_low,pt_high);

  plot.StyleMe(h_ptomega,   20, kGreen+2, 1., 1, 2); 
  plot.StyleMe(h_pt_gomega, 20, kGreen+2, 1., 2, 2); 

  TH1D *h_ptetap             = new TH1D("h_ptetap","pt",100,pt_low,pt_high);
  TH1D *h_pt_getap           = new TH1D("h_pt_getap","pt_g",100,pt_low,pt_high);

  plot.StyleMe(h_ptetap,   20, kOrange+2, 1., 1, 2); 
  plot.StyleMe(h_pt_getap, 20, kOrange+2, 1., 2, 2); 

  TH1D *h_pt_g           = new TH1D("h_pt_g","pt_g",100,pt_low,pt_high);
  TH1D *h_pt_g1          = new TH1D("h_pt_g1","pt_g",100,pt_low,pt_high);

  plot.StyleMe(h_pt_g,   20, kBlack, 1., 1, 2); 
  plot.StyleMe(h_pt_g1,   20, kBlack, 1., 2, 2); 


  for (int i=0; i<nevt; i++){                                     // event loop
    if(i%1000000==0) cout << "event loop at " << i << endl;         // event counter printed 
/////////////////////////////////////////////// pi decays ////////////////////////////////////////////////
    pi0.ResetP();
    pi0.GenerateP(pt_min,pt_max);                                // generate 4 vector for pi0 with flat distribution
    pi0.SetWeight(piHagedorn->Eval(pi0.Pt())/float(nevt));
    h_ptpi->Fill(pi0.Pt(),pi0.Weight());                         // histogram pion proprety

    DoDecay = (PHENIX.EMCalSector(pi0.Phi())>0 && abs(pi0.Eta())<0.35);  
    
    ndecay=0;
    if (DoDecay) { 
      if (iopt == 1) pi0.DecayFlat();
      if (iopt == 2) pi0.DecaySingleBranch("pi0->Dalitz");
      if (iopt == 3) pi0.DecaySingleBranch("pi0->gg");
      ndecay = pi0.GetNumberOfDaughters();
    }

    if (i<10) cout << "----- Pi0Deacy --------------------------------------------------------" << endl; 
    if (i<10) cout << " found decay with " << ndecay << " daughters " << endl; 
    if (i<10) cout << " weight " << pi0.GetDaughterWeight(0) << endl;

    g1Found = false;
    g2Found = false;    
    g1Reco  = false;
    g2Reco  = false;    

    for (Int_t j=0; j< ndecay; j++) {
      temp = pi0.GetDecayDaughter(j);
      if (i<10) temp.Print();
      ww   = pi0.GetDaughterWeight(j)*pi0.Weight();
      id   = pi0.GetDaughterID(j);
      if (i<10) cout << " weight " << ww << " id: " << id << endl;
      if (id == photonID) {
         if (j==0) { gamma1 = temp; g1Found = true;}
         if (j==1) { gamma2 = temp; g2Found = true;} 
      } 
    }

    if (g1Found) {
      PHENIX.CharacterizeTrack(gamma1,0,photonID);
      reco1  = PHENIX.ReconstructShower(gamma1,pi0.GetDaughterID(0));
      g1Reco = (reco1.E()>ecut) && (PHENIX.EMCalSector(reco1.Phi())>0) && (abs(reco1.Eta())<0.35);
      if (g1Reco) h_pt_gpi->Fill(reco1.Pt(),ww);   
    }
    if (g2Found) {
      PHENIX.CharacterizeTrack(gamma2,0,photonID);
      reco2  = PHENIX.ReconstructShower(gamma2,pi0.GetDaughterID(1));
      g2Reco = (reco2.E()>ecut) && (PHENIX.EMCalSector(reco2.Phi())>0) && (abs(reco2.Eta())<0.35);
      if (g2Reco) h_pt_gpi->Fill(reco2.Pt(),ww);   
    }
  
    if (g1Found && g2Found) {
      ggpair = reco1+reco2;
      OpeningAngle = gamma1.Angle(gamma2.Vect())*100*P_R_EMCal; 
      if (OpeningAngle > 2.*Dtower ){                            // both showers seperated 
         if (g1Reco) h_pt_gpi1->Fill(reco1.Pt(),ww);
         if (g2Reco) h_pt_gpi1->Fill(reco2.Pt(),ww);
         E1 = reco1.E();
         E2 = reco2.E();
         Phi1 = reco1.Phi();
         Phi2 = reco2.Phi();
         if ((E1>ecut && E2>ecut) 
              && (abs(E1-E2)/(E1+E2)<0.8)
              && (PHENIX.EMCalSector(Phi1)>0)
              && (PHENIX.EMCalSector(Phi1)==PHENIX.EMCalSector(Phi2))
              && (abs(reco1.Eta())<0.35 && abs(reco2.Eta())<0.35 )
              && (PHENIX.EMCalLive(PHENIX.EMCalSector(Phi1)))
              && (PHENIX.EMCalLive(PHENIX.EMCalSector(Phi2)))
              ){
            h_ptpiReco->Fill(ggpair.Pt(),pi0.Weight());
         }
      } else if (OpeningAngle < 2.*Dtower) {
//         cout << OpeningAngle << " " << ggpair.Pt()  << endl;
         h_pt_gpi2->Fill(ggpair.Pt(),ww);
      } 
    } else if (g1Found && ! g2Found) {
         h_pt_gpi1->Fill(reco1.Pt(),ww);      
    }
///////////////////////////////////////////// eta decays ////////////////////////////////////////////////
    // eta.ResetP();
    // eta.GenerateP(pt_min,pt_max);                                // generate 4 vector for pi0 with flat distribution
    // eta.SetWeight(etaHagedorn->Eval(eta.Pt())/float(nevt)*0.5);
    // h_pteta->Fill(eta.Pt(),eta.Weight());                         // histogram pion proprety
      // 
    // if (iopt == 1) eta.Decay();
    // if (iopt == 2) eta.DecayFlat();
    // if (iopt == 3) eta.DecaySingleBranch("eta->gg");
    // if (iopt == 4) eta.DecaySingleBranch("eta->Dalitz");
// 
    // ndecay = eta.GetNumberOfDaughters();
    // if (i<10)  cout << "----- EtaDeacy --------------------------------------------------------" << endl; 
    // if (i<10) cout << " found decay with " << ndecay << " daughters " << endl; 
     // 
    // g1Found = false;
    // g2Found = false;    
// 
    // for (Int_t j=0; j< ndecay; j++) {
      // temp = eta.GetDecayDaughter(j);
      // if (i<10) temp.Print();
      // ww   = eta.GetDaughterWeight(j)*eta.Weight();
      // id   = eta.GetDaughterID(j);
      // if (i<10) cout << " weight " << ww << " id: " << id << endl;
      // if (id == photonID) {
         // h_pt_geta->Fill(temp.Pt(),ww);   
         // if (j==0) { gamma1 = temp; g1Found = true;}
         // if (j==1) { gamma2 = temp; g2Found = true;} 
      // } 
    // }
    // if (g1Found && g2Found) {
      // ggpair = gamma1+gamma2;
      // OpeningAngle = gamma1.Angle(gamma2.Vect())*100*P_R_EMCal; 
      // if (OpeningAngle > 2.*Dtower ){                            // both showers seperated 
         // h_pt_geta1->Fill(gamma1.Pt(),ww);
         // h_pt_geta1->Fill(gamma2.Pt(),ww);
      // } else if (OpeningAngle < 2.*Dtower) {
        //cout << OpeningAngle << " " << ggpair.Pt()  << endl;
        //h_pt_gpi2->Fill(ggpair.Pt(),ww);
      // } 
      // eepair.Print();
      // if (i<100) {
        // ggpair.Print();
      // }
    // } else if (g1Found && ! g2Found) {
         // h_pt_geta1->Fill(gamma1.Pt(),ww);      
    // }
// 
///////////////////////////////////////////// omega decays ////////////////////////////////////////////////
    // omega.ResetP();
    // omega.GenerateP(pt_min,pt_max);                                // generate 4 vector for pi0 with flat distribution
    // omega.SetWeight(omegaHagedorn->Eval(omega.Pt())/float(nevt)*0.9);
    // h_ptomega->Fill(omega.Pt(),omega.Weight());                         // histogram pion proprety
// 
    // if (iopt == 1) omega.Decay();
    // if (iopt == 2) omega.DecayFlat();
    // if (iopt == 3) omega.DecaySingleBranch("omega->gg");
    // if (iopt == 4) omega.DecaySingleBranch("omega->pi0ee");
    // if (iopt == 5) omega.DecaySingleBranch("omega->ee");
// 
    // ndecay = omega.GetNumberOfDaughters();
    // if (i<10)  cout << "----- omegaDeacy --------------------------------------------------------" << endl; 
    // if (i<10) cout << " found decay with " << ndecay << " daughters " << endl; 
// 
    // for (Int_t j=0; j< ndecay; j++) {
       // temp = omega.GetDecayDaughter(j);
       // if (i<10) temp.Print();
       // ww   = omega.GetDaughterWeight(j)*omega.Weight();
       // id   = omega.GetDaughterID(j);
       // if (i<10) cout << " weight " << ww << " id: " << id << endl;
       // if (id == photonID) {
          // h_pt_gomega->Fill(temp.Pt(),ww);    
          // h_pt_gomega1->Fill(temp.Pt(),ww);      
       // }
    // }    
///////////////////////////////////////////////////////////////////////////////////////
  }
/////////////////////////////////////////////////////////////////////////////////////////


  h_pt_g->Add(h_pt_gpi);
  h_pt_g->Add(h_pt_geta);
  h_pt_g->Add(h_pt_gomega);
  h_pt_g->Add(h_pt_getap);

  h_pt_g1->Add(h_pt_gpi1);                                         // (A) pi0 gamma no overlap
  h_pt_g1->Add(h_pt_geta1);
  h_pt_g1->Add(h_pt_gomega1);

  TH1D *h_R_g         = (TH1D*)h_pt_gpi1->Clone("h_R_g");         // (B) single gamma from pi0
  TH1D *h_R_g1        = (TH1D*)h_pt_gpi1->Clone("h_R_g1");
  h_R_g->Divide(h_pt_gpi);                                        // (1+K) = (A)/(B)                             
  
  h_R_g1->Add(h_pt_gpi2);
  h_R_g1->Divide(h_pt_gpi);
  plot.StyleMe(h_R_g1, 20, kBlue-9, 1., 6, 2); 

  TH1D *h_ae_pi      = (TH1D*)h_ptpiReco->Clone("h_ae_pi");
  h_ae_pi->Divide(h_ptpi);


///////////////////////////////////////////////////////////////////////////////////////
  plot.SetLeftMargin(.2);  
  plot.SetyTitleOffset(1.4);
  TCanvas *c1 = plot.Canvas ("c1",400,600,10,10,1);
  TH1D *pt1 = plot.Frame("pt1","p_{T} [GeV/c^{2}]","dN/dp_{T} [a.u.]",pt_low,pt_high*.999,1e-12,0.01);
  pt1->Draw();
  h_ptpi->Draw("sameL Chist");
  h_ptpiReco->Draw("sameL Chist");
//  h_pteta->Draw("sameL Chist");
//  h_ptomega->Draw("sameL Chist");
//  h_ptetap->Draw("sameL Chist");

  TLegend *L1 = plot.Legend("" ,0.4,.79,.9,.95);
  L1->AddEntry(h_ptpi,"#pi^{0} generated" ,"l");
  L1->AddEntry(h_ptpiReco,"#pi^{0} reconstructed" ,"l");
//  L1->AddEntry(h_pteta,"#eta","l");
//  L1->AddEntry(h_ptomega,"#omega","l");  
//  L1->AddEntry(h_ptetap,"#eta'","l");  
  L1->Draw("same");

///////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *c11 = plot.Canvas ("c11",400,600,410,10,1);
  TH1D *pt2 = plot.Frame("pt2","p_{T} [GeV/c^{2}]","dN/dp_{T} [a.u.]",pt_low,pt_high*.999,1e-13,0.001);
  pt2->Draw();
//  h_ptpi->Draw("sameL Chist");
//  h_ptpiReco->Draw("sameL Chist");
  h_pt_gpi->Draw("same Chist" );
  h_pt_gpi1->Draw("same Chist" );
  h_pt_gpi2->Draw("same Chist" );
//  h_pt_geta->Draw("same Chist");
//  h_pt_geta1->Draw("same Chist");
//  h_pt_gomega->Draw("same Chist");
//  h_pt_getap->Draw("same Chist");

  TLegend *L11 = plot.Legend("#gamma from #pi^{0} decays of" ,0.4,.69,.9,.95);
  L11->AddEntry(h_pt_gpi,"no shower merging","l");
  L11->AddEntry(h_pt_gpi1,"#gamma's lost #Delta < 2 towers","l");
  L11->AddEntry(h_pt_gpi2,"#pi^{0} one shower  < 2 towers","l");
//  L11->AddEntry(h_pt_geta,"#eta","l");
//  L11->AddEntry(h_pt_gomega,"#omega","l");  
//  L11->AddEntry(h_pt_getap,"#eta'","l");  
  L11->Draw("same");
  plot.Reset();

////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *c22= plot.Canvas ("c22",400,300,810,610);
  TH1D *ptr2 = plot.Frame("ptr2","p_{T} [GeV/c^{2}]","(1+K)",pt_low,pt_high*.999,0.002,3.5);
  ptr2->Draw();
  h_R_g->Draw("same Chist");
  h_R_g1->Draw("same Chist");

  plot.Reset();

  TLegend *L22 = plot.Legend(" " ,0.25,.69,.55,.9,1.2);
  L22->AddEntry(h_R_g,"#gamma loss only","l");
  L22->AddEntry(h_R_g1,"#gamma loss and #pi^{0} merged","l");
  L22->Draw("same");

  plot.Reset();

////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *c21= plot.Canvas ("c21",400,300,410,610);
  TH1D *ptr3 = plot.Frame("ptr3","p_{T} [GeV/c^{2}]","acc x #epsilon",pt_low,pt_high*.999,0.002,.27);
  ptr3->Draw();
  h_ae_pi->Draw("same Chist");

  TLegend *L21 = plot.Legend("#pi^{0} " ,0.25,.79,.55,.9,1.2);
  L21->Draw("same");

  plot.Reset();


}




