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

	// -------------------- PARTE DE FLOTABILIDAD --------------------
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

	//// -------------------- PARTE DE FLOTABILIDAD --------------------

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

Scene1::Scene1(PxMaterial* material, PxPhysics* physics, PxScene* scene) : gMaterial(material), gPhysics(physics), gScene(scene)
{
}

void Scene1::init()
{
	// ----- SUELO -----
	//Creamos un material
	gMaterial = gPhysics->createMaterial(0.8f, 0.8f, 0.2f);
	//Creamos el transform
	PxTransform transform(PxVec3(0, -1, 0));
	//Creamos el rigido estatico del suelo
	PxRigidStatic* ground = gPhysics->createRigidStatic(transform);
	//Con una forma de cubo fino
	PxShape* shape = gPhysics->createShape(PxBoxGeometry(50, 1, 50), *gMaterial);
	//Y se lo adjudicamos al solido rigido
	ground->attachShape(*shape);
	//Creamos el color
	Vector4 color = Vector4(1.0, 0.5, 0.5, 1.0);
	//Aniadimos el actor a la escena
	gScene->addActor(*ground);
	//Lo renderizamos
	_groundSolid = new RenderItem(shape, ground, color);
	shape->release();

	// SOLIDOS DINAMICOS 
	_solidSystem = new SolidSystem(gPhysics, gScene);

	// ----- GENERADOR DE CAJAS -----
	SolidGenerator* boxGen = new SolidGenerator(gPhysics);
	boxGen->setPosition(PxVec3(0, 10, 0));
	boxGen->setShape(SolidShape::BOX);
	boxGen->setMaterial(SolidMaterialType::WOOD);
	boxGen->setSpawnTime(1.0f);
	boxGen->setDuration(20.0f);

	_solidSystem->addGenerator(boxGen);

	// ----- GENERADOR DE ESFERAS -----
	SolidGenerator* sphereGen = new SolidGenerator(gPhysics);
	sphereGen->setPosition(PxVec3(5, 15, 0));
	sphereGen->setShape(SolidShape::SPHERE);
	sphereGen->setMaterial(SolidMaterialType::RUBBER);
	sphereGen->setSpawnTime(1.5f);
	sphereGen->setDuration(20.0f);

	_solidSystem->addGenerator(sphereGen);

}

void Scene1::update(double t)
{
	_solidSystem->update(t);
}

void Scene1::cleanup()
{
	delete _solidSystem;
	_solidSystem = nullptr;

	delete _groundSolid;
	_groundSolid = nullptr;
}

void Scene1::handleKey(unsigned char key, const PxTransform& camera)
{
	switch (toupper(key))
	{
		//Quitamos y ponemos la gravedad
	case 'G':
		_solidSystem->setUseGravity(!_solidSystem->getUseGravity());
		break;
	}
}

Scene2::Scene2(PxMaterial* material, PxPhysics* physics, PxScene* scene) :
	gMaterial(material), gPhysics(physics), gScene(scene),
	_points(0), _lives(3),_movementActive(false)
{
	//Inicializamos 20 proyectiles para el player
	for (int i = 0; i < 20; i++)
	{
		_proyectils.push_back(new Proyectil(
			PxVec3(0, -500, 0),
			PxVec3(0, 0, 0),
			Vector4(0, 1, 0, 0),
			PxVec3(0, -9.8f, 0)
		));
		_proyectils.back()->setActive(false);
	}
}

void Scene2::init()
{
	// ----- SUELO -----
	//Creamos un material
	gMaterial = gPhysics->createMaterial(0.8f, 0.8f, 0.2f);
	//Creamos el transform
	PxTransform transform(PxVec3(0, -1, 0));
	//Creamos el rigido estatico del suelo
	PxRigidStatic* ground = gPhysics->createRigidStatic(transform);
	//Con una forma de cubo fino
	PxShape* shape = gPhysics->createShape(PxBoxGeometry(100, 1, 100), *gMaterial);
	//Y se lo adjudicamos al solido rigido
	ground->attachShape(*shape);
	//Creamos el color
	Vector4 color = Vector4(1.0, 0.5, 0.5, 1.0);
	//Aniadimos el actor a la escena
	gScene->addActor(*ground);
	//Lo renderizamos
	_base = new RenderItem(shape, ground, color);
	RegisterRenderItem(_base);

	// ----- JUGADOR -----
	_playerParticle = new Particle(PxVec3(0.0, 1.0, 0.0), PxVec3(0.0, 0.0, 0.0),
		Vector4(1.0, 0.0, 0.0, 1.0), PxVec3(0.0, 0.0, 0.0), 10.0, 0.999, 500.0, 1.0);
	_playerParticle->setActive(true);
	_player = new ParticleSystem();
	_player->addParticle(_playerParticle);

	// Su movimiento
	_movement = new WindForce(_playerParticle->getDirection() * 100, 1.2, 0.5, 2, _playerParticle->getPos(), _playerParticle->getPos());

	// Se ve afectado por la gravedad
	_gravity = new GravityForce(PxVec3(0.0, -9.8, 0.0));
	_player->addForceGenerator(_gravity);


}

