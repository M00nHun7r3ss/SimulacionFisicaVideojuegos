#include "SWindForce.h"

SWindForce::SWindForce(const PxVec3& force) :
	_force(force)
{
}

void SWindForce::updateForce(PxRigidDynamic* solid, double t)
{
	//Si no hay solido al que aplicarlo, no hace nada
	if (solid == nullptr) return;

	//Aniadimos la fuerza al solido con eFORCE
	//(de forma continua, teniendo en cuenta la masa)
	solid->addForce(_force, PxForceMode::eFORCE, true);
}
