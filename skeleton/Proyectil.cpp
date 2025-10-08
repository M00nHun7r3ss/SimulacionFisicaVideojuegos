#include "Proyectil.h"

Proyectil::Proyectil(PxVec3 pos, PxVec3 vel, PxVec3 gravity) :
	Particle(pos, vel), _g(gravity) {}

Proyectil::Proyectil(PxVec3 pos, PxVec3 vel, Vector4 color, PxVec3 gravity) :
	Particle(pos, vel, color), _g(gravity) {}

Proyectil::Proyectil(PxVec3 pos, PxVec3 vel, Vector4 color, PxVec3 acel, PxVec3 gravity, double masa, double dumping, double duration) :
	Particle(pos, vel, color, acel, masa, dumping, duration), _g(gravity) {}

Proyectil::~Proyectil() {}

PxVec3 Proyectil::getGravity() { return _g; }

void Proyectil::setGravity(PxVec3 newGravity) { _g = newGravity; }
