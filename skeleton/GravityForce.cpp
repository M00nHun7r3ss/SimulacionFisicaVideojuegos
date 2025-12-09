#include "GravityForce.h"

GravityForce::GravityForce(const PxVec3& gravedad) :
	_g(gravedad)
{
}

void GravityForce::updateForce(Particle* p, double t)
{
	//Ley de Gravedad Universal
	////Si no hay particula a la que aplicarlo, no hace nada
	//if (p == nullptr || !p->isActive()) return;

	////Radio distancia entre particulas
	//PxVec3 radiusDir = _pos2 - p->getPos();
	//double distance = radiusDir.magnitude();

	////Evitamos divisiones por 0
	//if (distance < 0.001) return;

	////Normalizamos la direccion de la fuerza
	//radiusDir.normalize();

	////Calculamos la fuerza
	//PxVec3 force = radiusDir * (G * p->getM() * _mass2 / (distance * distance));

	////Aniadimos la fuerza a la particula
	//p->addForce(force);

	//Si no hay particula a la que aplicarlo, no hace nada
	if (p == nullptr || !p->isActive()) return;

	//Aniadimos la fuerza a la particula (F = g * m)
	p->addForce(_g * p->getM());
}
