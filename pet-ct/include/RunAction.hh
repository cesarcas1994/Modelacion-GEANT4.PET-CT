/*  Proyecto Fuente: Modelación básica de un PET-CT.

desarrolladores: César Castillo López
                 Daniel Izquierdo Díaz}
                 Raúl Escalona Gutierrez

 Creado en: Mayo 8, 2017        
*/
#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;



class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();
    
    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

