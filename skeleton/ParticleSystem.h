#pragma once

#include <vector> //Para el vector de particulas
#include "Particle.h" //Para las particulas
#include "ParticleForceRegister.h" //Para las fuerzas
#include "ForceGenerator.h"

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

	// Aniadir elementos
	void addParticle(Particle* p);
	void addGenerator(ParticleGenerator* g);

	// Gestionar fuerzas
	void addForceGenerator(ForceGenerator* fGen);
	void removeForceGenerator(ForceGenerator* fGen);
	void clearForces();

	// Getters
	inline int numParticles() const { return _particles.size(); }
	inline int numGenerators() const { return _generators.size(); }
	inline bool getUseGravity() const { return _useGravity; }
	inline bool getPaused() const { return _paused; }

	// Setters
	inline void setNumParticles(int numParticles) { _particles.resize(numParticles); }
	inline void setUseGravity(bool newGravity) { _useGravity = newGravity; }
	inline void setPaused(bool pause) { _paused = pause; }

	// Limpiar particulas en desuso
	void deleteDeadParticles();

	// Reactivar particulas en desuso
	Particle* reactivateDeadParticles();


protected:

	//Gravedad por defecto
	const PxVec3 GRAVITY = PxVec3(0.0f, -10.0f, 0.0f);
	bool _useGravity; //Por si queremos desactivarla
	std::vector<Particle*> _particles;
	std::vector<ParticleGenerator*> _generators;

	//Para gestionar las fuerzas
	ParticleForceRegister _forceRegister;

	//Para la pausa del sistema
	bool _paused;
};

