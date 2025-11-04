#include "ParticleForceRegister.h"

ParticleForceRegister::ParticleForceRegister()
{
}

ParticleForceRegister::~ParticleForceRegister()
{
	//Elimina el registro entero
	clearRegister();
}

void ParticleForceRegister::add(Particle* p, ForceGenerator* fGen)
{
	//Si falta alguna de las dos, no hacemos nada
	if (p == nullptr || fGen == nullptr) return;

	//Si ha llegado hasta aqui, aniade el generador a la entrada de la particula
	_forceRegister[p].push_back(fGen);
}

void ParticleForceRegister::remove(Particle* p, ForceGenerator* fGen)
{
	//Si falta alguna de las dos, no hacemos nada
	if (p == nullptr || fGen == nullptr) return;

	//Busca la particula
	auto it = _forceRegister.find(p);
	//Si no se ha acabado el registro
	if (it != _forceRegister.end())
	{
		//Tomamos el segundo valor del map
		std::vector<ForceGenerator*>& generators = it->second;
		//Busca el concreto y lo borra
		generators.erase(std::remove(generators.begin(), generators.end(), fGen), generators.end());

		//Si dicha particula ya no tiene generadores de fuerza, quitamos la entrada relativa
		if (generators.empty()) 
		{
			clearParticle(p);
			}
	}

}

void ParticleForceRegister::clearRegister()
{
	//Vacia el registro
	_forceRegister.clear();
}

void ParticleForceRegister::clearParticle(Particle* p)
{
	//Si no hay particula sale
	if (p == nullptr) return;

	//Y si no, la borra del registro, asi como todas las entradas relacionadas a ella
	_forceRegister.erase(p);
}

void ParticleForceRegister::update(double t)
{
	//Recorre cada particula del registro y aplica las fuerzas que tenga
	for (std::pair<Particle* const, std::vector<ForceGenerator*>>& registerSpot : _forceRegister)
	{
		Particle* p = registerSpot.first;
		std::vector<ForceGenerator*>& generators = registerSpot.second;

		//Quita las fuerzas anteriores
		p->clearForce();

		//Aplica las del registro
		for (ForceGenerator* fGen : generators)
		{
			fGen->updateForce(p, t);
		}
	}

}
