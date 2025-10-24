#pragma once
#include "ForceGenerator.h"

class GravityForce : public ForceGenerator
{
public:
	//Constructora
	GravityForce(double mass1, double mass2, double radius);

	//Destructora
	~GravityForce() {}

private:

	const double G = pow(6.67384, -11); //m^3 / kg * s^2
	double _mass2;
	double _radius;
};


