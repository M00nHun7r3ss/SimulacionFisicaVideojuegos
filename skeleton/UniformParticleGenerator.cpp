#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(PxVec3 pos, int nParticles, PxVec3 minPos, PxVec3 maxPos, PxVec3 minVel, PxVec3 maxVel) :
	_minPos(minPos), _maxPos(maxPos), _minVel(minVel), _maxVel(maxVel)
{
    _pos = pos;
    _nParticles = nParticles;

}

UniformParticleGenerator::~UniformParticleGenerator()
{
}

void UniformParticleGenerator::generateParticles(ParticleSystem & system, double t)
{
    //Sacamos la distribucion uniforme para la posicion, la velocidad y la probabilidad de aparicion
    std::uniform_real_distribution<float> distPosX(_minPos.x, _maxPos.x);
    std::uniform_real_distribution<float> distPosY(_minPos.y, _maxPos.y);
    std::uniform_real_distribution<float> distPosZ(_minPos.z, _maxPos.z);

    std::uniform_real_distribution<float> distVelX(_minVel.x, _maxVel.x);
    std::uniform_real_distribution<float> distVelY(_minVel.y, _maxVel.y);
    std::uniform_real_distribution<float> distVelZ(_minVel.z, _maxVel.z);

    std::uniform_real_distribution<float> distProb(0.0f, 1.0f);

    for (int i = 0; i < _nParticles; ++i)
    {
        // si no hay probabilidad suficiente, no hay particula nueva
        if (distProb(_mersenneRandom) < _probability)
            continue;

        //Calcula la posicion y la velocidad de la particula nueva
        PxVec3 pos = _pos + PxVec3(distPosX(_mersenneRandom), distPosY(_mersenneRandom), distPosZ(_mersenneRandom));
        PxVec3 vel = _vel + PxVec3(distVelX(_mersenneRandom), distVelY(_mersenneRandom), distVelZ(_mersenneRandom));

        //Y la aniade al sistema
        //Y la aniade al sistema
        Particle* p = system.reactivateDeadParticles();
        if (p != nullptr)
        {
            p->setPos(pos);
            p->setV(vel);
            p->setColor(Vector4(0.9, 0.9, 0.9, 0.25));
            p->setA(PxVec3(0, 0, 0));
            p->setM(0.1f);
            p->setDump(0.999f);
            p->setDuration(2.0f);
            p->setSize(0.05);
            p->setActive(true);

        }
    }
}
