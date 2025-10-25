#include "ParticleSystem.h"
#include <algorithm>

#include "ParticleGenerator.h"

ParticleSystem::ParticleSystem() 
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
		_particles.back()->setActive(false);
		//Las aniade al pool
		addParticle(p);
	}
}

ParticleSystem::~ParticleSystem()
{
	//Vaciamos las particulas y las desactivamos
	for (Particle* p : _particles)
	{
		delete p;
		p->setActive(false);
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
	//1. Actualizar las existentes
	for (Particle* p : _particles)
	{
		if (p->isActive())
		{
			// Aplicar gravedad
			p->setA(GRAVITY);

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
