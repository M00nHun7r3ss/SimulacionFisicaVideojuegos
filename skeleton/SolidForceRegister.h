#pragma once
#include <iostream>
#include <map> //Para usar map
#include <vector> //Para grupos de fuerzas
#include <PxRigidDynamic.h>

#include "SolidForceGenerator.h"

using namespace physx;

class SolidForceRegister
{
public:
	//Constructora
	SolidForceRegister() {}

	//Destructora
	~SolidForceRegister();

	//Repasa cada solido para ver su tipo de fuerzas
	void update(double t);

	//Aniade una entrada al registro
	void add(PxRigidDynamic* body, SolidForceGenerator* fGen);

	//Elimina una entrada del registro
	void remove(PxRigidDynamic* body, SolidForceGenerator* fGen);

	//Elimina el registro entero
	void clearRegister();

	//Elimina las fuerzas asociadas a un solido
	void clearSolid(PxRigidDynamic* body);

private:

	std::map<PxRigidDynamic*, std::vector<SolidForceGenerator*>> _forceRegister;

};

