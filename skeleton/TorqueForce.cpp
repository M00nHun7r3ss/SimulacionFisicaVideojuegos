#include "TorqueForce.h"

TorqueForce::TorqueForce(const PxVec3& force, const PxVec3& pointA, const PxVec3& pointB)
    : _force(force), _pointA(pointA), _pointB(pointB)
{
}

void TorqueForce::updateForce(PxRigidDynamic* solid, double t)
{
    //Si no hay solido al que aplicarlo, no hace nada
    if (solid == nullptr) return;

    // Aplicamos la fuerza en el primer punto
    PxRigidBodyExt::addForceAtPos(*solid, _force, _pointA, PxForceMode::eFORCE, true);

    // Aplicamos la fuerza opuesta en el segundo punto
    PxRigidBodyExt::addForceAtPos(*solid, -_force, _pointB, PxForceMode::eFORCE, true);
}

