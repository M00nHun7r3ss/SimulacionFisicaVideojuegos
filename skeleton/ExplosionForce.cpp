#include "ExplosionForce.h"

ExplosionForce::ExplosionForce(PxVec3& centerPos, double k, double radius, double duration) :
_centerPos(centerPos), _k(k), _radius(radius), _duration(duration)
{}

void ExplosionForce::updateForce(Particle * p, double t)
{
    //Si no hay particula o esta inactiva, no hacemos nada
    if (p == nullptr || !p->isActive()) return;

    //Veremos la distancia de la particula al centro
    PxVec3 particlePos = p->getPos();
    PxVec3 direction = particlePos - _centerPos;

    //Si la particula esta fuera del radio no se vera afectada
    if (direction.magnitude() > _radius) return;

    //La explosion se disipa con el tiempo
    double withTime = max(0.0, 1.0 - t / _duration);

    //La explosion sera mas fuerte cuanto mas cerca del centro
    double withDistance = max(0.0, 1.0 - direction.magnitude() / _radius);

    //Calculo de la fuerza
    PxVec3 force = direction * (_k * withTime * withDistance);

    //Aplicamos la fuerza
    p->addForce(force);
}
