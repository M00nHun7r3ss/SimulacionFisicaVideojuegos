#pragma once

#include <random>
#include "PxPhysicsAPI.h"
#include "SolidSystem.h"

using namespace physx;

enum class SolidShape
{
	BOX,
    SPHERE
};

enum class SolidMaterialType
{
    WOOD,
    METAL,
    RUBBER
};


class SolidGenerator
{
public:

    //Constructora
    SolidGenerator(PxPhysics* physics);

    //Destructora
    ~SolidGenerator() {}

    //Genera solidos en el sistema
    void generate(SolidSystem& system, double t);

    // Getters
    inline PxVec3 getPosition() const { return _pos; }
    inline double getDuration() const { return _duration; }

    //Setters
    void setPosition(const PxVec3& p) { _pos = p; }
    void setDuration(float t) { _duration = t; }
    void setSpawnTime(float t) { _spawnTime = t; }
    void setShape(SolidShape s) { _shape = s; }
    void setMaterial(SolidMaterialType m) { _materialType = m; }

private:

    //Crea los solidos que se generaran en el sistema, como una plantilla
    PxRigidDynamic* createSolid(SolidSystem& system);

    //Base de solidos rigidos
    PxPhysics* gPhysics;
    SolidShape _shape; //Se usara para PxGeometry
    SolidMaterialType _materialType; //Se usara para PxMaterial
    RenderItem* _render;

    PxVec3 _pos;
    double _duration;
    double _spawnTime;
    double _timer;
};
