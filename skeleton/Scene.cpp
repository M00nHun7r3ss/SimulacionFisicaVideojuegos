#include "Scene.h"
#include <iostream>

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
Scene0::Scene0(PxMaterial* material) : gMaterial(material),
/*_fixedPos(PxVec3(0, 50, 0)), _kFixed(10), _restLengthFixed(5), _k(10), _restLength(5)*/ //MUELLES
_waterHeight(30.0f), _mass(4000.0f), _volume(0.0f) //FLOTACION
{
}

void Scene0::init()
{
	//// -------------------- PARTE DE LOS MUELLES --------------------

	//// ---------- OBJETO FIJO ----------
	////Creamos la geometria del objeto
	//PxGeometry* box1 = new PxBoxGeometry(5 / 2, 5 / 2, 5 / 2);
	////Creamos la forma con la geometria
	//PxShape* boxShape = CreateShape(*box1, gMaterial);
	////Creamos el transform, y el color
	//PxTransform* tr1 = new PxTransform(_fixedPos);
	//Vector4* color1 = new Vector4{ 0.0, 0.0, 1.0, 1.0 };
	////Renderizamos la base
	//_fixedObject = new RenderItem(boxShape, tr1, *color1);
	////La registramos
	//RegisterRenderItem(_fixedObject);
	//_fixedObject->color = Vector4(0.2, 0.2, 0.5, 1.0);

	////// ---------- PARTICULAS ----------
	////a = new Particle(PxVec3(0, 40, 0), PxVec3(0, 0, 0), PxVec4(1, 0, 0, 1), PxVec3(0, 0, 0), 10, 0.1, 100, 1);
	////b = new Particle(PxVec3(10, 40, 0), PxVec3(0, 0, 0), PxVec4(0, 1, 0, 1), PxVec3(0, 0, 0), 1, 0.1, 100, 1);
	////a->setActive(true);
	////b->setActive(true);
	//////Para que funcione con sistemas de particulas
	////_particleSystem = new ParticleSystem();
	////_particleSystem->addParticle(a);
	////_particleSystem->addParticle(b);
	////_particleSystem->setPaused(false);

	////_aGenerator = new UniformParticleGenerator(PxVec3(0, 40, 0), 1,
	////PxVec3(0, 40, 0), PxVec3(0, 40, 0),
	////PxVec3(0.0, -10.0, 0.0), PxVec3(0.0, 10.0, 0.0));
	////_aGenerator->setProbability(1);
	////_particleSystem->addGenerator(_aGenerator);

	////_bGenerator = new UniformParticleGenerator(PxVec3(10, 40, 0), 1,
	////	PxVec3(10, 40, 0), PxVec3(10, 40, 0),
	////	PxVec3(0.0, -10.0, 0.0), PxVec3(0.0, 10.0, 0.0));
	////_bGenerator->setProbability(1);
	////_particleSystem->addGenerator(_bGenerator);

	////// ---------- MUELLE FIJO - PARTICULA ----------
	////_FixedSpringForce = new FixedSpringForceGenerator(_fixedPos, a, _kFixed, _restLengthFixed);
	////_particleSystem->addForceGenerator(_FixedSpringForce);

	////// ---------- MUELLE PARTICULA - PARTICULA ----------
	////_SpringForce = new SpringForceGenerator(a, b, _k, 5);
	////_particleSystem->addForceGenerator(_SpringForce);

	////// ---------- GRAVEDAD ----------
	////_gravityForce = new GravityForce(PxVec3(0, -9.8, 0));
	////_particleSystem->addForceGenerator(_gravityForce);

	// _lateralForce = new WindForce(PxVec3(20, 0, 0), 1.2, 0.5, 1, PxVec3(-100, -100, -100), PxVec3(100, 100, 100));

	//// - EJERCICIO OPCIONAL SLINKY -
	//int count = 5;
	//float separation = 10.0f;

	//_particleSystem = new ParticleSystem();

	////Creamos las particulas
	//for (int i = 0; i < count; i++) {
	//	Particle* p = new Particle(
	//		PxVec3(0, _fixedPos.y + separation * i, 0),  
	//		PxVec3(0, 0, 0),                    
	//		PxVec4(1, 1, 0, 1),                 
	//		PxVec3(0, 0, 0),             
	//		1.0f,                            
	//		0.1f,                           
	//		100.0f,                             
	//		1.0f);
	//	p->setActive(true);
	//	_slinky.push_back(p);
	//	_particleSystem->addParticle(p);
	//}

	//_particleSystem->setPaused(false);

	////Creamos los muelles
	//// ---------- MUELLE FIJO - PARTICULA ----------
	//_FixedSpringForce = new FixedSpringForceGenerator(_fixedPos, _slinky[0], _kFixed, _restLengthFixed);
	//_particleSystem->addForceGenerator(_FixedSpringForce);

	//// ---------- MUELLE PARTICULA - PARTICULA ----------
	//for (int i = 0; i < count - 1; i++) {
	//	SpringForceGenerator* spring = new SpringForceGenerator(
	//		_slinky[i],
	//		_slinky[i + 1],
	//		_k,
	//		_restLength
	//	);
	//	_particleSystem->addForceGenerator(spring);
	//}

	////Gravedad
	//_gravityForce = new GravityForce(PxVec3(0, -9.8, 0));
	//_particleSystem->addForceGenerator(_gravityForce);

	//// - EJERCICIO OPCIONAL SLINKY -

	//// -------------------- PARTE DE LOS MUELLES --------------------

	// -------------------- PARTE DE FLOTACION --------------------

	// ---------- SUPERFICIE DEL AGUA ----------
	//Creamos la geometria del objeto
	PxGeometry* waterGeom = new PxBoxGeometry(50.0f, 0.05f, 50.0f);
	//Creamos la forma con la geometria
	PxShape* waterShape = CreateShape(*waterGeom, gMaterial);
	//Creamos el transform, y el color
	PxTransform* waterTr = new PxTransform(PxVec3(0, _waterHeight, 0));
	Vector4* waterColor = new Vector4(0.0f, 0.5f, 1.0f, 0.1f);
	//Renderizamos la base
	_waterPlane = new RenderItem(waterShape, waterTr, *waterColor);
	//La registramos
	RegisterRenderItem(_waterPlane);

	// ---------- CUBO ----------
	//Altura del cubo
	float objectSize = 2.0f;
	//Creamos la geometria del objeto

	PxGeometry* boxGeom = new PxBoxGeometry(objectSize /2.0f, objectSize / 2.0f, objectSize / 2.0f);
	//Creamos la forma con la geometria
	PxShape* boxShape = CreateShape(*boxGeom, gMaterial);
	//Creamos el transform, y el color
	PxTransform* boxTr = new PxTransform(PxVec3(0, _waterHeight, 0));
	Vector4* boxColor = new Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	//Renderizamos la base
	_floatingBox = new RenderItem(boxShape, boxTr, *boxColor);
	//La registramos
	RegisterRenderItem(_floatingBox);

	//Y particula relacionada, que sera la que se vera sometida a las fuerzas de flotacion
	_particleSystem = new ParticleSystem();
	_floatingParticle = new Particle(
		PxVec3(0, _waterHeight, 0),
		PxVec3(0, 0, 0),
		PxVec4(1, 1, 1, 1),
		PxVec3(0, 0, 0),
		_mass,
		0.3f,
		100.0f,
		1.0f
	);
	_floatingParticle->setActive(true);
	_particleSystem->addParticle(_floatingParticle);
	_particleSystem->setPaused(false);

	// Gravedad
	_gravityForce = new GravityForce(PxVec3(0, -9.8f, 0));
	_particleSystem->addForceGenerator(_gravityForce);

	_volume = objectSize * objectSize * objectSize;
	// Flotación
	_floatingForce = new FloatingForce(
		_waterHeight,
		objectSize,
		_volume,
		1000.0f
	);
	_particleSystem->addForceGenerator(_floatingForce);
}

