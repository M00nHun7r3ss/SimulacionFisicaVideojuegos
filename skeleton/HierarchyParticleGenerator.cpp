#include "HierarchyParticleGenerator.h"

HierarchyParticleGenerator::HierarchyParticleGenerator(PxVec3 pos)
{
    //El origen
    _pos = pos;
    // Solo generamos 1
    _nParticles = 1;
    // Se genera siempre
    _probability = 1.0f;        
}

HierarchyParticleGenerator::~HierarchyParticleGenerator()
{
}

void HierarchyParticleGenerator::generateParticles(ParticleSystem& system, double t)
{
    // Si aun no lanzamos el cohete
    if (!_processStarted)
    {
        //Coge particlas
        _firstParticle = system.reactivateDeadParticles();
        if (_firstParticle != nullptr)
        {
            //Empieza en origen
            _firstParticle->setPos(_pos);
            //Sube
            _firstParticle->setV(PxVec3(0, 25, 0));
            //Blanco. Todo Cambiar
            _firstParticle->setColor(Vector4(1, 1, 1, 1));
            _firstParticle->setDuration(2.0f);
            _firstParticle->setSize(0.2f);
            _firstParticle->setActive(true);

            _processStarted = true;
        }

        return;
    }

    // Si ya se ha disparado, y ademas, ha desaparecido
    if (_processStarted && _firstParticle != nullptr && !_firstParticle->isActive())
    {
        // Generamos partículas hijas (en plan explosion)
        std::uniform_real_distribution<float> vel(-15, 15);

        for (int i = 0; i < 30; i++)
        {
            Particle* p = system.reactivateDeadParticles();
            if (p != nullptr)
            {
                //Desde la posicion de la primera particula
                p->setPos(_firstParticle->getPos());

                //En direcciones aleatorias
                p->setV(PxVec3(vel(_mersenneRandom), vel(_mersenneRandom), vel(_mersenneRandom)));

                //Blanco, todo cambiar
                p->setColor(Vector4(1, 0.3, 0.1, 1));
                p->setDuration(1.5f);
                p->setSize(0.1f);
                p->setDump(0.98f);
                p->setActive(true);
            }
        }

        // Listo reiniciamos para lanzar otro 
        _processStarted = false;
    }
}
