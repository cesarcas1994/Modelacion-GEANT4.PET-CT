/*  Proyecto Fuente: Modelación básica de un PET-CT.

desarrolladores: César Castillo López
                 Daniel Izquierdo Díaz}
                 Raúl Escalona Gutierrez

 Creado en: Mayo 8, 2017        
*/
#ifndef Run_h
#define Run_h 1

#include "G4Run.hh"
#include "globals.hh"



class Run : public G4Run
{
  public:
    Run();
    virtual ~Run();

    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);

  public:
    G4int GetNbGoodEvents() const { return fGoodEvents; }
    G4int GetNbScatterEvents() const { return fScatterEvents; }


  private:
    G4int fCollID_cryst;
    G4int fPrintModulo;
    G4int fGoodEvents;
    G4int fScatterEvents;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


