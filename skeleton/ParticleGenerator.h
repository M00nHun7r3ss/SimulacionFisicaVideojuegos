//#pragma once
//
//#include <random>
//#include "Particle.h" //Para las particulas
//#include "ParticleSystem.h"
//#include <algorithm>
//
////Clase Abstracta 
//class ParticleGenerator
//{
//public:
//
//	//Constructora
//	ParticleGenerator();
//
//	//Destructora
//	virtual ~ParticleGenerator() = 0;
//
//	//Genera particulas en el sistema
//	virtual void generateParticles(ParticleSystem& system, double t) = 0;
//
//	//Getters
//	inline PxVec3 getPosition() { return _pos; }
//	inline PxVec3 getVelocity() { return _vel; }
//	inline int getNumParticles() const { return _nParticles; }
//	inline double getDuration() { return _duration; }
//	inline double getProbability() { return _probability; }
//
//	//Setters
//	inline void setPosition(PxVec3 p) { _pos = p; }
//	inline void setVelocity(PxVec3 v) { _vel = v; }
//	inline void setNumParticles(int n) { _nParticles = n; }
//	inline void setDuration(double d) { _duration = d; }
//	inline void setProbability(double p) { _probability = p; }
//
//protected:
//
//	int _nParticles;
//	PxVec3 _pos;
//	PxVec3 _vel;
//	double _duration;
//	double _probability;
//
//	std::mt19937 _mersenneRandom;
//	std::uniform_int_distribution<int>  uniformDistribution;
//};
//
