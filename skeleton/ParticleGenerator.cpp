#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator() : _nParticles(1), _pos(0, 0, 0), _vel(0, 0, 0),
    _duration(5.0), _probability(1.0),
    _mersenneRandom(std::random_device{}()),
    uniformDistribution(0, 100)
{
    _modelParticle = new Particle(PxVec3(0.0, 0.0, 0.0), PxVec3(0.0, 0.0, 0.0),
        Vector4(1.0, 1.0, 1.0, 1.0), PxVec3(0.0, 0.0, 0.0), 1.0,
        0.999, 5, 0.1);
}
