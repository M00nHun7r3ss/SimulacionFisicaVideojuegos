#include "SolidForceRegister.h"
#include <algorithm>

SolidForceRegister::~SolidForceRegister()
{
	clearRegister();
}

void SolidForceRegister::update(double t)
{
    //Recorre las entradas del registro
    for (auto& it : _forceRegister)
    {
        PxRigidDynamic* solid = it.first;
        std::vector<SolidForceGenerator*>& forces = it.second;

        //Si no hay solido, continua
        if (!solid) continue;

        //Recorre las fuerzas
        for (SolidForceGenerator* f : forces)
        {
            if (f)
            {
                //Y las actualiza para cada solido valido
            	f->updateForce(solid, t);
            }
        }
    }
}

void SolidForceRegister::add(PxRigidDynamic* body, SolidForceGenerator* fGen)
{
    //Si no hay solido o fuerzas, no podemos hacer nada
    if (!body || !fGen)
    {
        return;
    }

    //Recoge las fuerzas de un cuerpo concreto
    std::vector<SolidForceGenerator*>& forces = _forceRegister[body];

    //Busca entre ellas y si no esta, aniade la nueva
    if (std::find(forces.begin(), forces.end(), fGen) == forces.end())
    {
        forces.push_back(fGen);
    }
}

void SolidForceRegister::remove(PxRigidDynamic* body, SolidForceGenerator* fGen)
{
    //Si no hay solido o fuerzas, no podemos hacer nada
    if (!body || !fGen)
    {
        return;
    }

    //Buscamos el cuerpo concreto para dicha fuerza
    std::map<PxRigidDynamic*, std::vector<SolidForceGenerator*>>::iterator it = _forceRegister.find(body);
    //Si no esta, no podemos hacer nada
    if (it == _forceRegister.end())
    {
        return;
    }

    //Y borrara la fuerza correspondiente en caso de encontrarlo
    std::vector<SolidForceGenerator*>& forces = it->second;
    forces.erase(
        std::remove(forces.begin(), forces.end(), fGen),
        forces.end()
    );

    if (forces.empty())
        _forceRegister.erase(it);
}

void SolidForceRegister::clearRegister()
{
    _forceRegister.clear();
}

void SolidForceRegister::clearSolid(PxRigidDynamic* body)
{
    _forceRegister.erase(body);
}
