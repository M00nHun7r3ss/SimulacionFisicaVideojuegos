#include <ctype.h>
#include <execution>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

//GESTION DE ESCENAS
#include "SceneManager.h" 
#include "Scene.h"
//PRACTICA 0
#include "Vector3D.h"
//PRACTICA 1
#include "Particle.h" 
//PRACTICA 2
#include "Proyectil.h" 
#include "ParticleGenerator.h" 
#include "GaussParticleGenerator.h" 
#include "UniformParticleGenerator.h" 
#include "ParticleSystem.h" 
//PRACTICA 3
#include "GravityForce.h"
#include "WindForce.h" 
#include "WhirlwindForce.h" 

std::string display_text = "";

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

//GESTION DE ESCENAS
SceneManager* gSceneManager = NULL;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);


	//Creamos escenas
	gSceneManager = new SceneManager();

	//Las aniadimos en el manager
	//gSceneManager->addScene(new Scene0(gMaterial));
	//gSceneManager->addScene(new Scene1());
	//gSceneManager->addScene(new Scene2());
	gSceneManager->addScene(new Scene3(gMaterial));

    // Activar la primera escena
    gSceneManager->setActive(0);

}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	// Actualiza la escena activa
	gSceneManager->update(t);

}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------

	//Borramos el manager
	gSceneManager->cleanup();
	delete gSceneManager;
	gSceneManager = nullptr;

	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
}


// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case ' ':
	{
		break;
	}
		//Las escenas llevan numeros
	case '0':
		gSceneManager->setActive(0); // Practica 0
		break;
	case '1':
		gSceneManager->setActive(1); // Practica 1
		break;
	case '2':
		gSceneManager->setActive(2); // Practica 2 y 3
		break;
	case '3':
		gSceneManager->setActive(3); // Proyecto Intemedio
		break;

	default:
		break;
	}

	// Si existe una escena activa, le pasamos el input para que lo maneje
	if (gSceneManager != nullptr && gSceneManager->getActiveScene() != nullptr)
	{
		gSceneManager->getActiveScene()->handleKey(key, camera);
	}

}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}