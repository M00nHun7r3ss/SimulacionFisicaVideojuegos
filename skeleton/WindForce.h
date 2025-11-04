#pragma once
#include "ForceGenerator.h"

class WindForce : public ForceGenerator
{
public:
	//Constructora basica
	WindForce(PxVec3& sWind, double k1 = 0.1, double k2 = 0.0,
		const PxVec3& minArea = PxVec3(-100, -100, -100),
		const PxVec3& maxArea = PxVec3(100, 100, 100));

	//Constructora opcional
	WindForce(PxVec3& sWind, double density = 1.2, double dragCoef = 0.5,
		double area = 0.1,
		const PxVec3& minArea = PxVec3(-100, -100, -100),
		const PxVec3& maxArea = PxVec3(100, 100, 100));

	//Destructora
	~WindForce() {}

	void updateForce(Particle* p, double t) override;

private:

	PxVec3 _windSpeed; //velocidad del viento
	double _k1; //Intensidad
	double _k2; //Turbulencia
	PxVec3 _areaMin; //area minima de accion
	PxVec3 _areaMax; //area maxima de accion

	//extras Opcional
	double _airDensity;   // densidad
	double _dragCoef ;    // coeficiente aerodinamico
	double _area;         // en m^2

};

