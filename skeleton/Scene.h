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
	Scene();
	virtual ~Scene() {} 

	virtual void init() = 0; //En initPhysics()
	virtual void update(double t) = 0; //En stepPhysics()
	virtual void cleanup() = 0; //En cleanupPhysicis()

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
	Scene3() = default;
	void init() override;
	void update(double t) override;
	void cleanup() override;

private:

};

