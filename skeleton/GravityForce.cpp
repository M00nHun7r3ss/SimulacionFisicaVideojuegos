#include "GravityForce.h"

GravityForce::GravityForce(double mass1, double mass2, double radius) :
	ForceGenerator(mass1), _mass2(mass2), _radius(radius)
{
	_force->x = G * (_mass * _mass2) / pow(_radius, 2);
	_force->y = G * (_mass * _mass2) / pow(_radius, 2);
	_force->z = G * (_mass * _mass2) / pow(_radius, 2);
}
