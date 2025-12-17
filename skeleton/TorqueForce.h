#pragma once
#include "SolidForceGenerator.h"

class TorqueForce : public SolidForceGenerator
{
public:
    //Constructora
    TorqueForce(const PxVec3& force, const PxVec3& pointA, const PxVec3& pointB);

    //Destructora
    ~TorqueForce() {}

    //Update
    void updateForce(PxRigidDynamic* solid, double t) override;

private:
    PxVec3 _force;    
    PxVec3 _pointA;   // Origen primera fuerza
    PxVec3 _pointB;   // Origen segunda fuerza
};

