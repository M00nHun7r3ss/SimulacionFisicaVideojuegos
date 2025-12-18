#pragma once
#include "ForceGenerator.h"

class ExplosionForce : public ForceGenerator
{
public:
	//Constructora
	ExplosionForce(PxVec3& centerPos, double k , double radius, double duration);

	//Destructora
	~ExplosionForce() {}

	//Actualizacion de fuer<as
	void updateForce(Particle* p, double t) override;

protected:

	PxVec3 _centerPos; //Centro de explosion
	double _k; //intensidad
	double _radius; //radio de accion
	double _duration;
	double _elapsed;

};

