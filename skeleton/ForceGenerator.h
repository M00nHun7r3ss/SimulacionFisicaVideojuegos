#pragma once

#include <math.h>
#include <PxPhysicsAPI.h> //Para usar Vector3
#include "RenderUtils.hpp"
#include "Vector3D.h" //TODO: cambiar luego
using namespace physx;

class ForceGenerator
{
public:

	//Constructora con masa y fuerza inicial
	ForceGenerator(double mass = 1.0);

	//Destructora
	virtual ~ForceGenerator() = 0;

	//Getters
	inline PxVec3* getForce() { return _force; };
	inline double getMass() { return _mass; }

	//Setters
	inline void setForce(PxVec3* force) { _force = force; };
	inline void setMass(double m) { _mass = m; }

protected:

	PxVec3* _force; //En N (kg * m / s^2)
	double _mass; //en kg

};

