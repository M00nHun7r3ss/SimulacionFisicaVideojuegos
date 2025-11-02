#pragma once
#include <iostream>
#include <map> //Para usar map
#include <vector> //Para grupos de fuerzas
#include "ParticleSystem.h" //Pasara a ser particle system
#include "ForceGenerator.h"

class ParticleForceRegister
{
public:
	//Constructora
	ParticleForceRegister();

	//Destructora
	~ParticleForceRegister();

	//Repasa cada particula para ver su tipo de fuerzas
	void update();

private:

	//std::map<Particle*, ForceGenerator*> register;

};

