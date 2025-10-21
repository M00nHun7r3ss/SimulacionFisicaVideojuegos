#include "Proyectil.h"

Proyectil::Proyectil(PxVec3 pos, PxVec3 vel, PxVec3 gravity) :
	Particle(pos, vel), _g(gravity) 
{
	setA(gravity);
}

Proyectil::Proyectil(PxVec3 pos, PxVec3 vel, Vector4 color, PxVec3 gravity) :
	Particle(pos, vel, color), _g(gravity) 
{
	setA(gravity);
}

Proyectil::Proyectil(PxVec3 pos, PxVec3 vel, Vector4 color, PxVec3 acel, PxVec3 gravity, double masa, double dumping, double duration) :
	Particle(pos, vel, color, gravity, masa, dumping, duration), _g(gravity) {}

Proyectil::~Proyectil() {}

void Proyectil::shoot(ProyectilType type)
{
	//El tipo que se pasemos por input
	_t = type;

	//Desde la camara
	setPos(GetCamera()->getTransform().p);
	//Direccion de la camara
	PxVec3 dir = PxVec3(GetCamera()->getDir());

	//Iniciamos la duracion
	setDuration(5.0);

	//Diferentes tipos de proyectil, con distinto color y gravedad
	switch (type)
	{
		case ProyectilType::Bullet:
			setColor(Vector4(1.0, 0.0, 0.0, 1.0));
		//Con la direccion de la camara
			setV(60.0 * dir);
			setGravity(PxVec3(0.0, -0.0005, 0.0));
			setA(getGravity());
		break;

		case ProyectilType::CanonBall:
			setColor(Vector4(0.0, 1.0, 0.0, 1.0));
			//Con la direccion de la camara
			setV(40.0 * dir + PxVec3(0.0f, 20.0f, 0.0f));
			setGravity(PxVec3(0.0, -9.8, 0.0));
			setA(getGravity());
		break;

		case ProyectilType::Bubble:
			setColor(Vector4(0.0, 0.0, 1.0, 1.0));
			//Con la direccion de la camara
			setV(10.0 * dir);
			setGravity(PxVec3(0.0, 2.0, 0.0));
			setA(getGravity());
		break;
	}

	// Aceleracion de acuerdo a la gravedad
	setA(getGravity());

	// Actualizar color del RenderItem 
	if (getRenderItem() != nullptr)
	{
		getRenderItem()->color = getColor();
	}

	// Activamos el proyectil 
	Particle::setActive(true);


}

