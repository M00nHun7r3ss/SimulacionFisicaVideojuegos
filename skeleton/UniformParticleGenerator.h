#pragma once
#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator
{
public:
    UniformParticleGenerator();

    ~UniformParticleGenerator() override;

    void generateParticles(ParticleSystem& system, double t) override;

    //Getters
    double setMinPosition() { return _minPos; }
    double setMaxPosition() { return _maxPos; }
    double setMinVelocity() { return _minVel; }
    double setMaxVelocity() { return _maxVel; }

	//Setters
    inline void setMinPosition(double minP) { _minPos = minP; }
    inline void setMaxPosition(double maxP) { _maxPos = maxP; }
    inline void setMinVelocity(double minV) { _minVel = minV; }
    inline void setMaxVelocity(double maxV) { _maxVel = maxV; }

private:
    double _minPos;
    double _maxPos;
    double _minVel;
    double _maxVel;
};