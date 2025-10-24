#include "WindForce.h"

WindForce::WindForce(double cDyn, double cStat, PxVec3* sObj, PxVec3* sWind, PxVec2* area)
	: _coefD(cDyn), _coefS(cStat), _speedObj(sObj), _speedWind(sWind), _area(area)
{
	_pressure = 0.5 * _coefD * 

	_force = _area * _pressure;
}