void Scene2::update(double t)
{
	//Actualizamos al jugador
	_player->update(t);

	if (_movementActive) {
		_movementTimer -= t;
		if (_movementTimer <= 0) {
			_player->removeForceGenerator(_movement);
			_movementActive = false;
		}
	}

	//Comprobamos las colisiones con el suelo
	checkCollisionWithGround(_playerParticle, PxVec3(0, 0, 0));

	//Actualizamos balas
	for (Proyectil* p : _proyectils)
	{
		if (p->isActive())
		{
			p->integrate(t, 1); // SemiEuler
			PxVec3 pos = p->getPos();
			PxVec3 vel = p->getV();

			// Desactivamos si esta fuera del mundo
			if (pos.x > 150.0 || pos.x < -150.0 || pos.y < -150.0 || pos.y > 150.0 || p->getDuration() <= 0)
			{
				p->setActive(false);
			}
		}
	}

}

void Scene2::cleanup()
{
	// Borrar pool de proyectiles
	for (Proyectil* p : _proyectils) {
		{
			if (p->getRenderItem() != nullptr)
			{
				DeregisterRenderItem(p->getRenderItem());
				delete p;
			}
		}
	}
	_proyectils.clear();

	DeregisterRenderItem(_base);
	_base = nullptr;
}

void Scene2::handleKey(unsigned char key, const PxTransform& camera)
{
	switch (toupper(key))
	{
		//Izquierda
	case 'A':
		_playerParticle->setPos(_playerParticle->getPos() + PxVec3(-0.1, 0.0, 0.0));
		_playerParticle->setDirection(PxVec3(-1.0, 0.0, 0.0));

	break;
		//Derecha
	case 'D':
		_playerParticle->setPos(_playerParticle->getPos() + PxVec3(0.1, 0.0, 0.0));
		_playerParticle->setDirection(PxVec3(1.0, 0.0, 0.0));
	
	break;
		//Adelante
	case 'W':
		_playerParticle->setPos(_playerParticle->getPos() + PxVec3(0.0, 0.0, -0.1));
		_playerParticle->setDirection(PxVec3(0.0, 0.0, -1.0));
	break;

		//Atras
	case 'S':
		_playerParticle->setPos(_playerParticle->getPos() + PxVec3(0.0, 0.0, 0.1));
		_playerParticle->setDirection(PxVec3(0.0, 0.0, 1.0));

	break;

		//Salto
	case 'Q':
		_movement->setWindSpeed(PxVec3(0, 1, 0) * 150);
	
	break;

	case 'E':
		// disparar desde camara
		shootFromCamera(Proyectil::ProyectilType::Bullet);
		break;

	case 'R':
		//Disparar al frente
		shootFromPlace(Proyectil::ProyectilType::Bullet, _playerParticle->getPos(), _playerParticle->getDirection());
		break;
	default:
		break;
	}

	// Aniadimos la nueva fuerza
	_player->addForceGenerator(_movement);
	_movementActive = true;
	_movementTimer = 0.2; 
}

void Scene2::shootFromCamera(Proyectil::ProyectilType type)
{
	for (Proyectil* p : _proyectils)
	{
		if (!p->isActive())
		{
			p->shootFromCamera(type);
			break;
		}
	}
}

void Scene2::shootFromPlace(Proyectil::ProyectilType type, PxVec3 position, PxVec3 direction)
{
	for (Proyectil* p : _proyectils)
	{
		if (!p->isActive())
		{
			p->shootFromPlace(type, position, direction);
			break;
		}
	}
}

void Scene2::checkCollisionWithGround(Particle* p, PxVec3 floor)
{
	//La altura del suelo
	float groundY = floor.y;
	float radius = p->getSize();

	PxVec3 pos = p->getPos();
	PxVec3 vel = p->getV();

	// Miramos si esta dentro del suelo
	if (pos.y - radius < groundY)
	{
		// La reposicionamos
		pos.y = groundY + radius;
		p->setPos(pos);

	}
}

