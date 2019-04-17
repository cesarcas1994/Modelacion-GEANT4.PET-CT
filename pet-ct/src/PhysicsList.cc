/*  Proyecto Fuente: Modelación básica de un PET-CT.

desarrolladores: César Castillo López
                 Daniel Izquierdo Díaz}
                 Raúl Escalona Gutierrez

 Creado en: Mayo 8, 2017        
*/

#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4ParticleTypes.hh"

 //para gamma
#include "G4ComptonScattering.hh"
#include "G4KleinNishinaModel.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4RayleighScattering.hh"
#include "G4GammaConversion.hh"

//para electrones
#include "G4eBremsstrahlung.hh"
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"

//para positrones
#include "G4eplusAnnihilation.hh"

//para protones
#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"

//Generic Ion
#include "G4IonParametrisedLossModel.hh"
#include "G4ionIonisation.hh"

#include "G4StepLimiter.hh"
#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList()
{

	defaultCutValue  = 1.0*um;
	cutForGamma	= defaultCutValue;
	cutForElectron=defaultCutValue;
	cutForPositron=defaultCutValue;
	cutForProton = defaultCutValue;
}

PhysicsList::~PhysicsList(){}

void PhysicsList::ConstructParticle()
{
	//gamma
	G4Gamma::GammaDefinition();

	//lepton
	G4Electron::ElectronDefinition();
	G4Positron::PositronDefinition();

	//baryons
	G4Proton::ProtonDefinition();
	G4AntiProton::AntiProtonDefinition();
	//ions
	G4He3::He3();
	G4Alpha::Alpha();
	G4GenericIon::GenericIonDefinition();
}


void PhysicsList::ConstructProcess()
{
	AddTransportation();

	//ooooooooooooooooooo00000000000000000000*****************ConstructEM*********
	G4PhysicsListHelper* ph =G4PhysicsListHelper::GetPhysicsListHelper();
	auto particleIterator = GetParticleIterator();
		particleIterator->reset();

		while((*particleIterator)())
		{
			G4ParticleDefinition* particle = particleIterator->value();
			G4String particleName = particle->GetParticleName();

			if (particleName == "gamma")
			{
				ph->RegisterProcess(new G4RayleighScattering, particle);
				ph->RegisterProcess(new G4PhotoElectricEffect, particle);
				G4ComptonScattering* cs = new G4ComptonScattering;
				cs->SetEmModel(new G4KleinNishinaModel());
				ph->RegisterProcess(cs,particle);
				ph->RegisterProcess(new G4GammaConversion, particle);
			}

			else if (particleName=="e-")
					{
						ph-> RegisterProcess(new G4eMultipleScattering(), particle);

						G4eIonisation* eIoni = new  G4eIonisation();
						ph->RegisterProcess(eIoni,particle);

						ph->RegisterProcess(new G4eBremsstrahlung(), particle);

					}

			else if (particleName=="e+")
		{
			ph-> RegisterProcess(new G4eMultipleScattering(), particle);

			G4eIonisation* eIoni = new  G4eIonisation();
			ph->RegisterProcess(eIoni,particle);

			ph->RegisterProcess(new G4eBremsstrahlung(), particle);

			ph->RegisterProcess(new G4eplusAnnihilation(), particle);

		}
			else if (particleName=="proton")
					{
						ph-> RegisterProcess(new G4hMultipleScattering(), particle);
						ph-> RegisterProcess(new G4hIonisation(),particle);

					}
			else if (particleName=="alpha" ||
									"He3")
								{
									ph-> RegisterProcess(new G4hMultipleScattering(),particle);
								//	ph-> RegisterProcess(new G4ionIonisation(),particle);

								}
			else if (particleName=="GenericIon")
								{
									ph-> RegisterProcess(new G4hMultipleScattering("ionmsc"), particle);
									G4ionIonisation* ionIoni = new G4ionIonisation();
									ionIoni->SetEmModel(new G4IonParametrisedLossModel());
									ph->RegisterProcess(ionIoni, particle);
								}

}
}
void PhysicsList::SetCuts()
{
	G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100*eV,1*GeV);
	SetCutValue(defaultCutValue, "gamma");
	SetCutValue(cutForElectron, "e-");
	SetCutValue(cutForPositron, "e+");
	SetCutValue(cutForProton, "proton");




}





