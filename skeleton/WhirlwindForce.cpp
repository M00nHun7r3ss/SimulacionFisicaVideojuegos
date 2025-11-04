#include "WhirlwindForce.h"

WhirlwindForce::WhirlwindForce(PxVec3 center, double k, double radius, double density, double dragCoef, double area)
	: WindForce(PxVec3(0, 0, 0), density, dragCoef, area), _centerPos(center), _k(k), _radius(radius)

{
}

void WhirlwindForce::updateForce(Particle* p, double t)
{
	//Si no hay particula o esta inactiva, no hacemos nada
	if (p == nullptr || !p->isActive()) return;

	//Veremos la distancia de la particula al centro
	PxVec3 particlePos = p->getPos();
	PxVec3 distance = particlePos - _centerPos;

	//Si la particula esta fuera del radio no se vera afectada
	if (distance.magnitude() > _radius) return;

	//Formula del enunciado para velocidad
	PxVec3 windSpeed(
		-_k * (particlePos.z - _centerPos.z),
		_k * (50 - (particlePos.y - _centerPos.y)),
		_k * (particlePos.x - _centerPos.x)
	);

	//Diferencia de velocidad
	PxVec3 speedDiff = windSpeed - p->getV();
	//Si no hay velocidad, no hay efecto
	if (speedDiff.magnitude() == 0) return;

	//Dicha velocidad sera tambien la direccion del movimiento
	PxVec3 direction = speedDiff.getNormalized();

	//Calculo de la fuerza
	PxVec3 force = direction * (0.5 * _airDensity * _dragCoef * _area
		* speedDiff.magnitude() * speedDiff.magnitude());

	//Aplicamos la fuerza
	p->addForce(force);
}
