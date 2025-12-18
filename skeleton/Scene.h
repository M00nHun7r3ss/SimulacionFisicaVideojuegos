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
// Scene0, Scene1, Scene0 ...

//ESCENA FINAL
class Scene0 : public Scene
{
public:
	Scene0(PxMaterial* material, PxPhysics* physics, PxScene* scene);
	~Scene0() {}
	void init() override;
	void update(double t) override;
	void cleanup() override;

	void handleKey(unsigned char key, const PxTransform& camera) override;

	void shootFromCamera(Proyectil::ProyectilType type) override;
	void shootFromPlace(Proyectil::ProyectilType type, PxVec3 position, PxVec3 direction) override;
	void shootEnemyCanon(Proyectil::ProyectilType type, PxVec3 position, PxVec3 direction);

	//CONDICIONES DE MUERTE
	void checkCollisionWithGround(Particle* p, PxVec3 floor);
	void checkCollisionWithWater(Particle* p);
	bool checkCollisionWithBullet(Particle* player, Proyectil* bullet);

	//CONDICIONES DE VICTORIA
	bool checkCollisionWithCollectables(Particle* p, PxRigidDynamic* collectable);
	bool checkCollisionBulletCollectables(Proyectil* bullet, PxRigidDynamic* collectable);

	void checkEndGame(double t);

	//Getters
	inline PxVec3 getPlayerPos() const { return _playerParticle->getPos(); }
	inline PxVec3 getPlayerFront() const { return _playerParticle->getFrontOrientation(); }
	inline int getPlayerLives() const { return _lives; }
	inline int getPlayerPoints() const { return _points; }
	//Setters
	inline void setPlayerPoints(int points) { _points += points; }
	inline void setPlayerLives() { _lives -= 1; }


private:

	// --- SOLIDOS RIGIDOS ---
	PxMaterial* gMaterial = NULL;
	PxPhysics* gPhysics = NULL;
	PxScene* gScene = nullptr;

	// --- BASE --- // SOLIDO RIGIDO ESTATICO
	RenderItem* _base = NULL;

	void createBase();

	// --- LAGO --- // FLOTABILIDAD
	RenderItem* _lake = NULL;
	float _waterHeight;
	//Caja
	RenderItem* _floatingBox1 = NULL;
	RenderItem* _floatingBox2 = NULL;
	RenderItem* _floatingBox3 = NULL;
	RenderItem* _floatingBox4 = NULL;
	RenderItem* _floatingBox5 = NULL;
	Particle* _floatingParticle1;
	Particle* _floatingParticle2;
	Particle* _floatingParticle3;
	Particle* _floatingParticle4;
	Particle* _floatingParticle5;
	ParticleSystem* _particleSystem;
	double _objectSize;
	double _mass;
	double _volume;

	void createLake();
	void createWaterCube(PxVec3 position, Particle*& particle, RenderItem*& render);

	// --- FUENTES DEL LAGO ---
	ParticleSystem* _fountain1 = nullptr;
	ParticleSystem* _fountain2 = nullptr;
	ParticleSystem* _fountain3 = nullptr;
	ParticleSystem* _fountain4 = nullptr;
	GaussParticleGenerator* _f1gen = nullptr;
	GaussParticleGenerator* _f2gen = nullptr;
	GaussParticleGenerator* _f3gen = nullptr;
	GaussParticleGenerator* _f4gen = nullptr;

	void createFountain(PxVec3 position, ParticleSystem*& particleSystem, GaussParticleGenerator*& generator);

	// --- JUGADOR ---
	Particle* _playerParticle;
	ParticleSystem* _player;
	int _points;
	int _lives;

	void createPlayer();

	// --- DISPAROS DEL JUGADOR ---
	std::vector<Proyectil*> _proyectils;

	// --- FUERZAS GENERALES DE JUEGO
	GravityForce* _gravity = NULL; //La gravedad se aplica al jugador y a los cubos del agua
	WindForce* _wind = NULL; //El viento se aplica a la lluvia
	FloatingForce* _floating = NULL; //Para los cubos sobre el agua
	//ExplosionForce* _explosion1 = NULL; //Para los fuegos artificiales de la victoria
	//ExplosionForce* _explosion2 = NULL; //Para los fuegos artificiales de la victoria
	//ExplosionForce* _explosion3 = NULL; //Para los fuegos artificiales de la victoria
	//ExplosionForce* _explosion4 = NULL; //Para los fuegos artificiales de la victoria

	//// --- ENEMIGOS ---
	RenderItem* _enemyCannon1 = NULL;
	RenderItem* _enemyCannon2 = NULL;
	RenderItem* _enemyCannon3 = NULL;
	RenderItem* _enemyCannon4 = NULL;
	RenderItem* _enemyCannon5 = NULL;
	RenderItem* _enemyCannon6 = NULL;
	RenderItem* _enemyCannon7 = NULL;
	RenderItem* _enemyCannon8 = NULL;

	void createEnemy(PxVec3 position, RenderItem*& render);

	// --- DISPAROS DE ENEMIGOS ---
	std::vector<Proyectil*> _enemyProyectils;
	double _enemyShootTimer[8];
	double _enemyShootCooldown[8];

	void enemyShoot(int index, PxVec3 position,	PxVec3 direction, double t);

	// --- RECOLECTABLES ---
	SolidSystem* _collectable1;
	SolidSystem* _collectable2;
	SolidSystem* _collectable3;
	SolidSystem* _collectable4;
	SolidSystem* _collectable5;
	SolidSystem* _collectable6;
	SolidSystem* _collectable7;
	SolidSystem* _collectable8;
	SolidSystem* _collectable9;

	void createCollectables(SolidSystem*& sSystem, PxVec3 position);
	void checkCollectables(SolidSystem* sSystem);
	void checkBulletCollectables(SolidSystem* sSystem);

	// --- LLUVIA ---
	ParticleSystem* _rain = nullptr;
	UniformParticleGenerator* _rainGen = nullptr;
	bool _isRaining;

	void createRain();

	//// --- FUEGOS ARTIFICIALES ---
	//ParticleSystem* _firework1 = nullptr;
	//ParticleSystem* _firework2 = nullptr;
	//ParticleSystem* _firework3 = nullptr;
	//ParticleSystem* _firework4 = nullptr;
	//UniformParticleGenerator* _fw1gen = nullptr;
	//UniformParticleGenerator* _fw2gen = nullptr;
	//UniformParticleGenerator* _fw3gen = nullptr;
	//UniformParticleGenerator* _fw4gen = nullptr;
	bool _victory;

	//void createFirework(const PxVec3& position, ParticleSystem*& particleSystem, UniformParticleGenerator*& generator, const Vector4& color, ExplosionForce*& force);

	// ---- CONDICIONES DE JUEGO ----
	int _goalPoints; //Puntos objetivo de victoria
	int _gameState; //0 - sigue jugando, 1 - ha ganado por llegar a puntos maximos, 2 - ha perdido por perder todas las vidas

};
