#include "G4BetheBlochModel.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4ParticleTable.hh"
#include "G4MuonMinus.hh"
#include "G4SystemOfUnits.hh"
#include "G4TransportationManager.hh"
#include "G4PropagatorInField.hh"

#include "TCanvas.h"
#include "TGraph.h"

int main() {
    // Create a muon with an energy range from 1 MeV to 1 TeV
    const int numPoints = 100;
    G4double energies[numPoints];
    G4double energyStep = std::pow(10.0, (std::log10(1.0*MeV) + std::log10(1.0*TeV))/numPoints);
    for (int i = 0; i < numPoints; i++) {
        energies[i] = std::pow(10.0, std::log10(1.0*MeV) + i*std::log10(energyStep));
    }

    // Create a material consisting of iron
    G4Material* material = G4NistManager::Instance()->FindOrBuildMaterial("G4_Fe");

    // Calculate the energy loss for each energy using the Bethe-Block formula
    G4double density = material->GetDensity();
    G4double z = material->GetZ();
    G4double a = material->GetA()/g/mole;
    G4double ionization = 0.0;
    G4double radiation = 0.0;
    G4double energyLosses[numPoints];
    for (int i = 0; i < numPoints; i++) {
        G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
        G4ParticleDefinition* muon = particleTable->FindParticle("mu-");
        G4double energy = energies[i];
        G4double momentum = std::sqrt(energy*energy - muon->GetPDGMass()*muon->GetPDGMass());
        G4ThreeVector direction(0.0, 0.0, 1.0);
        G4DynamicParticle* dynParticle = new G4DynamicParticle(muon, momentum*direction, energy);

        energyLosses[i] = G4BetheBlochModel::ComputeDEDX(dynParticle, material, ionization, radiation);
    }

    // Draw the energy loss versus energy using a TGraph
    TCanvas* canvas = new TCanvas("canvas", "Energy Loss vs Energy", 800, 600);
    TGraph* graph = new TGraph(numPoints, energies, energyLosses);
    graph->SetTitle("Energy Loss vs Energy");
    graph->GetXaxis()->SetTitle("Energy (MeV)");
    graph->GetYaxis()->SetTitle("Energy Loss (MeV/cm)");
    graph->SetLineColor(kBlue);
    graph->SetLineWidth(2);
    graph->Draw("AL");

    canvas->SaveAs("energy_loss_vs_energy.png");

    return 0;
}
