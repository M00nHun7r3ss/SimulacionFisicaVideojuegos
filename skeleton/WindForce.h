#pragma once
#include "ForceGenerator.h"

class WindForce : public ForceGenerator
{
public:
	//Constructora
	WindForce(double cDyn, double cStat, PxVec3* sObj, PxVec3* sWind, PxVec2* area);

	//Destructora
	~WindForce() {}

private:

	double _coefD; //Coeficiente dinamico
	double _coefS; //Coeficiente estatico
	PxVec3* _speedObj; //velocidad del objeto
	PxVec3* _speedWind; //velocidad del viento
	PxVec2* _area; //area 
	double _pressure; //presion del viento (N / m*2)
	double _density; //densidad del viento
};

