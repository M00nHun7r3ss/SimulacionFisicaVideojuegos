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
	Particle(pos, vel, color, acel, masa, dumping, duration, 1.0), _g(gravity)
{
	setA(acel);
}

Proyectil::~Proyectil() {}

double Proyectil::calculateSimulatedMandV(double mReal, double vReal)
{
	// 0.5 * mReal * vReal^2 = 0.5 * mSim * vSim^2
	// => vSim = vReal * sqrt(mReal / mSim)

	//Calculo de la velocidad en base a la masa
	double vSim = vReal * sqrt(mReal / getM());

	//Elegimos la direccion
	PxVec3 dir = getV().getNormalized();

	//Y seteamos la nueva velocidad en base al valor simulado
	setV(dir * vSim);
}

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

	// Variables reales para el escalado de velocidad
	double mReal;   // masa real en kg
	double vReal;  // velocidad real en m/s

	//Diferentes tipos de proyectil, con distinto color y gravedad
	switch (type)
	{
		case ProyectilType::Bullet:
			mReal = 0.05;
			vReal = 300;
			setColor(Vector4(1.0, 0.0, 0.0, 1.0));
		//Con la direccion de la camara
			setV(60.0 * dir);
			setGravity(PxVec3(0.0, -0.0005, 0.0));
			setA(getGravity());
		break;

		//case ProyectilType::CanonBall:
		//	setColor(Vector4(0.0, 1.0, 0.0, 1.0));
		//	//Con la direccion de la camara
		//	setV(40.0 * dir + PxVec3(0.0f, 20.0f, 0.0f));
		//	setGravity(PxVec3(0.0, -9.8, 0.0));
		//	setA(getGravity());
		//break;

		case ProyectilType::Bubble:
			mReal = 0.001;
			vReal = 5;
			setColor(Vector4(0.0, 0.0, 1.0, 1.0));
			//Con la direccion de la camara
			setV(10.0 * dir);
			setGravity(PxVec3(0.0, 2.0, 0.0));
			setA(getGravity());
		break;
	}

	// Aceleracion de acuerdo a la gravedad
	setA(getGravity());

	// Velocidad de acuerdo a la masa
	calculateSimulatedMandV(mReal, vReal);

	// Actualizar color del RenderItem 
	if (getRenderItem() != nullptr)
	{
		getRenderItem()->color = getColor();
	}

	// Activamos el proyectil 
	Particle::setActive(true);
}

