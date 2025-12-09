#include "Scene.h"
#include <iostream>

#include "HierarchyParticleGenerator.h"

void Scene::enterScene()
{
	init();
}

void Scene::exitScene()
{
	cleanup();
}

// --- ESCENAS HIJAS ---
// Para ver las anteriores practicas basta con volver a los commits concretos.
//Voy a dejar aqui solo las escenas en las que estoy trabajando
// Scene0, Scene1, Scene2 ... 

// ---- SCENE 0 ----
Scene0::Scene0(PxMaterial* material) : gMaterial(material), _fixedPos(PxVec3(0, 50, 0)), _kFixed(100), _restLengthFixed(5), _k(100), _restLength(5)
{
}

void Scene0::init()
{
	///PARTE DE LOS MUELLES

	// ---------- OBJETO FIJO ----------
	//Creamos la geometria del objeto
	PxGeometry* box1 = new PxBoxGeometry(5 / 2, 5 / 2, 5 / 2);
	//Creamos la forma con la geometria
	PxShape* boxShape = CreateShape(*box1, gMaterial);
	//Creamos el transform, y el color
	PxTransform* tr1 = new PxTransform(_fixedPos);
	Vector4* color1 = new Vector4{ 0.0, 0.0, 1.0, 1.0 };
	//Renderizamos la base
	_fixedObject = new RenderItem(boxShape, tr1, *color1);
	//La registramos
	RegisterRenderItem(_fixedObject);
	_fixedObject->color = Vector4(0.2, 0.2, 0.5, 1.0);

	// ---------- PARTICULAS ----------
	a = new Particle(PxVec3(0, 40, 0), PxVec3(0, 0, 0), PxVec4(1, 0, 0, 1), PxVec3(0, 0, 0), 1, 0.1, 100, 1);
	b = new Particle(PxVec3(10, 40, 0), PxVec3(0, 0, 0), PxVec4(0, 1, 0, 1), PxVec3(0, 0, 0), 1, 0.1, 100, 1);

	//Para que funcione con sistemas de particulas
	_particleSystem = new ParticleSystem();
	_particleSystem->addParticle(a);
	_particleSystem->addParticle(b);
	_particleSystem->setPaused(false);

	// ---------- MUELLE FIJO - PARTICULA ----------
	_FixedSpringForce = new FixedSpringForceGenerator(_fixedPos, _kFixed, _restLengthFixed);
	_particleSystem->addForceGenerator(_FixedSpringForce);

	// ---------- MUELLE PARTICULA - PARTICULA ----------
	_SpringForce = new SpringForceGenerator(a, b, 50, 5);
	_particleSystem->addForceGenerator(_SpringForce);

	// ---------- GRAVEDAD ----------
	_gravityForce = new GravityForce(PxVec3(0, -9.8, 0));
	_particleSystem->addForceGenerator(_gravityForce);
}

void Scene0::update(double t)
{
	_particleSystem->update(t);
}

void Scene0::cleanup()
{
	delete _FixedSpringForce;
	_FixedSpringForce = NULL;

	delete _SpringForce;
	_SpringForce = NULL;

	delete _particleSystem;
	_particleSystem = NULL;
}

void Scene0::handleKey(unsigned char key, const PxTransform& camera)
{

	switch (toupper(key))
	{
		//K disminuye (Como minimo 0)
	case 'Q':
		_kFixed = max(0, _kFixed - 1);
		_FixedSpringForce->setK(_kFixed);
		std::cout << _kFixed;
		break;
		//K aumenta
	case 'W':
		_kFixed += 1;
		_FixedSpringForce->setK(_kFixed);
		std::cout << _kFixed;
		break;
		//Aniade una fuerza
	case 'E':
		a->addForce(PxVec3(200, 0, 0));
		break;

	default:
		break;
	}
}
