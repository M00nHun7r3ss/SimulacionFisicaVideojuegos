#pragma once
#include <iostream>
#include <map> //Para usar map
#include <vector> //Para grupos de fuerzas
#include "Particle.h" 
#include "ForceGenerator.h"

class ParticleForceRegister
{
public:
	//Constructora
	ParticleForceRegister() {}

	//Destructora
	~ParticleForceRegister();

	//Repasa cada particula para ver su tipo de fuerzas
	void update(double t);

	//Aniade una entrada al registro
	void add(Particle* p, ForceGenerator* fGen);

	//Elimina una entrada del registro
	void remove(Particle* p, ForceGenerator* fGen);

	//Elimina el registro entero
	void clearRegister();

	//Elimina las fuerzas asociadas a una particula (para despues de integrar)
	void clearParticle(Particle* p);

private:

	std::map<Particle*, std::vector<ForceGenerator*>> _forceRegister;

};

