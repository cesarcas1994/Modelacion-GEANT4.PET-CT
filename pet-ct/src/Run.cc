/*  Proyecto Fuente: Modelación básica de un PET-CT.

desarrolladores: César Castillo López
                 Daniel Izquierdo Díaz}
                 Raúl Escalona Gutierrez

 Creado en: Mayo 8, 2017        
*/
#include "Run.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Run::Run()
 : G4Run(),
   fCollID_cryst(-1),
   fPrintModulo(10000),
   fGoodEvents(0),
   fScatterEvents(0)

{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Run::~Run()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Run::RecordEvent(const G4Event* event)
{
  if ( fCollID_cryst < 0 ) {
   fCollID_cryst
     = G4SDManager::GetSDMpointer()->GetCollectionID("crystal/edep");
   //G4cout << " fCollID_cryst: " << fCollID_cryst << G4endl;
  }


  G4int evtNb = event->GetEventID();

  if (evtNb%fPrintModulo == 0) {
    G4cout << G4endl << "---> end of event: " << evtNb << G4endl;
  }

  //Hits collections
  //
  G4HCofThisEvent* HCE = event->GetHCofThisEvent();
  if(!HCE) return;

  //Energy in crystals : identify 'good events'
  //
  const G4double eThreshold = 500*keV;
  G4int nbOfFired = 0;

  G4THitsMap<G4double>* evtMap =
    static_cast<G4THitsMap<G4double>*>(HCE->GetHC(fCollID_cryst));

  std::map<G4int,G4double*>::iterator itr;
  for (itr = evtMap->GetMap()->begin(); itr != evtMap->GetMap()->end(); itr++) {
    G4double edep = *(itr->second);
    if (edep > eThreshold) nbOfFired++;
    ///G4int copyNb  = (itr->first);
    ///G4cout << G4endl << "  cryst" << copyNb << ": " << edep/keV << " keV ";
  }
  if (nbOfFired == 2) fGoodEvents++;

  //Energy in crystals : identify 'scatter events'
    //
    const G4double eThreshold1 = 200*keV;

    G4int nbOfFired1 = 0;

    G4THitsMap<G4double>* evtMap1 =
      static_cast<G4THitsMap<G4double>*>(HCE->GetHC(fCollID_cryst));

    std::map<G4int,G4double*>::iterator itr1;
    for (itr1 = evtMap1->GetMap()->begin(); itr1 != evtMap1->GetMap()->end(); itr1++)
    {
      G4double edep = *(itr1->second);
      if (edep > eThreshold1) nbOfFired1++;
      ///G4int copyNb  = (itr->first);
      ///G4cout << G4endl << "  cryst" << copyNb << ": " << edep/keV << " keV ";

    }
    if (nbOfFired1 == 2) fScatterEvents++;


  G4Run::RecordEvent(event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Run::Merge(const G4Run* aRun)
{
  const Run* localRun = static_cast<const Run*>(aRun);
  fGoodEvents += localRun->fGoodEvents;
  fScatterEvents += localRun->fScatterEvents;


  G4Run::Merge(aRun);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
