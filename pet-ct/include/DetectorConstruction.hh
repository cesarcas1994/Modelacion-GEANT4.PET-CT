/*  Proyecto Fuente: Modelación básica de un PET-CT.

desarrolladores: César Castillo López
                 Daniel Izquierdo Díaz}
                 Raúl Escalona Gutierrez

 Creado en: Mayo 8, 2017        
*/


#ifndef INCLUDE_DETECTORCONSTRUCTION_HH_
#define INCLUDE_DETECTORCONSTRUCTION_HH_

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Material;
class G4VPhysicalVolume;
class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
DetectorConstruction();
virtual ~DetectorConstruction();


public:
virtual G4VPhysicalVolume* Construct();
virtual void ConstructSDandField();


private:
void DefineMaterials();
G4Material* worldMat;
G4Material* targetMat;
G4Material* detectorMat;
G4bool  fCheckOverlaps;

};



#endif /* INCLUDE_DETECTORCONSTRUCTION_HH_ */
