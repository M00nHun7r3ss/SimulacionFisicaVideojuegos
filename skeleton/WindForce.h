#pragma once
#include "ForceGenerator.h"

class WindForce : public ForceGenerator
{
public:
	//Constructora basica
	WindForce(PxVec3& sWind, double k1 = 0.1, double k2 = 0.0,
		const PxVec3& minArea = PxVec3(-100, -100, -100),
		const PxVec3& maxArea = PxVec3(100, 100, 100));

	//Destructora
	~WindForce() {}

	void updateForce(Particle* p, double t) override;

private:

	double _k1; //Intensidad
	double _k2; //Turbulencia
	PxVec3 _windSpeed; //velocidad del viento
	PxVec3 _areaMin; //area minima de accion
	PxVec3 _areaMax; //area maxima de accion

	////Parte Opcional
	//double _pressure; //presion del viento (N / m*2)
	//double _density; //densidad del viento
};

