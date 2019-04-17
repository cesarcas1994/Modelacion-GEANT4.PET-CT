/*  Proyecto Fuente: Modelación básica de un PET-CT.

desarrolladores: César Castillo López
                 Daniel Izquierdo Díaz}
                 Raúl Escalona Gutierrez

 Creado en: Mayo 8, 2017        
*/

#ifndef INCLUDE_PHYSICSLIST_HH_
#define INCLUDE_PHYSICSLIST_HH_

#include "G4VModularPhysicsList.hh"

class G4VPhysicsConstructor;

class PhysicsList: public G4VModularPhysicsList
{
public:
PhysicsList();
virtual ~PhysicsList();

// methods
virtual void ConstructParticle();
virtual void ConstructProcess();
virtual void SetCuts();

private:
G4double cutForGamma;
G4double cutForElectron;
G4double cutForPositron;
G4double cutForProton;

};



#endif /* INCLUDE_PHYSICSLIST_HH_ */

