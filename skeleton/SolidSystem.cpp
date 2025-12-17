#include "SolidSystem.h"
#include "SolidGenerator.h"
#include <algorithm>

SolidSystem::SolidSystem(PxPhysics* physics, PxScene* scene) : gPhysics(physics), gScene(scene), _useGravity(true)
{
	// Reservamos espacio inicial
    _solids.reserve(20);
}

SolidSystem::~SolidSystem()
{
    //Vaciamos las fuerzas
    clearForces();

    //Liberamos los solidos
    for (SolidData& s : _solids)
    {
        if (s.render)
        {
            s.render->release();
            s.render = nullptr;
        }

        if (s.solid)
        {
            //gScene->removeActor(*s.solid);
            s.solid->release();
            s.solid = nullptr;
        }
    }
    _solids.clear();

    //Vaciamos los generadores
    for (SolidGenerator* g : _generators)
    {
        delete g;
    }
    _generators.clear();

}

void SolidSystem::update(double t)
{
    //Aplicamos las fuerzas
    _forceRegister.update(t);
    //Y la gravedad
    applyGravityState();

	//1. Actualizar las existentes
    //Se actualizan en el bucle principal del main

    // 2.  Eliminar los solidos que se dejan de usar
    deleteDeadSolids(t);

    //// 3. Crear solidos nuevos
    for (SolidGenerator* g : _generators)
    {
        g->generate(*this, t);
    }
}

void SolidSystem::addSolid(PxRigidDynamic* solid, RenderItem* render, double duration)
{
    //Si no hay solido, no podemos hacer nada
    if (!solid) return;

    SolidData s;
    s.solid = solid;
    s.render = render;
    s.duration = duration;

	//Pero si lo hay, aniadimos el solido al sistema
    gScene->addActor(*solid);
    _solids.push_back(s);
}

void SolidSystem::addGenerator(SolidGenerator* g)
{
    //Si no hay generador, no podemos hacer nada
    if (!g) return;

    //Pero si lo hay, aniadimos el generador al sistema
    _generators.push_back(g);
}

void SolidSystem::deleteDeadSolids(double t)
{
    //Recorre los solidos
    for (int i = 0; i < _solids.size(); )
    {
        //Si ya no existe el actor en escena
        if (!_solids[i].solid)
        {
            _solids.erase(_solids.begin() + i);
            continue;
        }

        //Reduce vida
        _solids[i].duration -= t;

        //Toma su posicion
        PxVec3 pos = _solids[i].solid->getGlobalPose().p;

        //Si han llegado a 0 o a posiciones invalidas, lo borran
        if (_solids[i].duration <= 0.0f ||
            pos.y < -200.0f || pos.y > 200.0f ||
            pos.x < -200.0f || pos.x > 200.0f)
        {
            //Los libera
            if (_solids[i].render)
            {
                _solids[i].render->release();  
                _solids[i].render = nullptr;
            }

            gScene->removeActor(*_solids[i].solid);
            _solids[i].solid->release();
            _solids[i].solid = nullptr;

            _solids.erase(_solids.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}

void SolidSystem::applyGravityState()
{
    //Activa o desactiva la gravedad
    for (SolidData& s : _solids)
    {
        if (s.solid)
        {
            s.solid->setActorFlag(
                PxActorFlag::eDISABLE_GRAVITY,
                !_useGravity
            );
        }
    }
}

void SolidSystem::addForceGenerator(PxRigidDynamic* solid, SolidForceGenerator* fGen)
{
    _forceRegister.add(solid, fGen);
}

void SolidSystem::removeForceGenerator(PxRigidDynamic* solid, SolidForceGenerator* fGen)
{
    _forceRegister.remove(solid, fGen);
}

void SolidSystem::clearForces()
{
    _forceRegister.clearRegister();
}

//void SolidSystem::registerRenderItem(PxRigidDynamic* solid, RenderItem* item) {
//    _renderMap[solid] = item;
//    RegisterRenderItem(item); 
//}
//
//void SolidSystem::deregisterRenderItem(PxRigidDynamic* solid) {
//    auto it = _renderMap.find(solid);
//    if (it != _renderMap.end())
//    {
//        //DeregisterRenderItem(it->second);
//        it->second->release();
//        _renderMap.erase(it);
//    }
//}