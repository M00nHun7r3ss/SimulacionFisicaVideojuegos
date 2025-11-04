#include "WindForce.h"

WindForce::WindForce(PxVec3& sWind, double k1, double k2, const PxVec3& minArea, const PxVec3& maxArea)
	: _windSpeed(sWind), _k1(k1), _k2(k2), _areaMin(minArea), _areaMax(maxArea)
{
}

WindForce::WindForce(PxVec3& sWind, double density, double dragCoef, double area, const PxVec3& minArea, const PxVec3& maxArea)
	: _windSpeed(sWind), _airDensity(density), _dragCoef(dragCoef), _area(area), _areaMin(minArea), _areaMax(maxArea)
{
}

void WindForce::updateForce(Particle* p, double t)
{
	//Lo mismo de siempre. Si no hay particula o esta inactiva, no hacemos nada
	if (p == nullptr || !p->isActive()) return;

	//Solo aplicaremos la fuerza si esta en el area determinado
	PxVec3 particlePos = p->getPos();
	if (particlePos.x < _areaMin.x || particlePos.y < _areaMin.y || particlePos.z < _areaMin.z ||
		particlePos.x > _areaMax.x || particlePos.y > _areaMax.y || particlePos.z > _areaMax.z)
		return;

	//Diferencia de velocidades
	PxVec3 speedDiff = _windSpeed - p->getV();
	//Si no hay diferencia, el viento no hace nada
	if (speedDiff.magnitude() == 0) return;

	//Si queremos el viento basico descomentar esto

	////Calculo de la fuerza
	//PxVec3 force = _k1 * speedDiff + _k2 * speedDiff.magnitude() * speedDiff;

	//------ fin viento basico

	//Si queremos el viento avanzado descomentar esto
	PxVec3 direction = speedDiff.getNormalized();

	PxVec3 force = direction * (0.5 * _airDensity * _dragCoef * _area 
		* speedDiff.magnitude() * speedDiff.magnitude());

	//------ fin viento avanzado

	//Aplicamos la fuerza
	p->addForce(force);

}
