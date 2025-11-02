#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator() :
	_minPos(-1.5), _maxPos(1.5), _minVel(-2.0), _maxVel(2.0)
{}

UniformParticleGenerator::~UniformParticleGenerator()
{
}

void UniformParticleGenerator::generateParticles(ParticleSystem & system, double t)
{
    //Sacamos la distribucion uniforme para la posicion, la velocidad y la probabilidad de aparicion
    std::uniform_real_distribution<float> distPos(_minPos, _maxPos);
    std::uniform_real_distribution<float> distVel(_minVel, _maxVel);
    std::uniform_real_distribution<float> distProb(0.0f, 1.0f);

    for (int i = 0; i < _nParticles; ++i)
    {
        // si no hay probabilidad suficiente, no hay particula nueva
        if (distProb(_mersenneRandom) < _probability)
            return;

        //Calcula la posicion y la velocidad de la particula nueva
        PxVec3 pos = _pos + PxVec3(distPos(_mersenneRandom), distPos(_mersenneRandom), distPos(_mersenneRandom));
        PxVec3 vel = _vel + PxVec3(distVel(_mersenneRandom), distVel(_mersenneRandom), distVel(_mersenneRandom));

        //Y la aniade al sistema
        Particle* p = new Particle(pos, vel, Vector4(1, 1, 1, 1), PxVec3(0, -9.8f, 0), 0.1, 1.0, 0.999, _duration);
        system.addParticle(p);
    }
}
