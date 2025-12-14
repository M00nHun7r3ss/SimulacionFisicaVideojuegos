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


	//// ---------- PARTICULAS ----------
	//a = new Particle(PxVec3(0, 40, 0), PxVec3(0, 0, 0), PxVec4(1, 0, 0, 1), PxVec3(0, 0, 0), 10, 0.1, 100, 1);
	//b = new Particle(PxVec3(10, 40, 0), PxVec3(0, 0, 0), PxVec4(0, 1, 0, 1), PxVec3(0, 0, 0), 1, 0.1, 100, 1);
	//a->setActive(true);
	//b->setActive(true);
	////Para que funcione con sistemas de particulas
	//_particleSystem = new ParticleSystem();
	//_particleSystem->addParticle(a);
	//_particleSystem->addParticle(b);
	//_particleSystem->setPaused(false);

	//_aGenerator = new UniformParticleGenerator(PxVec3(0, 40, 0), 1,
	//PxVec3(0, 40, 0), PxVec3(0, 40, 0),
	//PxVec3(0.0, -10.0, 0.0), PxVec3(0.0, 10.0, 0.0));
	//_aGenerator->setProbability(1);
	//_particleSystem->addGenerator(_aGenerator);

	//_bGenerator = new UniformParticleGenerator(PxVec3(10, 40, 0), 1,
	//	PxVec3(10, 40, 0), PxVec3(10, 40, 0),
	//	PxVec3(0.0, -10.0, 0.0), PxVec3(0.0, 10.0, 0.0));
	//_bGenerator->setProbability(1);
	//_particleSystem->addGenerator(_bGenerator);

	//// ---------- MUELLE FIJO - PARTICULA ----------
	//_FixedSpringForce = new FixedSpringForceGenerator(_fixedPos, a, _kFixed, _restLengthFixed);
	//_particleSystem->addForceGenerator(_FixedSpringForce);

	//// ---------- MUELLE PARTICULA - PARTICULA ----------
	//_SpringForce = new SpringForceGenerator(a, b, _k, 5);
	//_particleSystem->addForceGenerator(_SpringForce);

	//// ---------- GRAVEDAD ----------
	//_gravityForce = new GravityForce(PxVec3(0, -9.8, 0));
	//_particleSystem->addForceGenerator(_gravityForce);

	 _lateralForce = new WindForce(PxVec3(20, 0, 0), 1.2, 0.5, 1, PxVec3(-100, -100, -100), PxVec3(100, 100, 100));

	// - EJERCICIO OPCIONAL SLINKY -
	int count = 5;
	float separation = 10.0f;

	_particleSystem = new ParticleSystem();

	//Creamos las particulas
	for (int i = 0; i < count; i++) {
		Particle* p = new Particle(
			PxVec3(0, _fixedPos.y + separation * i, 0),  
			PxVec3(0, 0, 0),                    
			PxVec4(1, 1, 0, 1),                 
			PxVec3(0, 0, 0),             
			1.0f,                            
			0.1f,                           
			100.0f,                             
			1.0f);
		p->setActive(true);
		_slinky.push_back(p);
		_particleSystem->addParticle(p);
	}

	_particleSystem->setPaused(false);

	//Creamos los muelles
	// ---------- MUELLE FIJO - PARTICULA ----------
	_FixedSpringForce = new FixedSpringForceGenerator(_fixedPos, _slinky[0], _kFixed, _restLengthFixed);
	_particleSystem->addForceGenerator(_FixedSpringForce);

	// ---------- MUELLE PARTICULA - PARTICULA ----------
	for (int i = 0; i < count - 1; i++) {
		SpringForceGenerator* spring = new SpringForceGenerator(
			_slinky[i],
			_slinky[i + 1],
			_k,
			_restLength
		);
		_particleSystem->addForceGenerator(spring);
	}

	//Gravedad
	_gravityForce = new GravityForce(PxVec3(0, -9.8, 0));
	_particleSystem->addForceGenerator(_gravityForce);

	// - EJERCICIO OPCIONAL SLINKY -

	// ---------- PARTICULAS ----------
	//a = new Particle(PxVec3(0, 40, 0), PxVec3(0, 0, 0), PxVec4(1, 0, 0, 1), PxVec3(0, 0, 0), 1, 0.1, 100, 1);
	//b = new Particle(PxVec3(10, 40, 0), PxVec3(0, 0, 0), PxVec4(0, 1, 0, 1), PxVec3(0, 0, 0), 1, 0.1, 100, 1);

	// - EJERCICIO OPCIONAL SLINKY -
	int count = 5;
	float separation = 3.0f;

	_particleSystem = new ParticleSystem();

	//Creamos las partivulas
	for (int i = 0; i < count; i++) {
		Particle* p = new Particle(
			PxVec3(0, 50 - i * separation, 0),  
			PxVec3(0, 0, 0),                    
			PxVec4(1, 1, 0, 1),                 
			PxVec3(0, 0, 0),             
			1.0f,                            
			0.1f,                           
			100.0f,                             
			1.0f);                          
		_slinky.push_back(p);
		_particleSystem->addParticle(p);
	}

	_particleSystem->setPaused(false);

	//Creamos los muelles
	float k = 80.0f;    
	float restLength = separation; 

	for (int i = 0; i < count - 1; i++) {
		SpringForceGenerator* spring = new SpringForceGenerator(
			_slinky[i],
			_slinky[i + 1],
			k,
			restLength
		);
		_particleSystem->addForceGenerator(spring);
	}

	//Gravedad
	_gravityForce = new GravityForce(PxVec3(0, -9.8, 0));
	_particleSystem->addForceGenerator(_gravityForce);


	////Para que funcione con sistemas de particulas
	//_particleSystem = new ParticleSystem();
	//_particleSystem->addParticle(a);
	//_particleSystem->addParticle(b);
	//_particleSystem->setPaused(false);

	//_aGenerator = new UniformParticleGenerator(PxVec3(0, 40, 0), 1,
	//	PxVec3(0, 40, 0), PxVec3(0, 40, 0),
	//PxVec3(0.0, -10.0, 0.0), PxVec3(0.0, 10.0, 0.0));
	//_aGenerator->setProbability(1);
	//_particleSystem->addGenerator(_aGenerator);

	//_bGenerator = new UniformParticleGenerator(PxVec3(10, 40, 0), 1,
	//	PxVec3(10, 40, 0), PxVec3(10, 40, 0),
	//	PxVec3(0.0, -10.0, 0.0), PxVec3(0.0, 10.0, 0.0));
	//_bGenerator->setProbability(1);
	//_particleSystem->addGenerator(_bGenerator);

	//// ---------- MUELLE FIJO - PARTICULA ----------
	//_FixedSpringForce = new FixedSpringForceGenerator(_fixedPos, _kFixed, _restLengthFixed);
	//_particleSystem->addForceGenerator(_FixedSpringForce);

	//// ---------- MUELLE PARTICULA - PARTICULA ----------
	//_SpringForce = new SpringForceGenerator(a, b, 50, 5);
	//_particleSystem->addForceGenerator(_SpringForce);

	//// ---------- GRAVEDAD ----------
	//_gravityForce = new GravityForce(PxVec3(0, -9.8, 0));
	//_particleSystem->addForceGenerator(_gravityForce);

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
