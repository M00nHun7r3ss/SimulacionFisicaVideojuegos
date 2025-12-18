#include "ExplosionForce.h"

ExplosionForce::ExplosionForce(PxVec3& centerPos, double k, double radius, double duration) :
_centerPos(centerPos), _k(k), _radius(radius), _duration(duration), _elapsed(0)
{}

void ExplosionForce::updateForce(Particle * p, double t)
{
	//Si no hay particula, no podemos seguir
	if (!p || !p->isActive()) return;

	//Avanzamos el tiempo
	_elapsed += t;
	//Si se termina, no podemos seguir
	if (_elapsed > _duration) return;

	//Direccion
	PxVec3 dir = p->getPos() - _centerPos;
	//Distancia
	double dist = dir.magnitude();

	//Correcion
	if (dist <= 0.0001 || dist > _radius) return;

	dir.normalize();

	//Calculamos la fuerza
	double force = _k * (1.0 - dist / _radius);

	p->addForce(dir * force);
}
