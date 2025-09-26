#pragma once

#include <PxPhysicsAPI.h> //Para usar Vector3
#include "Vector3D.h" //Para cuando lo arregle
#include "RenderUtils.hpp" //Para RenderItem

using namespace physx;


class Particle
{
public: 
	//Constructora con velocidad y posicion iniciales
	Particle(PxVec3 pos, PxVec3 vel);

	//Destructora - borrar render item
	~Particle();

	//1.1.a Integracion con Euler
	void integrateEuler(double t);

	//1.1.b Integracion con Euler Semiimplicito
	//void integrateSemiEuler(double t);

	//1.1.c Integracion con Verlet
	//void integrateVerlet(double t);

	//Getters
	RenderItem* getRenderItem();
	Vector4 getColor();
	PxVec3 getPos();
	PxVec3 getV();
	PxVec3 getA();
	double getM();
	double getDump();
	double getDuration();

	//Setters
	void setRenderItem(RenderItem* newParticle);
	void setColor(Vector4 newColor);
	void setPos(PxVec3 newPos);
	void setV(PxVec3 newV);
	void setA(PxVec3 newA);
	void setM(double newM);
	void setDump(double newDump);
	void setDuration(double newDuration);

private:

	RenderItem* _renderItem;
	Vector4 _color;
	PxVec3 _pos; //Lo usaremos para el RenderItem en m
	PxVec3 _v; //velocidad en m/s
	PxVec3 _a; //aceleracion en m/s^2
	double _m; //masa en kg
	double _dump; //dumping
	double _duration; //en s (entre 0 y 1, cuanto mas pequenio mas se frena)

	//1. Mov con v constante
	//2. Mov con a
	//3. Dumping

};

