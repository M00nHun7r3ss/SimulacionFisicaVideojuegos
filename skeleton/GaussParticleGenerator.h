#pragma once
#include "ParticleGenerator.h"

class GaussParticleGenerator : ParticleGenerator
{
public:

    //Constructora
    GaussParticleGenerator(PxVec3 pos, PxVec3 medVel, PxVec3 desvVel, int nParticles);

    //Destructora
    ~GaussParticleGenerator();

    //Genera particulas en el sistema
    void generateParticles(ParticleSystem& system, double t) override;

    //Getters
    inline PxVec3 getMedia() { return _mediaVel; }
    inline PxVec3 getDesviacion() { return _desvVel; }

    //Setters
    inline void setMedia(PxVec3 med) { _mediaVel = med; }
    inline void setDesviacion(PxVec3 desv) { _desvVel = desv; }

private:

    PxVec3 _mediaVel; // Medias de velocidad
    PxVec3 _desvVel;  // Desviacion tipica de velocidad
};

