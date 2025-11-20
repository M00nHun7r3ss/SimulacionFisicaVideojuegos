#pragma once
#include "ParticleGenerator.h"

class HierarchyParticleGenerator : public ParticleGenerator
{
public:

    //Constructora
    HierarchyParticleGenerator(PxVec3 pos);

    //Destructora
    ~HierarchyParticleGenerator() override;

    //Genera particulas en el sistema
    void generateParticles(ParticleSystem& system, double t) override;

private:
    bool _processStarted = false; //Para saber si la particula inicial ya esta en marcha
    Particle* _firstParticle = nullptr;  //Particula inicial

};

