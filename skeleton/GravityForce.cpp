#include "GravityForce.h"

GravityForce::GravityForce(double mass2, PxVec3& pos2) :
	_mass2(mass2), _pos2(pos2)
{
}

void GravityForce::updateForce(Particle* p, double t)
{
	//Si no hay particula a la que aplicarlo, no hace nada
	if (p == nullptr || !p->isActive()) return;

	//Radio distancia entre particulas
	PxVec3 radiusDir = _pos2 - p->getPos();
	double distance = radiusDir.magnitude();

	//Evitamos divisiones por 0
	if (distance < 0.001) return;

	//Normalizamos la direccion de la fuerza
	radiusDir.normalize();

	//Calculamos la fuerza
	PxVec3 force = radiusDir * (G * p->getM() * _mass2 / (distance * distance));

	//Aniadimos la fuerza a la particula
	p->addForce(force);

}
