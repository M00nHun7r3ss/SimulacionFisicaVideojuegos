#pragma once
#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
public:
    UniformParticleGenerator(PxVec3 pos, int nParticles, PxVec3 minPos, PxVec3 maxPos, PxVec3 minVel, PxVec3 maxVel);

    ~UniformParticleGenerator() override;

    void generateParticles(ParticleSystem& system, double t) override;

    //Getters
    PxVec3 setMinPosition() { return _minPos; }
    PxVec3 setMaxPosition() { return _maxPos; }
    PxVec3 setMinVelocity() { return _minVel; }
    PxVec3 setMaxVelocity() { return _maxVel; }

	//Setters
    inline void setMinPosition(PxVec3 minP) { _minPos = minP; }
    inline void setMaxPosition(PxVec3 maxP) { _maxPos = maxP; }
    inline void setMinVelocity(PxVec3 minV) { _minVel = minV; }
    inline void setMaxVelocity(PxVec3 maxV) { _maxVel = maxV; }

private:
    PxVec3 _minPos;
    PxVec3 _maxPos;
    PxVec3 _minVel;
    PxVec3 _maxVel;
};