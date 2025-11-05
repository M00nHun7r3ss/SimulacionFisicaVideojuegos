#pragma once
#include "ForceGenerator.h"

class GravityForce : public ForceGenerator
{
public:
	//Constructora
	GravityForce(double mass2, PxVec3& pos2);

	//Destructora
	~GravityForce() {}

	//Update
	void updateForce(Particle* p, double t) override;

private:

	const double G = 6.67384e-11;; //m^3 / kg * s^2
	double _mass2;
	PxVec3 _pos2;
};


