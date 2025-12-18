#include "SolidGenerator.h"
#include "SolidSystem.h"

SolidGenerator::SolidGenerator(PxPhysics* physics)
    : gPhysics(physics),
    _shape(SolidShape::BOX),
    _materialType(SolidMaterialType::WOOD),
    _pos(0, 10, 0),
    _duration(5.0),
    _spawnTime(1.0),
    _timer(0.0)
{
}

void SolidGenerator::generate(SolidSystem& system, double t)
{
    //Avanzamos el tiempo
    _timer += t;

    //Cuando toque spawnear, lo spawmea
    if (_timer >= _spawnTime)
    {
        //Resetea el tiempo
        _timer = 0.0f;
        //Crea el solido
        PxRigidDynamic* solid = createSolid(system);
        //Lo aniade al sistema
        system.addSolid(solid, _render, _duration);
    }
}

PxRigidDynamic* SolidGenerator::createSolid(SolidSystem& system)
{
    //Usamos el tranform
    PxTransform transform(_pos);
    //Y generamos un cuerpo
    PxRigidDynamic* body = gPhysics->createRigidDynamic(transform);

    // Material y color
    PxMaterial* material = nullptr;
    Vector4 color;
    switch (_materialType)
    {
    case SolidMaterialType::WOOD:
        material = gPhysics->createMaterial(0.5f, 0.4f, 0.3f);
        color = Vector4(0.6f, 0.4f, 0.2f, 1.0f);
        break;
    case SolidMaterialType::METAL:
        material = gPhysics->createMaterial(0.2f, 0.1f, 0.05f);
        color = Vector4(0.7f, 0.7f, 0.8f, 1.0f);
        break;
    case SolidMaterialType::RUBBER:
        material = gPhysics->createMaterial(0.9f, 0.8f, 0.9f);
        color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
        break;
    }

    // Forma
    PxShape* shape = nullptr;
    switch (_shape)
    {
    case SolidShape::BOX:
        shape = gPhysics->createShape(PxBoxGeometry(1, 1, 1), *material);
        break;
    case SolidShape::SPHERE:
        shape = gPhysics->createShape(PxSphereGeometry(1), *material);
        break;
    }

    body->attachShape(*shape);


    //Masa e inercia automatica
    PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);

    //Masa e inercia manual
    /*
    body->setMass(10.0f);
    body->setMassSpaceInertiaTensor(PxVec3(4.0f, 4.0f, 4.0f));
    */

    //El damping
    body->setLinearDamping(0.1f);
    body->setAngularDamping(0.05f);

    // RenderItem
    _render = new RenderItem(shape, body, color);

    return body;
}
