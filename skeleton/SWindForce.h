#pragma once
#include "SolidForceGenerator.h"
#include <PxRigidDynamic.h>

class SWindForce : public SolidForceGenerator
{
public:
	//Constructora
	SWindForce(const PxVec3& force);

	//Destructora
	~SWindForce() {}

	//Update
	void updateForce(PxRigidDynamic* solid, double t) override;

private:

	PxVec3 _force;
};

