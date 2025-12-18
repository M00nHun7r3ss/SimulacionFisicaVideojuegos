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
//PRACTICA 1
#include "Particle.h" 

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
Scene0* gameScene = NULL;

int lives = 3;
int points = 0;

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
	gameScene = new Scene0(gMaterial, gPhysics, gScene);
	gSceneManager->addScene(gameScene);

    // Activar la primera escena
    gSceneManager->setActive(0);

	//Escribimos las vidas y los puntos por pantalla
	if (gSceneManager->getActiveScene() == gameScene)
	{
		lives = gameScene->getPlayerLives();
		points = gameScene->getPlayerPoints();
		//Actualiza los textos de puntos y vida
		drawText("Lives: " + std::to_string(lives), 5, 0);
		drawText("Points: " + std::to_string(points), 30, 0);
	}
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

	//Colocamos la camara para que siga al jugador. El jugador estará centrado en pantalla 
	if (gSceneManager->getActiveScene() == gameScene)
	{
		//Camara 3era persona
		PxVec3 offset(0, 5, 0);
		GetCamera()->setEye(gameScene->getPlayerPos() + offset);

		// Direccion hacia el jugador
		PxVec3 toPlayer = (gameScene->getPlayerPos() - GetCamera()->getEye()).getNormalized();

		// Peso de influencia de direcciones
		double frontWeight = 0.7;   
		double playerWeight = 0.3;

		GetCamera()->setDir((gameScene->getPlayerFront() * frontWeight + toPlayer * playerWeight).getNormalized());

		//Actualiza los textos de puntos y vida
		lives = gameScene->getPlayerLives();
		points = gameScene->getPlayerPoints();
		drawText("Lives: " + std::to_string(lives), 5, 0);
		drawText("Points: " + std::to_string(points), 30, 0);
	}


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
		gSceneManager->setActive(0); // Practica 4
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