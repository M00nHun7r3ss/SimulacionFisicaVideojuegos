#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(Particle* a, Particle* b, float k, float restLength) :
    _a(a), _b(b), _k(k), _restLength(restLength)
{

}

void SpringForceGenerator::updateForce(Particle* p, double dt)
{
    //Si falta una de las particulas, nada
    if (!_a || !_b) return;

    //Si no hay particula inactiva, nada
    if (!p->isActive()) return;

    // Obtenemos quien es el otro extremo del muelle:
    Particle* other = (p == _a ? _b : _a);

    //Vemos las posiciones
    PxVec3 pos1 = p->getPos();
    PxVec3 pos2 = other->getPos();

    // Vector que va desde p hacia el otro extremo (direccion de fuerza)
    PxVec3 dir = pos2 - pos1;

    //Vemos la distancia
    float dist = dir.magnitude();
    if (dist <= 0.0001f) return;

    dir.normalize();  

    float delta = dist - _restLength;
    //No habra estiramiento si esta comprimida
    if (delta <= 0) return;

    // F = k * delta * dir
    PxVec3 force = dir * (delta * _k);

    p->addForce(force);
}
