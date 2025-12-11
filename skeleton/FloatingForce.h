#pragma once
#include "ForceGenerator.h"

class FloatingForce : public ForceGenerator
{
public:
    FloatingForce(float waterHeight, float height, float volume, float liquidDensity = 1000.0f);

    void updateForce(Particle* p, double t) override;

    inline void setVolume(float v) { _volume = v; }
    inline void setHeight(float h) { _height = h; }

private:
    float _waterHeight;
    float _height;
    float _volume;
    float _liquidDensity;
};