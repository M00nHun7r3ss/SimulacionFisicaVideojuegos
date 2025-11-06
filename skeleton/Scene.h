#pragma once

#include "Particle.h"  //Practica 1.1
#include "Proyectil.h" //Practica 1.2
#include "ParticleGenerator.h" //Practica 2
#include "GaussParticleGenerator.h" //Practica 2
#include "UniformParticleGenerator.h" //Practica 2
#include "ParticleSystem.h" //Practica 2
#include "GravityForce.h"//Practica 3
#include "WindForce.h" //Practica 3
#include "WhirlwindForce.h" //Practica 3

class Scene
{
public:
	Scene() {}
	virtual ~Scene() {} 

	virtual void init() = 0; //En initPhysics()
	virtual void update(double t) = 0; //En stepPhysics()
	virtual void cleanup() = 0; //En cleanupPhysicis()

	virtual void enterScene(); //Al entrar en una escena
	virtual void exitScene(); //Al salir de una escena

	//Gestiona el input de escenas concretas
	virtual void handleKey(unsigned char key, const PxTransform& camera) {} //En keyPress()

	//Gestiona los disparos desde camera
	virtual void shootFromCamera(Proyectil::ProyectilType type) {} //en el handleKey de cada escena
	//Gestiona los disparos desde una posicion
	virtual void shootFromPlace(Proyectil::ProyectilType type, PxVec3 position, PxVec3 direction) {} //en el handleKey de cada escena

};

// --- ESCENAS HIJAS ---
// Scene0, Scene1, Scene2 ...

//Practica 0
class Scene0 : public Scene
{
public:
	Scene0(PxMaterial* material);
	~Scene0() {}
	void init() override;
	void update(double t) override;
	void cleanup() override;

private:
	// PRACTICA 0
	RenderItem* sp1 = NULL;
	RenderItem* spX = NULL;
	RenderItem* spY = NULL;
	RenderItem* spZ = NULL;

	PxMaterial* gMaterial = NULL;
};

//Practica 1
class Scene1 : public Scene
{
public:
	Scene1() = default;
	~Scene1() {}
	void init() override;
	void update(double t) override;
	void cleanup() override;

private:
	//Practica 1.1
	Particle* particleSimple = NULL;
	Particle* particleColor = NULL;
	Particle* particleFull = NULL;

	//Practica 1.2
	Proyectil* bullet = NULL;
	Proyectil* cannonBall = NULL;
	Proyectil* bubble = NULL;

	std::vector<Proyectil*> proyectils;
};

//Practica 2 y 3
class Scene2 : public Scene
{
public:
	Scene2() = default;
	~Scene2() {}
	void init() override;
	void update(double t) override;
	void cleanup() override;

private:
	//Practica 2
	// Sistemas de partículas
	//Manguera
	ParticleSystem* hoseSystem = NULL;
	//Niebla
	ParticleSystem* fogSystem = NULL;
	//Fuego
	ParticleSystem* fireSystem = NULL;

	// Generadores
	ParticleGenerator* hoseGenerator = NULL;
	ParticleGenerator* fogGenerator = NULL;
	ParticleGenerator* fireGenerator = NULL;

	//Practica 3
	GravityForce* inverseGravity = NULL;
	WindForce* basicWind = NULL;
	WindForce* advancedWind = NULL;
	WhirlwindForce* whirlwind = NULL;

};

//Practica Intermedia
class Scene3 : public Scene
{
public:
	Scene3(PxMaterial* material);
	~Scene3() {}
	void init() override;
	void update(double t) override;
	void cleanup() override;

	void handleKey(unsigned char key, const PxTransform& camera) override;

	void shootFromCamera(Proyectil::ProyectilType type) override;
	void shootFromPlace(Proyectil::ProyectilType type, PxVec3 position, PxVec3 direction) override;

private:
	PxMaterial* gMaterial = NULL;

	//Plano de la base
	RenderItem* _base1 = NULL;

	//Player
	Particle* _player = NULL;
	//ParticleSystem* _playerSystem = NULL;
	//UniformParticleGenerator* _playerGenerator = NULL;

	//Disparos
	Proyectil* bullet = NULL;
	std::vector<Proyectil*> proyectils;

	//Caniones de fuerzas
	RenderItem* _windCanon = NULL;
	RenderItem* _fireCanon = NULL;
	// Sistemas de partículas
	//Aire
	ParticleSystem* airSystem = NULL;
	//Fuego
	ParticleSystem* fireSystem = NULL;

	//Generadores
	ParticleGenerator* airGenerator = NULL;
	ParticleGenerator* fireGenerator = NULL;

	//Fuerzas
	GravityForce* inverseGravity = NULL;
	WindForce* advancedWind = NULL;

	//Activar y desactivar
	bool windActive = false;
	bool fireActive = false;
};

