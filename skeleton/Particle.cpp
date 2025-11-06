#include "Particle.h"

Particle::Particle(PxVec3 pos, PxVec3 vel) :
	_v(vel), _color(Vector4(1.0, 1.0, 1.0, 1.0)), _a(PxVec3(0.0, 0.0, 0.0)),
	_m(1.0), _dump(0.999), _duration(5.0), _active(true), _size(1.0), _direction(PxVec3(1.0, 0.0, 0.0))
{
	//Creamos la forma con la geometria
	PxShape* sphere0 = CreateShape(PxSphereGeometry(_size));

	_transform = new PxTransform(PxVec3(pos.x, pos.y, pos.z));
	_renderItem = new RenderItem(sphere0, _transform, _color);

	RegisterRenderItem(_renderItem);
}

Particle::Particle(PxVec3 pos, PxVec3 vel, Vector4 color) :
	_v(vel), _color(color), _a(PxVec3(0.0, 0.0, 0.0)),
	_m(1.0), _dump(0.999), _duration(5.0), _size(1.0), _direction(PxVec3(1.0, 0.0, 0.0))
{
	//Creamos la forma con la geometria
	PxShape* sphere0 = CreateShape(PxSphereGeometry(_size));

	_transform = new PxTransform(PxVec3(pos.x, pos.y, pos.z));
	_renderItem = new RenderItem(sphere0, _transform, _color);

	RegisterRenderItem(_renderItem);
}

Particle::Particle(PxVec3 pos, PxVec3 vel, Vector4 color, double masa) :
	_v(vel), _color(color), _a(PxVec3(0.0, 0.0, 0.0)),
	_m(masa), _dump(0.999), _size(2.0), _direction(PxVec3(1.0, 0.0, 0.0))
{
	//Creamos la forma con la geometria
	PxShape* sphere0 = CreateShape(PxSphereGeometry(_size));

	_transform = new PxTransform(PxVec3(pos.x, pos.y, pos.z));
	_renderItem = new RenderItem(sphere0, _transform, _color);

	RegisterRenderItem(_renderItem);
}

Particle::Particle(PxVec3 pos, PxVec3 vel, Vector4 color, PxVec3 acel, double masa, double dumping, double duration) :
	_v(vel), _color(color), _a(acel),
	_m(masa), _size(2.0), _dump(dumping), _direction(PxVec3(1.0, 0.0, 0.0))
{
	// Creamos la forma con la geometria
	PxShape* sphere0 = CreateShape(PxSphereGeometry(_size));

	_transform = new PxTransform(PxVec3(pos.x, pos.y, pos.z));
	_renderItem = new RenderItem(sphere0, _transform, _color);

	RegisterRenderItem(_renderItem);
}

Particle::Particle(PxVec3 pos, PxVec3 vel, Vector4 color, PxVec3 acel, double masa, double dumping, double duration, double size) :
	_v(vel), _color(color), _a(acel),
	_m(masa), _dump(dumping), _duration(duration), _size(size), _direction(PxVec3(1.0, 0.0, 0.0))
{
	//Creamos la forma con la geometria
	PxShape* sphere0 = CreateShape(PxSphereGeometry(_size));

	_transform = new PxTransform(PxVec3(pos.x, pos.y, pos.z));
	_renderItem = new RenderItem(sphere0, _transform, _color);

	RegisterRenderItem(_renderItem);
}



//Destructora
Particle::~Particle()
{
	if (_renderItem != nullptr)
	{
		DeregisterRenderItem(_renderItem);
		delete _renderItem;
		_renderItem = nullptr;
	}

	if (_transform != nullptr)
	{
		delete _transform;
		_transform = nullptr;
	}
}

void Particle::addForce(const PxVec3& force)
{
	_allForces += force;
}

void Particle::clearForce()
{
	_allForces = PxVec3(0, 0, 0);
}

void Particle::integrateEuler(double t)
{
	//MRU
	////x1 = x0 + v0 * t;
	//_transform->p += _v * t;

	//MRUA
	////x1 = x0 + v0 * t;
	////v1 = v0 + a * t
	//_transform->p += _v * t;
	//_v += _a * t;

	//Dumping
	////x1 = x0 + v0 * t;
	////v1 = v0 + a * t
	////v1 = v1 * d^t
	_transform->p += _v * t;
	_v += _a * t;
	_v *= pow(_dump, t);

}

void Particle::integrateSemiEuler(double t)
{
	//MRU
	////x1 = x0 + v0 * t;
	//_transform->p += _v * t;

	//MRUA
	////v1 = v0 + a * t
	////x1 = x0 + v0 * t;
	//_v += _a * t;
	//_transform->p += _v * t;

	//Dumping
	////v1 = v0 + a * t
	////v1 = v1 * d^t
	////x1 = x0 + v0 * t;
	_v += _a * t;
	_v *= pow(_dump, t);
	_transform->p += _v * t;
}

//void Particle::integrateVerlet(double t) //Se resuelve metiendo un pequenio delay
//{
//	//MRUA
//	////x1 = 2*x0 - x-1 + t^2 * a0;
//	////a1 =
//	//_v += _a * t;
//	//_transform->p += _v * t;
//
//	//Dumping
//	////x1 = 2*x(0) - x(-1) + t^2 * a(0);
//	////v1 = v0 + a * t
//	////v1 = v1 * d^t
//	//_v += _a * t;
//	//_v *= pow(_dump, t);
//	//_transform->p + _v * t;
//
//}

void Particle::integrate(double t, int integrationType)
{
	//Si no está activada no hacemos nada
	if (!_active) return;

	//Vamos reduciendo el tiempo de vida
	_duration -= t;

	// Si el tiempo de vida se acabó
	if (_duration <= 0.0)
	{
		//Lo desactivamos y forzamos vida a 0
		_duration = 0.0;

		// No borramos los objetos (permitir reutilización desde pool). Sólo desregistramos del render.
		_active = false;

		// Mover proyectil fuera de la vista
		if (_transform != nullptr)
			_transform->p = PxVec3(0, -500, 0);

		if (_renderItem != nullptr)
		{
			DeregisterRenderItem(_renderItem);

		}

		return;
	}

	//Teniendo en cuenta las fuerzas
	//Aceleracion = Fuerza / masa
	_a = _allForces / _m;

	// Si sigue viva, integrar
	switch (integrationType)
	{
		//Euler
	case 0: {
		integrateEuler(t);
		break;
	}
		//EulerSemimplicito
	case 1: {
		integrateSemiEuler(t);
		break;
	}
	//	//Verlet. Sin acabar
	//case 2: {
	//	integrateVerlet(t);
	//	break;
	//}
	default:{
		break;
	}
	}

	//Delay de cara a verlet
	//std::this_thread::sleep_for(std::chrono::milliseconds(50));


	//Despues de integrar, borramos las fuerzas
	clearForce();
}



