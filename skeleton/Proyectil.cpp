#include "Proyectil.h"

Proyectil::Proyectil(PxVec3 pos, PxVec3 vel, Vector4 color, double masa) :
	Particle(pos, vel, color), _g(PxVec3(0.0, 0.01, 0.0))
{
	this->setColor(color);
	this->setM(masa);
}

Proyectil::~Proyectil() {}

PxVec3 Proyectil::getGravity() { return _g; }

void Proyectil::setGravity(PxVec3 newGravity) { _g = newGravity; }
