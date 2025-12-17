#pragma once

#include "ExplosionForce.h"
#include "Particle.h"  //Practica 1.1
#include "Proyectil.h" //Practica 1.2
#include "ParticleGenerator.h" //Practica 2
#include "GaussParticleGenerator.h" //Practica 2
#include "UniformParticleGenerator.h" //Practica 2
#include "ParticleSystem.h" //Practica 2
#include "GravityForce.h"//Practica 3
#include "WindForce.h" //Practica 3
#include "WhirlwindForce.h" //Practica 3
#include "FixedSpringForceGenerator.h" //Practica 4
#include "SpringForceGenerator.h" //Practica 4
#include "FloatingForce.h" //Practica 4
#include "SolidSystem.h" //Practica 5
#include "SolidGenerator.h" //Practica 5
#include "SWindForce.h" //Practica 5
#include "TorqueForce.h" //Practica 5


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
// Para ver las anteriores practicas basta con volver a los commits concretos.
//	Voy a dejar aqui solo las escenas en las que estoy trabajando
// Scene0, Scene1, Scene2 ...

//Practica 4
class Scene0 : public Scene
{
public:
	Scene0(PxMaterial* material);
	~Scene0() {}
	void init() override;
	void update(double t) override;
	void cleanup() override;

	void handleKey(unsigned char key, const PxTransform& camera) override;

private:
	//Practica 4
	PxMaterial* gMaterial = NULL;

	//// -------------------- PARTE DE LOS MUELLES --------------------
	////Fuerzas
	//FixedSpringForceGenerator* _FixedSpringForce = NULL;
	//SpringForceGenerator* _SpringForce = NULL;
	//GravityForce* _gravityForce = NULL;
	//WindForce* _lateralForce = NULL;
	//bool _windActive;
	//double _windTimer;

	////FIXED - PARTICLE
	//PxVec3 _fixedPos;
	//float _kFixed;
	//float _restLengthFixed;
	//RenderItem* _fixedObject = NULL;
	//Particle* a = NULL;

	////PARTICLE - PARTICLE
	//float _k;
	//float _restLength;
	//Particle* b = NULL;
	//ParticleSystem* _particleSystem;

	//// - EJERCICIO OPCIONAL SLINKY -
	//std::vector<Particle*> _slinky;

	// -------------------- PARTE DE FLOTACION --------------------
	//Agua
	RenderItem* _waterPlane = NULL;
	float _waterHeight;
	//Caja
	RenderItem* _floatingBox = NULL;
	Particle* _floatingParticle;
	ParticleSystem* _particleSystem;
	double _mass;
	double _volume;
	//Fuerzas
	GravityForce* _gravityForce = NULL;
	FloatingForce* _floatingForce = NULL;
};

class Scene1 : public Scene
{
public:
	Scene1(PxMaterial* material, PxPhysics* physics, PxScene* scene);
	~Scene1() {}
	void init() override;
	void update(double t) override;
	void cleanup() override;

	void handleKey(unsigned char key, const PxTransform& camera) override;

private:
	//Practica 5
	PxMaterial* gMaterial = NULL;
	PxPhysics* gPhysics = NULL;
	PxScene* gScene = nullptr;
	RenderItem* _groundSolid = NULL;

	SolidSystem* _solidSystem;
};

//ESCENA FINAL
class Scene2 : public Scene
{
public:
	Scene2(PxMaterial* material, PxPhysics* physics, PxScene* scene);
	~Scene2() {}
	void init() override;
	void update(double t) override;
	void cleanup() override;

	void handleKey(unsigned char key, const PxTransform& camera) override;

	void shootFromCamera(Proyectil::ProyectilType type) override;
	void shootFromPlace(Proyectil::ProyectilType type, PxVec3 position, PxVec3 direction) override;
	//void shootEnemyCanon(Proyectil::ProyectilType type, PxVec3 position, PxVec3 direction);

	void checkCollisionWithGround(Particle* p, PxVec3 floor);

	inline PxVec3 getPlayerPos() const { return _playerParticle->getPos(); }


private:

	// --- SOLIDOS RIGIDOS ---
	PxMaterial* gMaterial = NULL;
	PxPhysics* gPhysics = NULL;
	PxScene* gScene = nullptr;

	// --- BASE --- // SOLIDO RIGIDO ESTATICO
	RenderItem* _base = NULL;
	RenderItem* _plat1 = NULL;
	RenderItem* _plat2 = NULL;
	RenderItem* _plat3 = NULL;
	RenderItem* _plat4 = NULL;

	// --- JUGADOR ---
	Particle* _playerParticle;
	ParticleSystem* _player;
	int _points;
	int _lives;
	PxVec3 _playerDirection;
	//Actuara como fuerza del movimiento del player en las distintas direcciones
	WindForce* _movement = NULL;
	bool _movementActive;
	int _movementTimer;

	// --- DISPAROS DEL JUGADOR ---
	std::vector<Proyectil*> _proyectils;

	// --- FUERZAS GENERALES DE JUEGO
	GravityForce* _gravity = NULL;

	//// --- ENEMIGOS ---
	//RenderItem* _windCanon = NULL;
	//RenderItem* _fireCanon = NULL;
	//// Sistemas de particulas
	////Aire
	//ParticleSystem* _airSystem = NULL;
	////Fuego
	//ParticleSystem* _fireSystem = NULL;

};
