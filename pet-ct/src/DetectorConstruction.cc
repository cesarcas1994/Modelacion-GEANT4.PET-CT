/*  Proyecto Fuente: Modelación básica de un PET-CT.

desarrolladores: César Castillo López
                 Daniel Izquierdo Díaz}
                 Raúl Escalona Gutierrez

 Creado en: Mayo 8, 2017        
*/
#include "DetectorConstruction.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"




DetectorConstruction::DetectorConstruction():
worldMat(0), targetMat(0), detectorMat(0)
{
         DefineMaterials();
}
DetectorConstruction::~DetectorConstruction(){}

void DetectorConstruction::DefineMaterials()
{
	G4double z, a;
	G4double temperature, pressure;
	G4double density;

	density = universe_mean_density;
	pressure = 3.e-18*pascal;
	temperature = 2.73*kelvin;

	G4Material* vacuum = new G4Material("Galactic", z=1., a=1.01*g/mole, density, kStateGas, temperature, pressure);


	G4NistManager* man = G4NistManager::Instance();

	  G4bool isotopes = false;

	  G4Element* H = man->FindOrBuildElement("H" , isotopes);
	  G4Element* C = man->FindOrBuildElement("C", isotopes);
	  G4Element* N = man->FindOrBuildElement("N", isotopes);
	  G4Element* O = man->FindOrBuildElement("O", isotopes);
	  G4Element* Na = man->FindOrBuildElement("Na", isotopes);
	  G4Element* S = man->FindOrBuildElement("S", isotopes);
	  G4Element* Cl = man->FindOrBuildElement("Cl", isotopes);
	  G4Element* Lu = man->FindOrBuildElement("Lu", isotopes);


	  G4Material* tejadiposo = new G4Material("adiposo", 0.95*g/cm3, 8);
	  tejadiposo->AddElement(H, 0.114);
	  tejadiposo->AddElement(C, 0.598);
	  tejadiposo->AddElement(N , 0.007);
	  tejadiposo->AddElement(O , 0.278);
	  tejadiposo->AddElement(Na , 0.001);
	  tejadiposo->AddElement(S , 0.001);
	  tejadiposo->AddElement(Cl , 0.0005);
	  tejadiposo->AddElement(Lu , 0.0005);

	worldMat = vacuum;
	detectorMat = tejadiposo;


}
G4VPhysicalVolume*DetectorConstruction::Construct(){
  G4double worldx=100*cm;
  G4double worldy=100*cm;
  G4double worldz=100*cm;
  G4NistManager* nist = G4NistManager::Instance();

  G4Material* default_mat = nist->FindOrBuildMaterial("G4_AIR");
 /* G4Material* water = nist->FindOrBuildMaterial("G4_WATER");
  G4Material* graf = nist->FindOrBuildMaterial("G4_GRAPHITE");
  G4Material* lung = nist->FindOrBuildMaterial("G4_LUNG_ICRP");*/

  G4Box* solidWorld = new G4Box("world", worldx, worldy, worldz);
  G4LogicalVolume* logicalWorld = new G4LogicalVolume(solidWorld, default_mat,"world");
  G4VPhysicalVolume* physicalWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalWorld, "world", 0, false, 0, true);

  //G4double targetx=0.5*cm;
  //G4double targety=0.5*cm;
  //G4double targetz=1*um;
  //G4Box* solidTarget = new G4Box("target",targetx,targety,targetz);
  // G4LogicalVolume* logicalTarget = new G4LogicalVolume(solidTarget, targetMat,"target");
  // G4VPhysicalVolume* physicalTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalTarget, "target", logicalWorld, false, 0, true);


  G4double distancia_x  =10*cm;
  G4double distancia_y  =10*cm;
  G4double distancia_z  =5*cm;

 /* G4double ddistancia_x  = 0.2*cm;
  G4double ddistancia_y  = 1.00*cm;
  G4double ddistancia_z  = 0.2*cm;*/

 // G4double radioBlockDetector = 41.1*cm;
 // G4double deltaangle = 7.5*degree;


  G4Box* eDetector = new G4Box("crystal",distancia_x,distancia_y,distancia_z);
  //G4double angle=0;
  G4LogicalVolume* logiceDetector= new G4LogicalVolume(eDetector, detectorMat,"Logiccrystal");
  new G4PVPlacement(0,G4ThreeVector(0., 0., -5*cm), logiceDetector, "crystal", logicalWorld, false, 0, true);


  /*G4Box* sDetector = new G4Box("small_solidbox",ddistancia_x,ddistancia_y,ddistancia_z);
  G4LogicalVolume* logicsDetector = new G4LogicalVolume(sDetector, detectorMat,"LVsmall_solidbox");
  G4int copyNo=0;*/

  /*for(G4double z = -2.60+0.2; z <= 2.60-0.2; z+=0.4 )
  {
  		  for(G4double x = -2.60+0.2; x <= 2.60-0.2; x+=0.4 )
  		  {
  			  new G4PVPlacement(0,G4ThreeVector(x*cm,0.,z*cm), logicsDetector, "small_solidbox", logiceDetector, false, copyNo, true);
  			  ++copyNo;
  		  }

  }*/






 /* for (G4int detect = 0; detect < 48; ++ detect )
  {
	  angle = detect*deltaangle;
	  G4RotationMatrix* rotm = new G4RotationMatrix();
	  rotm->rotateX(-angle);
	  for (G4int i=0; i<8; ++i)
	  new G4PVPlacement(rotm,G4ThreeVector((-18.2+i*5.2)*cm,radioBlockDetector*cos(angle),radioBlockDetector*sin(angle)), logiceDetector, "crystal", logicalWorld, false, detect, fCheckOverlaps);

  }*/

  /*  G4double patient_radius = 10.15*cm;
    G4double patient_dZ = 70*cm;
    G4Material* patient_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

    G4Tubs* solidPatient =
      new G4Tubs("Patient", 0., patient_radius, 0.5*patient_dZ, 0., twopi);

    G4LogicalVolume* logicPatient =
      new G4LogicalVolume(solidPatient,        //its solid
                          patient_mat,         //its material
                          "Patient");        //its name

    G4Tubs* cavity =
         new G4Tubs("cavity", 0., 0.32*cm, 0.5*patient_dZ, 0., twopi);

    G4LogicalVolume* logiccavity =
          new G4LogicalVolume(cavity,        //its solid
                              default_mat,         //its material
                              "cavity");        //its name



    G4RotationMatrix* rotm1 = new G4RotationMatrix();
    	  rotm1->rotateY(-90*degree);
    // place patient in world

    new G4PVPlacement(rotm1,                       //no rotation
                      G4ThreeVector(),         //at (0,0,0)
                      logicPatient,            //its logical volume
                      "Patient",               //its name
                      logicalWorld,              //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      true);         // checking overlaps

    new G4PVPlacement(0,                       //no rotation
                          G4ThreeVector(0.,0.,0.),         //at (0,0,0)
                          logiccavity,            //its logical volume
                          "cavity",               //its name
                          logicPatient,              //its mother  volume
                          false,                   //no boolean operation
                          0,                       //copy number
                          true);         // checking overlaps

    G4double distancia_xx=100*cm;
	G4double distancia_yy=1.5*cm;
	G4double distancia_zz=21*cm;
	G4Material* bedMat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");

	G4Box* bed = new G4Box("bed",distancia_xx,distancia_yy,distancia_zz);
	 G4LogicalVolume* logicbed =
	          new G4LogicalVolume(bed,        //its solid
	                              bedMat,         //its material
	                              "bed");        //its name
	 new G4PVPlacement(0,                       //no rotation
	                           G4ThreeVector(0.,-11.65*cm,0.),         //at (0,0,0)
	                           logicbed,            //its logical volume
	                           "bed",               //its name
	                           logicalWorld,              //its mother  volume
	                           false,                   //no boolean operation
	                           0,                       //copy number
	                           true);         // checking overlaps


  //logiceDetector->SetVisAttributes (G4VisAttributes::GetInvisible());

*/
  return physicalWorld;

}

void DetectorConstruction::ConstructSDandField()
  {
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

    // declare crystal as a MultiFunctionalDetector scorer

    G4MultiFunctionalDetector* cryst = new G4MultiFunctionalDetector("crystal");
    G4SDManager::GetSDMpointer()->AddNewDetector(cryst);
    G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("edep");
    cryst->RegisterPrimitive(primitiv1);
    SetSensitiveDetector("Logiccrystal",cryst);


  }


