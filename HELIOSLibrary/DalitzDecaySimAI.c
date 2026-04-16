DalitzDecaySimAI.C

#include <TGenPhaseSpace.h>
#include <TLorentzVector.h>
#include <TRandom3.h>
#include <TH1D.h>
#include <TCanvas.h>

void DalitzDecaySim(int nEvents = 100000) {
    const double mpi0 = 0.134977;   // π⁰ mass in GeV
    const double me   = 0.000511;   // electron mass in GeV

    TLorentzVector pi0(0, 0, 0, mpi0);
    TRandom3 rand(0);

    TH1D* hMee = new TH1D("hMee", "Invariant Mass of e+e-;m_{ee} [GeV];Events", 100, 2*me, mpi0);
    TH1D* hCosTheta = new TH1D("hCosTheta", "cos(#theta*) in γ* frame;cos(#theta*);Events", 100, -1, 1);

    for (int i = 0; i < nEvents; ++i) {
        // Sample m_ee from allowed range
        double mee;
        double weight;
        do {
            mee = rand.Uniform(2*me, mpi0);
            double q2 = mee * mee;
            double kinematic = (1 - q2 / (mpi0 * mpi0));
            weight = (1 + 2 * me * me / q2) * pow(kinematic, 3) / mee;
        } while (rand.Uniform() > weight);  // accept-reject sampling

        // Construct virtual photon (γ*) and real photon
        double E_gamma = (mpi0*mpi0 - mee*mee) / (2*mpi0);
        double E_ee    = mpi0 - E_gamma;
        TLorentzVector gamma(0, 0, E_gamma, E_gamma);
        TLorentzVector gammaStar(0, 0, -E_gamma, E_ee);

        // Boost to γ* rest frame
        TVector3 boostVec = -gammaStar.BoostVector();

        // Sample cosθ* from 1 + cos²θ* distribution
        double cosTheta;
        do {
            cosTheta = rand.Uniform(-1, 1);
            double w = 1 + cosTheta * cosTheta + pow(2*me/mee, 2) * (1 - cosTheta * cosTheta);
            if (rand.Uniform(0, 2) < w) break;
        } while (true);

        double sinTheta = sqrt(1 - cosTheta * cosTheta);
        double phi = rand.Uniform(0, 2 * TMath::Pi());

        // e⁺ and e⁻ momenta in γ* frame
        double Ee = mee / 2;
        double pe = sqrt(Ee*Ee - me*me);
        TVector3 p_e(pe * sinTheta * cos(phi), pe * sinTheta * sin(phi), pe * cosTheta);
        TLorentzVector ePlus(p_e, Ee);
        TLorentzVector eMinus(-p_e, Ee);

        // Boost back to π⁰ frame
        ePlus.Boost(boostVec);
        eMinus.Boost(boostVec);

        hMee->Fill(mee);
        hCosTheta->Fill(cosTheta);
    }

    TCanvas* c1 = new TCanvas("c1", "Dalitz Decay", 800, 400);
    c1->Divide(2,1);
    c1->cd(1); hMee->Draw();
    c1->cd(2); hCosTheta->Draw();
}