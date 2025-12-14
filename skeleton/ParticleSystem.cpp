#include "ParticleSystem.h"
#include <algorithm>

#include "ParticleGenerator.h"

ParticleSystem::ParticleSystem() : _useGravity(true), _paused(true)
{
	// Reservamos espacio inicial
	_particles.reserve(200);

	//Para el vector ilimitado - inicializamos con particulas basicas
	for (int i = 0; i < 200; i++)
	{
		Particle* p = new Particle(
			PxVec3(0, -500, 0),
			PxVec3(0, 0, 0),
			Vector4(1, 1, 1, 0));
		//Empiezan inactivas
		p->setActive(false);
		//Las aniade al pool
		addParticle(p);
	}
}

ParticleSystem::~ParticleSystem()
{
	//Vaciamos las fuerzas
	_forceRegister.clearRegister();

	//Vaciamos las particulas y las desactivamos
	for (Particle* p : _particles)
	{
		if (p != nullptr) p->setActive(false);

		delete p;
	}
	_particles.clear();

	//Vaciamos los generadores
	for (ParticleGenerator* g : _generators)
	{
		delete g;
	}
	_generators.clear();

}

void ParticleSystem::update(double t)
{
	//Aplicamos las fuerzas
	_forceRegister.update(t);

	//1. Actualizar las existentes
	for (Particle* p : _particles)
	{
		if (p->isActive())
		{
			//// Aplicar gravedad solo si este sistema la usa
			//if (_useGravity)
			//	p->setA(GRAVITY);
			//else
			//	p->setA(PxVec3(0)); // sin aceleración

			//if (_useGravity)
			//	p->addForce(GRAVITY * p->getM());

			// Integrar movimiento 
			p->integrate(t, 1);
		}
	}

	//2. Eliminar las particulas que se dejan de usar
	deleteDeadParticles();

	//3. Crear particulas nuevas
	for (ParticleGenerator* g : _generators)
	{
		g->generateParticles(*this, t);
	}

	//Gestion de la pausa
	//if (_paused)
	//{
	//	for (Particle* p : _particles)
	//	{
	//		p->setPos(PxVec3(0, -100, 0));
	//		
	//	}
	//}
}

void ParticleSystem::addParticle(Particle* p)
{
	//Si hay particula
	if (p != nullptr)
	{
		//Aniadimos la particula al sistema
		_particles.push_back(p);
	}
}

void ParticleSystem::addGenerator(ParticleGenerator* g)
{
	//Si hay generador
	if (g != nullptr)
	{
		//Aniadimos el generador al sistema
		_generators.push_back(g);
	}
}

void ParticleSystem::addForceGenerator(ForceGenerator* fGen)
{
	//Aniadimos el generador de fuerzas a cada particula del sistema
	for (Particle* p : _particles)
	{
		_forceRegister.add(p, fGen);
	}
}

void ParticleSystem::removeForceGenerator(ForceGenerator* fGen)
{
	if (!fGen) return;

	//Eliminamos el generador de fuerzas a cada particula del sistema
	for (Particle* p : _particles)
	{
		if (p) {
			_forceRegister.remove(p, fGen);
		}
	}
}

void ParticleSystem::clearForces()
{
	//Vaciamos las fuerzas del sistema
	_forceRegister.clearRegister();
}

void ParticleSystem::deleteDeadParticles()
{
	//Desactivamos las particulas que ya no valen
	for (Particle* p : _particles)
	{
		if (p->isActive())
		{
			// Desactivamos si esta fuera del mundo o sin vida
			if (p->getPos().x > 150.0 || p->getPos().x < -150.0 ||
				p->getPos().y < -150.0 || p->getPos().y > 150.0 ||
				p->getDuration() <= 0)
			{
				p->setActive(false);
			}
		}
	}
}

Particle* ParticleSystem::reactivateDeadParticles()
{

	//Desactivamos las particulas que ya no valen
	for (Particle* p : _particles)
	{
		if (!p->isActive())
		{
			return p;
		}
	}

	//Si todas estan vivas, no devuelve nada
	return nullptr;
	
}
