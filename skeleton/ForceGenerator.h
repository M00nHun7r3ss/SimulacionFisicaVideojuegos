#pragma once

#include <math.h>
#include <PxPhysicsAPI.h> //Para usar Vector3
#include "Particle.h"
#include "RenderUtils.hpp"
#include "Vector3D.h" //TODO: cambiar luego
using namespace physx;

class ForceGenerator
{
public:

	//Constructora con masa y fuerza inicial
	ForceGenerator();

	//Destructora
	virtual ~ForceGenerator();

	//Actualiza la fuerza de la particula p
	virtual void updateForce(Particle* p, double t) = 0;
};

