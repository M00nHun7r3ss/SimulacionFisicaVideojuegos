#pragma once
#include "WindForce.h"

class WhirlwindForce : public WindForce
{
public:
	//Constructora
	WhirlwindForce(PxVec3 center, double k, double radius,
		double density, double dragCoef, double area);

	//Destructora
	~WhirlwindForce() {}

	//Actualizacion de fuer<as
	void updateForce(Particle* p, double t) override;

private:

	PxVec3 _centerPos; //Centro del torbellino
	double _k; //intensidad
	double _radius; //radio de accion


};

