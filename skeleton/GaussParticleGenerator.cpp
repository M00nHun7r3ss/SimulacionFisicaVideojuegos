#include "GaussParticleGenerator.h"

GaussParticleGenerator::GaussParticleGenerator(PxVec3 pos, PxVec3 medVel, PxVec3 desvVel, int nParticles) :
	_mediaVel(medVel), _desvVel(desvVel)
{
    _pos = pos;
    _nParticles = nParticles;
}

void GaussParticleGenerator::generateParticles(ParticleSystem& system, double t)
{
    //Sacamos la distribucion normal para los tres ejes
    std::normal_distribution<float> distX(_mediaVel.x, _desvVel.x);
    std::normal_distribution<float> distY(_mediaVel.y, _desvVel.y);
    std::normal_distribution<float> distZ(_mediaVel.z, _desvVel.z);

    //Y la uniforme para la probabilidad
    std::uniform_real_distribution<float> distProb(0.0f, 1.0f);

    for (int i = 0; i < _nParticles; ++i)
    {
        // si no hay probabilidad suficiente, no hay particula nueva
        if (distProb(_mersenneRandom) > _probability)
            return;

        //Calcula la posicion y la velocidad de la particula nueva
        PxVec3 vel(distX(_mersenneRandom), distY(_mersenneRandom), distZ(_mersenneRandom));

        //Y la aniade al sistema
        //system.addParticle(_pos, vel, Vector4(1, 1, 1, 1), PxVec3(0, -9.8f, 0), 0.1f, 1.0f, 0.999f, 3.0f);
    }
}