void Scene0::update(double t)
{
	//// -------------------- PARTE DE LOS MUELLES --------------------
	//_particleSystem->update(t);

	//if (_windActive) {
	//	_windTimer -= t;
	//	if (_windTimer <= 0) {
	//		_particleSystem->removeForceGenerator(_lateralForce);
	//		_windActive = false;
	//	}
	//}
	// -------------------- PARTE DE LOS MUELLES --------------------
	_particleSystem->update(t);
	_floatingBox->transform = new PxTransform(_floatingParticle->getPos());
}

void Scene0::cleanup()
{
	// -------------------- PARTE DE LOS MUELLES --------------------

	//delete _particleSystem;
	//_particleSystem = NULL;

	//delete a;
	//a = NULL;

	//delete b;
	//b = NULL;

	//DeregisterRenderItem(_fixedObject);
	//_fixedObject = nullptr;

	//for (int i = 0; i < _slinky.size(); i++)
	//{
	//	delete _slinky[i];
	//	_slinky[i] = nullptr;
	//}
	//_slinky.clear();

	//// -------------------- PARTE DE LOS MUELLES --------------------

	// -------------------- PARTE DE FLOTACION --------------------
	DeregisterRenderItem(_waterPlane);
	_waterPlane = nullptr;

	DeregisterRenderItem(_floatingBox);
	_floatingBox = nullptr;

	delete _floatingParticle;
	_floatingParticle = nullptr;

	delete _particleSystem;
	_particleSystem = nullptr;

}

void Scene0::handleKey(unsigned char key, const PxTransform& camera)
{

	switch (toupper(key))
	{
		//// -------------------- PARTE DE LOS MUELLES --------------------
	//	//K disminuye (Como minimo 0)
	//case 'Q':
	//	_kFixed = max(0, _kFixed - 1);
	//	_FixedSpringForce->setK(_kFixed);
	//	break;
	//	//K aumenta
	//case 'W':
	//	_kFixed += 1;
	//	_FixedSpringForce->setK(_kFixed);
	//	break;
	//	//Aniade una fuerza
	//case 'E':
	//	if (!_windActive) {
	//		_particleSystem->addForceGenerator(_lateralForce);
	//		_windActive = true;
	//		_windTimer = 2.0;
	//	}
	//	break;
		// -------------------- PARTE DE FLOTACION --------------------

		//Bajar masa
	case 'R':
		_mass -= 100;
		//Dado que se trata de un cuerpo "realista" no puede tener masa 0, ponemos una masa simbolica pequenia
		if (_mass <= 0) _mass = 0.01; 
		_floatingParticle->setM(_mass);
		std::cout << "Masa: " << _mass << std::endl;
	break;
		//Subir masa
	case 'T':
		_mass += 100;
		_floatingParticle->setM(_mass);
		std::cout << "Masa: " << _mass << std::endl;
		break;
		//Bajar volumen
	case 'Y':
		_volume -= 1;
		//Dado que se trata de un cuerpo "realista" no puede tener volumen 0, ponemos un volumen simbolica pequenia
		if (_volume <= 0) _volume = 0.01;
		_floatingForce->setVolume(_volume);
		std::cout << "Volumen: " << _volume << std::endl;
		break;
		//Subir volumen
	case 'U':
		_volume += 1;
		_floatingForce->setVolume(_volume);
		std::cout << "Volumen: " << _volume << std::endl;
		break;
	default:
		break;
	}
}