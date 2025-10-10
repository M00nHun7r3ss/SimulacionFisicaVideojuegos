#pragma once

#include <random>
#include "Particle.h" //Para las particulas

//Clase Abstracta 
class ParticleGenerator
{
public:

	//Constructora
	ParticleGenerator();

	//Destructora
	~ParticleGenerator();

	//Genera particulas en el sistema
	virtual void generateParticle() = 0;

	//Getters

	//Setters

private:

	int _nParticles;
	PxVec3 _pos;
	PxVec3 _vel;
	double _duration;
	double _probability;
	std::mt19937 _mersenneRandom;
	std::uniform_int_distribution<int>  uniformDistribution;
};

