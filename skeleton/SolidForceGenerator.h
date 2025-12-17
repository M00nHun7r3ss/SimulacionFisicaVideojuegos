#pragma once

#include <math.h>
#include <PxPhysicsAPI.h> //Para usar Vector3
#include <PxRigidDynamic.h>
#include "RenderUtils.hpp"

using namespace physx;

class SolidForceGenerator
{
public:

	//Constructora con masa y fuerza inicial
	SolidForceGenerator() {}

	//Destructora
	virtual ~SolidForceGenerator() {}

	//Actualiza la fuerza del solido solid
	virtual void updateForce(PxRigidDynamic* solid, double t) = 0;
};

