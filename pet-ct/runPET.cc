#include "G4RunManager.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "PhysicsList.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "RunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
//.......oooOOOOooooo Construct the default run manager ooOOOOooooo.............
G4RunManager* runManager = new G4RunManager;

//Set mandatory initialization classes

runManager->SetUserInitialization(new DetectorConstruction); // Detector Construction
runManager->SetUserInitialization(new PhysicsList); //Physics List

//G4VModularPhysicsList* physicsList = new PhysicsList;
//physicsList->SetVerboseLevel(1);
//runManager->SetUserInitialization(physicsList);
// Set mandatory user action class
runManager->SetUserAction(new PrimaryGeneratorAction);
runManager->SetUserAction(new RunAction);

//initialize G4 kernel
runManager->Initialize();


//...........oooOOOOooooo Initialize visualization ooOOOOooooo..................
G4UImanager* UImanager = G4UImanager::GetUIpointer();
G4UIExecutive* ui = 0;
if (argc == 1)
{
	ui = new G4UIExecutive(argc, argv);
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	UImanager->ApplyCommand("/control/execute vis.mac");
	ui->SessionStart();
	delete ui;
	}
//.............oooOOOOooooo End of visualization ooOOOOooooo....................
else
{
	G4String file=argv[1];
	UImanager->ApplyCommand("/control/execute "+file);
}
	// Job termination
  delete runManager;
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
