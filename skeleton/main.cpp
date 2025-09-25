#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "Vector3D.h"

std::string display_text = "This is a test";


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

// PRACTICA 0
RenderItem* sp1 = NULL;
RenderItem* spX = NULL;
RenderItem* spY = NULL;
RenderItem* spZ = NULL;


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


	// PRACTICA 0
	//Creamos la geometria de la esfera (con radio 0)
	PxGeometry* sphereGeo = new PxSphereGeometry(1.0);
	//Creamos la forma con la geometria
	PxShape* sphere0 = CreateShape(*sphereGeo, gMaterial);
	//Creamos el transform, y el color
	Vector3D pos(0.0, 0.0, 0.0);
	PxTransform* tr = new PxTransform(PxVec3(pos.getX(), pos.getY(), pos.getZ()));
	Vector4* color = new Vector4{ 1.0, 1.0, 1.0, 1.0 };
	//Renderizamos la esfera
	sp1 = new RenderItem(sphere0, tr, *color);
	//La registramos
	RegisterRenderItem(sp1);

	//---- Eje rojo x
	//Creamos la forma con la geometria
	PxShape* sphereX = CreateShape(*sphereGeo, gMaterial);
	Vector3D posX(10.0, 0.0, 0.0);
	PxTransform* trX = new PxTransform(PxVec3(posX.getX(), posX.getY(), posX.getZ()));
	Vector4* rojo = new Vector4{ 1.0, 0.0, 0.0, 1.0 };
	//Renderizamos la esfera
	spX = new RenderItem(sphereX, trX, *rojo);
	//La registramos
	RegisterRenderItem(spX);

	//---- Eje verde y
	//Creamos la forma con la geometria
	PxShape* sphereY = CreateShape(*sphereGeo, gMaterial);
	Vector3D posY(0, 10.0, 0);
	PxTransform* trY = new PxTransform(PxVec3(posY.getX(), posY.getY(), posY.getZ()));
	Vector4* verde = new Vector4{ 0.0, 1.0, 0.0, 1.0 };
	//Renderizamos la esfera
	spY = new RenderItem(sphereY, trY, *verde);
	//La registramos
	RegisterRenderItem(spY);

	//---- Eje azul z
	//Creamos la forma con la geometria
	PxShape* sphereZ = CreateShape(*sphereGeo, gMaterial);
	Vector3D posZ(0.0, 0.0, 10.0);
	PxTransform* trZ = new PxTransform(PxVec3(posZ.getX(), posZ.getY(), posZ.getZ()));
	Vector4* azul = new Vector4{ 0.0, 0.0, 1.0, 1.0 };
	//Renderizamos la esfera
	spZ = new RenderItem(sphereZ, trZ, *azul);
	//La registramos
	RegisterRenderItem(spZ);

}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);


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

	// PRACTICA 0
	//Las desregistramos
	DeregisterRenderItem(sp1);
	DeregisterRenderItem(spX);
	DeregisterRenderItem(spY);
	DeregisterRenderItem(spZ);

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
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{
		break;
	}
	default:
		break;
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