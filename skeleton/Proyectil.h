#pragma once

#include <PxPhysicsAPI.h> //Para usar Vector3
#include "RenderUtils.hpp" //Para RenderItem
#include <vector> //Para el vector de proyectiles
#include "Particle.h" 

using namespace physx;

class Proyectil : public Particle
{
public:

	//Usara la constructora base de Particle, aniadiendo unicamente la gravedad
	//Constructora con velocidad y posicion iniciales (Blanca)
	Proyectil(PxVec3 pos, PxVec3 vel, PxVec3 gravity);

	//Constructora con velocidad, posicion y colores iniciales (De colores)
	Proyectil(PxVec3 pos, PxVec3 vel, Vector4 color, PxVec3 gravity);

	//Constructora con todos los datos (Especiales)
	Proyectil(PxVec3 pos, PxVec3 vel, Vector4 color, PxVec3 acel, PxVec3 gravity, double masa = 1.0, double dumping = 0.999, double duration = 5.0);

	//Diferentes tipos de proyectil //CanonBall no funciona bien
	enum class ProyectilType { Bullet, /*CanonBall,*/ Bubble };

	//Disparo desde camera y desde un lugar (ya sea el player u otro sitio)
	void shootFromCamera(ProyectilType type);
	void shootFromPlace(ProyectilType type, PxVec3 positionSpawn, PxVec3 direction);

	//Destructora
	~Proyectil();

	//Escalado de velocidad segun masa
	void calculateSimulatedMandV(double mReal, double vReal);

	//Getters
	inline PxVec3 getGravity() { return _g; }
	inline bool isActive() { return Particle::isActive();}

	//Setters
	inline void setGravity(PxVec3 newGravity) { _g = newGravity; }
	inline void setActive(bool act) {Particle::setActive(act);}


private:

	PxVec3 _g;	 //gravedad en m/s^2
	ProyectilType _t; //para definir el tipo de proyectil al disparar

};



