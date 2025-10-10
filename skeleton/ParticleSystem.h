#pragma once

#include <vector> //Para el vector de particulas
#include "Particle.h" //Para las particulas
#include "ParticleGenerator.h" //Para los generadores

class ParticleSystem
{
public:
	//Constructora
	ParticleSystem();

	//Destructora
	~ParticleSystem();

	//Ciclo de vida de las particulas
	//1. Actualizar las existentes
	//2. Eliminar las particulas que se dejan de usar
	//3. Crear particulas nuevas
	void update(double t);

private:

	std::vector<Particle*> _particles;
	std::vector<ParticleGenerator*> _generators;
};

//list Particle*
//list ParticleGenerator*

