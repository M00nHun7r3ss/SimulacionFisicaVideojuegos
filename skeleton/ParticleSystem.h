#pragma once

#include <vector> //Para el vector de particulas
#include "Particle.h" //Para las particulas

class ParticleGenerator; //Para los generadores

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

	// Anidir elementos
	void addParticle(Particle* p);
	void addGenerator(ParticleGenerator* g);

	// Getters
	inline int numParticles() const { return _particles.size(); }
	inline int numGenerators() const { return _generators.size(); }

	// Limpiar particulas en desuso
	void deleteDeadParticles();

	// Reactivar particulas en desuso
	Particle* reactivateDeadParticles();

protected:

	// gravedad por defecto
	const PxVec3 GRAVITY = PxVec3(0.0f, -10.0f, 0.0f);
	std::vector<Particle*> _particles;
	std::vector<ParticleGenerator*> _generators;

};

