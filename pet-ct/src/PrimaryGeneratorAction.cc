/*  Proyecto Fuente: Modelación básica de un PET-CT.

desarrolladores: César Castillo López
                 Daniel Izquierdo Díaz}
                 Raúl Escalona Gutierrez

 Creado en: Mayo 8, 2017        
*/
#include "PrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ChargedGeantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4PhysicalConstants.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
  /*G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle
                    = particleTable->FindParticle("chargedgeantino");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  fParticleGun->SetParticleEnergy(1*eV);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));*/

  G4int numberOfBullets = 1;
  G4int energy = 1;
		G4ParticleDefinition* TypeOfParticle = G4ParticleTable::GetParticleTable()->FindParticle("photos");
		fParticleGun= new G4ParticleGun(numberOfBullets);
		fParticleGun->SetParticleDefinition(TypeOfParticle);
		fParticleGun->SetParticleEnergy(energy*GeV);
		fParticleGun->SetParticleMomentumDirection(G4ThreeVector (0.,0.,-1.));
		fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 // G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
 /* if (particle == G4ChargedGeantino::ChargedGeantino())
  {
    //fluorine
    G4int Z = 9, A = 18;
    G4double ionCharge   = 0.*eplus;
    G4double excitEnergy = 0.*keV;

    G4ParticleDefinition* ion
       = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(ionCharge);
  }*/


  G4double x0  = 0.*mm;
  G4double y0  = 0.*mm;
  G4double z0  = 0.*mm;
//  G4double r = 3.2*mm*G4UniformRand();
//  G4double angle = G4UniformRand()*2*pi;
  G4double dz = 100.*mm;

 // z0 = r*(cos(angle));
 // y0 = r*(sin(angle));
  y0 = dz*(G4UniformRand()-0.5);
  x0 = dz*(G4UniformRand()-0.5);


  /*G4cout<<" x0 "<<x0<<" y0 "<<y0<<" z0 "<<z0<<G4endl;
  G4cout<<" r "<<r<<" angulo "<<angle<<G4endl;*/

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  //create vertex
  //
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

