#include "Particle.h"

Particle::Particle(PxVec3 pos, PxVec3 vel) : _pos(pos), _v(vel), _color(1.0, 1.0, 1.0, 1.0), _a(PxVec3(0.0, 0.0, 0.0)), _m(1.0), _dump(0.999), _duration(5.0) {}

//Destructora
Particle::~Particle() {}

void Particle::integrateEuler(double t)
{
	//MRU
	////x1 = x0 + v0 * t;
	//_pos += _v * t;

	//MRUA
	////x1 = x0 + v0 * t;
	////v1 = v0 + a * t
	//_pos += _v * t;
	//_v += _a * t;

	//Dumping
	////x1 = x0 + v0 * t;
	////v1 = v0 + a * t
	////v1 = v1 * d^t
	_pos = _pos + _v * t;
	_v += _a * t;
	_v *= pow(_dump, t);

}

void Particle::integrateSemiEuler(double t)
{
	//MRU
	////x1 = x0 + v0 * t;
	//_pos += _v * t;

	//MRUA
	////v1 = v0 + a * t
	////x1 = x0 + v0 * t;
	//_v += _a * t;
	//_pos += _v * t;

	//Dumping
	////v1 = v0 + a * t
	////v1 = v1 * d^t
	////x1 = x0 + v0 * t;
	_v += _a * t;
	_v *= pow(_dump, t);
	_pos = _pos + _v * t;
}

void Particle::integrateVerlet(double t)
{
	//MRUA
	////x1 = 2*x0 - x-1 + t^2 * a0;
	////a1 =
	//_v += _a * t;
	//_pos += _v * t;

	//Dumping
	////x1 = 2*x0 - x-1 + t^2 * a0;
	////v1 = v0 + a * t
	////v1 = v1 * d^t
	//_v += _a * t;
	//_v *= pow(_dump, t);
	//_pos = _pos + _v * t;

}

RenderItem* Particle::getRenderItem() { return _renderItem; }

Vector4 Particle::getColor() { return _color; }

PxVec3 Particle::getPos() {	return _pos; }

PxVec3 Particle::getV() { return _v; }

PxVec3 Particle::getA() { return _a; }

double Particle::getM() { return _m; }

double Particle::getDump() { return _dump; }

double Particle::getDuration() { return _duration; }

void Particle::setRenderItem(RenderItem* newRenderItem) { _renderItem = newRenderItem; }

void Particle::setColor(Vector4 newColor) { _color = newColor; }

void Particle::setPos(PxVec3 newPos) { _pos = newPos; }

void Particle::setV(PxVec3 newV) { _v = newV; }

void Particle::setA(PxVec3 newA) { _a = newA; }

void Particle::setM(double newM) { _m = newM; }

void Particle::setDump(double newDump) { _dump = newDump; }

void Particle::setDuration(double newDuration) { _duration = newDuration; }


