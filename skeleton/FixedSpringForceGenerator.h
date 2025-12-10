#pragma once
#include "ForceGenerator.h"

class FixedSpringForceGenerator : public ForceGenerator
{

public:
    FixedSpringForceGenerator(PxVec3 fixed, Particle* p, float k, float restLength);

    virtual void updateForce(Particle* p, double dt) override;

    //Getters
    inline float getK() const { return _k; }

    //Setters
	inline void setK(float k) { _k = k; }

private:
    PxVec3 _fixed;
    Particle* _p;
    float _k;
    float _restLength;
};


