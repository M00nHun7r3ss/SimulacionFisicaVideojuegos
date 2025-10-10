#pragma once

#include <PxPhysicsAPI.h> //Para usar Vector3
#include "RenderUtils.hpp" //Para RenderItem
#include "Vector3D.h" //TODO: cambiar luego

#include <chrono> //Para el delay en la integracion 
#include <thread>
 
using namespace physx;


class Particle
{
public: 
	//Constructora con velocidad y posicion iniciales (Blanca)
	Particle(PxVec3 pos, PxVec3 vel);

	//Constructora con velocidad, posicion y colores iniciales (De colores)
	Particle(PxVec3 pos, PxVec3 vel, Vector4 color);

	//Constructora con todos los datos (Especiales)
	Particle(PxVec3 pos, PxVec3 vel, Vector4 color, PxVec3 acel, double masa = 1.0, double dumping = 0.999, double duration = 5.0);

	//Destructora
	~Particle();

	//1.1. Integracion // 0 - Euler,  1 - SemiEuler, 2 - Verlet
	void integrate(double t, int integrationType);

	//Getters
	RenderItem* getRenderItem();
	Vector4 getColor();
	PxVec3 getPos();
	PxVec3 getV();
	PxVec3 getA();
	double getM();
	double getDump();
	double getDuration();
	bool isActive();

	//Setters
	void setRenderItem(RenderItem* newParticle);
	void setColor(Vector4 newColor);
	void setPos(PxVec3 newPos);
	void setV(PxVec3 newV);
	void setA(PxVec3 newA);
	void setM(double newM);
	void setDump(double newDump);
	void setDuration(double newDuration);
	void setActive(bool act);

private:

	RenderItem* _renderItem;
	Vector4 _color;
	PxTransform* _transform; //para la posicion, etc...
	PxVec3 _v; //velocidad en m/s
	PxVec3 _a; //aceleracion en m/s^2
	double _m; //masa en kg
	double _dump; //dumping
	double _duration; //en s (entre 0 y 1, cuanto mas pequenio mas se frena)
	bool _active = false; //para saber si se esta usando

	//1.1.a Integracion con Euler
	void integrateEuler(double t);

	//1.1.b Integracion con Euler Semiimplicito
	void integrateSemiEuler(double t);

	//1.1.c Integracion con Verlet
	void integrateVerlet(double t);
};

