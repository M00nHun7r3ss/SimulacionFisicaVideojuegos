#pragma once

#include <PxPhysicsAPI.h> //Para usar Vector3
#include "RenderUtils.hpp" //Para RenderItem
#include "Vector3D.h" //TODO: cambiar luego
#include <vector> //Para el vector de proyectiles
#include "Particle.h" 

using namespace physx;

class Proyectil : public Particle
{
public:

	//Constructora con velocidad y posicion iniciales
	Proyectil(PxVec3 pos, PxVec3 vel, Vector4 color, double masa);

	//Destructora
	~Proyectil();

	double calculateSimulatedM(); 

	//Getters
	PxVec3 getGravity();

	//Setters
	void setGravity(PxVec3 newGravity);

private:

	PxVec3 _g;	 //gravedad en m/s^2
};


//Para cuando hagamos fuerzas
//0.5* mReal * vReal^2 = 0.5 * mReal * vReal^2

//Direccion de la camara 
//velAuxiliar * direccion



