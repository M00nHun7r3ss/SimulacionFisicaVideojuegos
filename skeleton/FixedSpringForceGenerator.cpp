#include "FixedSpringForceGenerator.h"

FixedSpringForceGenerator::FixedSpringForceGenerator(PxVec3 fixed, float k, float restLength) :
	_fixed(fixed), _k(k), _restLength(restLength)
{

}

void FixedSpringForceGenerator::updateForce(Particle* p, double dt)
{
    //Si no hay particula inactiva, nada
    if (!p->isActive()) return;

    //Vemos las posiciones
    PxVec3 pos1 = p->getPos();

    // Vector que va desde p hacia el otro extremo (direccion de fuerza)
    PxVec3 dir = _fixed - pos1;

    //Vemos la distancia
    float dist = dir.magnitude();
    if (dist <= 0.0001f) return;

    dir.normalize();

    float delta = dist - _restLength;

    // F = k * delta * dir
    PxVec3 force = dir * (delta * _k);

    p->addForce(force);

}

