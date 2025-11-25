#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{

public:
    SpringForceGenerator(Particle* a, Particle* b, float k, float restLength);

    virtual void updateForce(Particle* p, double dt) override;

private:
    Particle* _a;
    Particle* _b;
    float _k;
    float _restLength;
};

