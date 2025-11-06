#include "GaussParticleGenerator.h"

GaussParticleGenerator::GaussParticleGenerator(PxVec3 pos, PxVec3 medVel, PxVec3 desvVel, int nParticles) :
	_mediaVel(medVel), _desvVel(desvVel)
{
    _pos = pos;
    _nParticles = nParticles;

    _modelParticle = new Particle(PxVec3(0.0, 0.0, 0.0), PxVec3(0.0, 0.0, 0.0), 
        Vector4(1.0, 1.0, 1.0, 1.0), PxVec3(0.0, 0.0, 0.0), 1.0, 
        0.999, 5, 0.1);
}

GaussParticleGenerator::~GaussParticleGenerator()
{
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
            continue;

        //Calcula la posicion y la velocidad de la particula nueva
        PxVec3 vel(distX(_mersenneRandom), distY(_mersenneRandom), distZ(_mersenneRandom));

        //Y la aniade al sistema
        _modelParticle = system.reactivateDeadParticles();
        if (_modelParticle != nullptr)
        {
            _modelParticle->setPos(_pos);
            _modelParticle->setV(vel);
            _modelParticle->setColor(Vector4(1, 1, 1, 1));
            _modelParticle->setA(PxVec3(0, -9.8f, 0));
            _modelParticle->setM(0.1f);
            _modelParticle->setDump(0.999f);
            _modelParticle->setDuration(2.0f);
            _modelParticle->setSize(0.1);
            _modelParticle->setActive(true);

        }
    }
}
