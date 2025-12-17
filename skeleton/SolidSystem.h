#pragma once
#include <vector> //Para el vector de solidos
#include <PxRigidDynamic.h> //Para los solidos dinamicos
#include <map>
#include "SolidForceRegister.h"

class SolidGenerator;

using namespace physx;

struct SolidData
{
    PxRigidDynamic* solid;
    double duration;
};

class SolidSystem
{
public:
    //Constructora
    SolidSystem(PxPhysics* physics, PxScene* scene);

    //Destructora
    ~SolidSystem();

    //Ciclo de vida de los solidos 
        //1. Actualizar los existentes
        //2. Eliminar los solidos que se dejan de usar
        //3. Crear solidos nuevos
    void update(double t);

    // Aniadir elementos
    void addSolid(PxRigidDynamic* solid, double duration);
    void addGenerator(SolidGenerator* g);

    // Gestionar fuerzas
    void addForceGenerator(PxRigidDynamic* solid, SolidForceGenerator* fGen);
    void removeForceGenerator(PxRigidDynamic* solid, SolidForceGenerator* fGen);
    void clearForces();

    // Getters
    inline int numSolids() const { return _solids.size(); }
    inline int numGenerators() const { return _generators.size(); }
    inline bool getUseGravity() const { return _useGravity; }
    inline PxPhysics* getPhysics() const { return gPhysics; }

    // Setters
    inline void setUseGravity(bool newGravity) { _useGravity = newGravity; }

    // Limpiar particulas en desuso
    void deleteDeadSolids(double t);

    //Para la gravedad
    void applyGravityState();

    //Para el render
    void registerRenderItem(PxRigidDynamic* solid, RenderItem* item);
    void deregisterRenderItem(PxRigidDynamic* solid);

protected:

    //Gravedad por defecto
    const PxVec3 GRAVITY = PxVec3(0.0f, -10.0f, 0.0f);
    bool _useGravity; //Por si queremos desactivarla
    std::vector<SolidData> _solids;
    std::vector<SolidGenerator*> _generators;

    PxPhysics* gPhysics = NULL;
    PxScene* gScene = NULL;

    //Para los renderItem de cada solido del sistema
    std::map<PxRigidDynamic*, RenderItem*> _renderMap;

    //Para gestionar las fuerzas
    SolidForceRegister _forceRegister;

};
