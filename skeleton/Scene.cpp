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
// Scene0, Scene1, Scene2 ... 

// ---- SCENE 0 ----
Scene0::Scene0(PxMaterial* material) : Scene(), gMaterial(material)
{}

void Scene0::init()
{
	// PRACTICA 0
	//Creamos la geometria de la esfera (con radio 0)
	PxGeometry* sphereGeo = new PxSphereGeometry(1.0);
	//Creamos la forma con la geometria
	PxShape* sphere0 = CreateShape(*sphereGeo, gMaterial);
	//Creamos el transform, y el color
	Vector3D pos(0.0, 0.0, 0.0);
	PxTransform* tr = new PxTransform(PxVec3(pos.getX(), pos.getY(), pos.getZ()));
	Vector4* color = new Vector4{ 1.0, 1.0, 1.0, 1.0 };
	//Renderizamos la esfera
	sp1 = new RenderItem(sphere0, tr, *color);
	//La registramos
	RegisterRenderItem(sp1);

	//---- Eje rojo x
	//Creamos la forma con la geometria
	PxShape* sphereX = CreateShape(*sphereGeo, gMaterial);
	Vector3D posX(10.0, 0.0, 0.0);
	PxTransform* trX = new PxTransform(PxVec3(posX.getX(), posX.getY(), posX.getZ()));
	Vector4* rojo = new Vector4{ 1.0, 0.0, 0.0, 1.0 };
	//Renderizamos la esfera
	spX = new RenderItem(sphereX, trX, *rojo);
	//La registramos
	RegisterRenderItem(spX);

	//---- Eje verde y
	//Creamos la forma con la geometria
	PxShape* sphereY = CreateShape(*sphereGeo, gMaterial);
	Vector3D posY(0, 10.0, 0);
	PxTransform* trY = new PxTransform(PxVec3(posY.getX(), posY.getY(), posY.getZ()));
	Vector4* verde = new Vector4{ 0.0, 1.0, 0.0, 1.0 };
	//Renderizamos la esfera
	spY = new RenderItem(sphereY, trY, *verde);
	//La registramos
	RegisterRenderItem(spY);

	//---- Eje azul z
	//Creamos la forma con la geometria
	PxShape* sphereZ = CreateShape(*sphereGeo, gMaterial);
	Vector3D posZ(0.0, 0.0, 10.0);
	PxTransform* trZ = new PxTransform(PxVec3(posZ.getX(), posZ.getY(), posZ.getZ()));
	Vector4* azul = new Vector4{ 0.0, 0.0, 1.0, 1.0 };
	//Renderizamos la esfera
	spZ = new RenderItem(sphereZ, trZ, *azul);
	//La registramos
	RegisterRenderItem(spZ);

}

void Scene0::update(double t)
{}

void Scene0::cleanup()
{
	////Las desregistramos
	//DeregisterRenderItem(sp1);
	//DeregisterRenderItem(spX);
	//DeregisterRenderItem(spY);
	//DeregisterRenderItem(spZ);
}

// ---- SCENE 1 ----
void Scene1::init()
{
#pragma region Practica 1.1

	//particleSimple = new Particle(PxVec3(0.0, 10.0, 0.0), PxVec3(0.0, 2.5, 0.0));
	//particleColor = new Particle(PxVec3(1.0, 10.0, 0.0), PxVec3(5.0, 0.0, 0.0), Vector4(1.0, 0.0, 0.0, 1.0));
	//particleFull = new Particle(PxVec3(-2.0, 10.0, 0.0), PxVec3(-5.0, 0.0, 0.0), Vector4(0.0, 1.0, 1.0, 1.0), PxVec3(0.0, 0.0, 0.0), 2.0, 0.5, 5.0);

#pragma endregion

#pragma region Practica 1.2

//Direccion de la camara
	PxVec3 dir = PxVec3(GetCamera()->getDir());

	////Color rojo. Gravedad baja, practicamente 0, porque va casi recto
	//bullet = new Proyectil(PxVec3(0.0, 30.0, -10.0), PxVec3(dir.x * -60.0, dir.y * 0.0, dir.z * 0.0), Vector4(1.0, 0.0, 0.0, 0.0), PxVec3(0.0, -0.05, 0.0));
	////Color verde. Gravedad alta, cae eventualmente
	//cannonBall = new Proyectil(PxVec3(-20.0, 30.0, 0.0), PxVec3(dir.x * 0.0, dir.y * -40.0, dir.z * 20.0), Vector4(0.0, 1.0, 0.0, 0.0), PxVec3(0.0, -9.8, 0.0));
	////Color azul. Gravedad positiva, flotan
	//bubble = new Proyectil(PxVec3(0.0, 0.0, 0.0), PxVec3(dir.x * 0.0, dir.y * -15.0, dir.z * -0.05), Vector4(0.0, 0.0, 1.0, 0.0), PxVec3(0.0, 0.1, 0.0));

	//Para el vector ilimitado - inicializamos con proyectiles basicos
	for (int i = 0; i < 20; i++)
	{
		proyectils.push_back(new Proyectil(
			PxVec3(0, -500, 0),
			PxVec3(0, 0, 0),
			Vector4(1, 1, 1, 0),
			PxVec3(0, -9.8f, 0)
		));
		proyectils.back()->setActive(false);
	}
#pragma endregion
}

void Scene1::update(double t)
{
#pragma region Practica 1.1

	////Actualizar la posicion con los integrate...
	//particleSimple->integrate(t, 0); //EULER
	//particleColor->integrate(t, 1); //SEMIEULER
	//particleFull->integrate(t, 0); //VERLET no esta acabado

#pragma endregion

#pragma region Practica 1.2

	//std::cout << GetCamera()->getDir().x << GetCamera()->getDir().y << GetCamera()->getDir().z << std::endl;
	////Actualizar la posicion con los SemiEuler...
	//bullet->integrate(t, 1);
	//cannonBall->integrate(t, 1);
	//bubble->integrate(t, 1);

	//Actualizamos
	for (Proyectil* p : proyectils)
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

#pragma endregion
}

void Scene1::cleanup()
{
#pragma region Practica 1.1

	//DeregisterRenderItem(particleSimple->getRenderItem());
	//DeregisterRenderItem(particleColor->getRenderItem());
	//DeregisterRenderItem(particleFull->getRenderItem());

#pragma endregion

#pragma region Practica 1.2

	//Los desregistramos
	//DeregisterRenderItem(bullet->getRenderItem());
	//DeregisterRenderItem(cannonBall->getRenderItem());
	//DeregisterRenderItem(bubble->getRenderItem());

	// Borrar pool de proyectiles
	for (Proyectil* p : proyectils) {
		
		if (p->getRenderItem() != nullptr)
		{
			//DeregisterRenderItem(p->getRenderItem());
			delete p;
		}
		
	}
	proyectils.clear();

#pragma endregion
}

void Scene1::handleKey(unsigned char key, const PxTransform& camera)
{
	switch (toupper(key))
	{
	case 'Q':
		// disparar desde camara
		shootFromCamera(Proyectil::ProyectilType::Bullet);
		break;

	case 'W':
		//Disparar al frente
		shootFromCamera(Proyectil::ProyectilType::Bubble);
		break;

	//case 'E':
	//	//Disparar al frente
	//	shootFromCamera(Proyectil::ProyectilType::CanonBall);
	//	break;

	default:
		break;
	}
}

void Scene1::shootFromCamera(Proyectil::ProyectilType type)
{
	for (Proyectil* p : proyectils)
	{
		if (!p->isActive())
		{
			p->shootFromCamera(type);
			break;
		}
	}
}

// ---- SCENE 2 ----
void Scene2::init()
{
	////Manguera - Gaussiano
	//hoseSystem = new ParticleSystem(); 
	//hoseGenerator = new GaussParticleGenerator(PxVec3(0.0, 5.0, 0.0), PxVec3(0.0, 15.0, 0.0), PxVec3(0.01, 5.0, 0.01), 5);
	//hoseSystem->setUseGravity(true);
	//hoseGenerator->setDuration(2.0);
	//hoseGenerator->setProbability(1.0);        
	//hoseSystem->addGenerator(hoseGenerator);

	//Niebla - Uniforme
	fogSystem = new ParticleSystem();
	fogGenerator = new UniformParticleGenerator(PxVec3(0, 5, 0), 50,
		PxVec3(-10, 0, -10), PxVec3(10, 10, 10),
		PxVec3(-0.3, -0.3, -0.3), PxVec3(0.3, 0.3, 0.3));
	fogSystem->setUseGravity(false);
	fogGenerator->setDuration(5.0);
	fogGenerator->setProbability(0.9);
	fogSystem->addGenerator(fogGenerator);
	////PRACTICA 3 - FUERZAS DE VIENTO
	////Viento simple
	//WindForce* basicWind = new WindForce(PxVec3(5.0, 0.0, 0.0), 0.2, 0.0,
	//	PxVec3(-10, 0, -10), PxVec3(10, 10, 10));
	//fogSystem->addForceGenerator(basicWind);
	////Viento avanzado
	//WindForce* _advancedWind = new WindForce(PxVec3(5.0, 0.0, 0.0), 1.2, 0.5, 0.1,
	//	PxVec3(-10, 0, -10), PxVec3(10, 10, 10));
	//fogSystem->addForceGenerator(_advancedWind);

	////PRACTICA 3 - FUERZAS DE VIENTO - TORBELLINO
	WhirlwindForce* whirlwind = new WhirlwindForce(PxVec3(0.0, 5.0, 0.0), 0.9,
		15.0, 1.2, 0.5, 0.2);
	fogSystem->addForceGenerator(whirlwind);

	////Fuego - Gaussiano
	//_fireSystem = new ParticleSystem();
	//_fireGenerator = new GaussParticleGenerator(PxVec3(0.0, 0.0, 0.0), PxVec3(0.0, 5.0, 0.0), PxVec3(1.0, 1.0, 1.0), 10);
	////_fireSystem->setUseGravity(false);
	//_fireGenerator->setProbability(0.8);
	//_fireSystem->addGenerator(_fireGenerator);
	////PRACTICA 3 - FUERZAS DE GRAVEDAD, PERO INVERSA
	//GravityForce* _inverseGravity = new GravityForce(0.2, PxVec3(0, -500, 0));
	//_fireSystem->addForceGenerator(_inverseGravity);

}

void Scene2::update(double t)
{
	//Actualizamos el sistema
	//hoseSystem->update(t);
	fogSystem->update(t);
	//_fireSystem->update(t);
}

void Scene2::cleanup()
{
	//Los borra
	//delete hoseSystem;
	//hoseSystem = nullptr;
	delete fogSystem;
	fogSystem = nullptr;
	//delete _fireSystem;
	//_fireSystem = nullptr;
}

// ---- SCENE 3 - PRACTICA INTERMEDIA ----
Scene3::Scene3(PxMaterial* material) : gMaterial(material)
{
	for (int i = 0; i < 20; i++)
	{
		proyectils.push_back(new Proyectil(
			PxVec3(0, -500, 0),
			PxVec3(0, 0, 0),
			Vector4(0, 1, 0, 0),
			PxVec3(0, -9.8f, 0)
		));
		proyectils.back()->setActive(false);
	}

	//Para el vector ilimitado - inicializamos con proyectiles basicos
	for (int i = 0; i < 1; i++)
	{
		_canonProyectils.push_back(new Proyectil(
			PxVec3(0, -500, 0),
			PxVec3(0, 0, 0),
			Vector4(0, 1, 0, 0),
			PxVec3(0, -9.8f, 0)
		));
		_canonProyectils.back()->setActive(false);
	}

	_shootingDuration = 500;
}

void Scene3::init()
{
	//Colocamos camera
	//GetCamera()->setDir(PxVec3(50.0, 40.0, -20.0));

	// ---------- PLANO BASE ----------
	//Creamos la geometria del plano
	PxGeometry* boxGeo = new PxBoxGeometry(50 / 2, 5 / 2, 50 / 2);
	//Creamos la forma con la geometria
	PxShape* box = CreateShape(*boxGeo, gMaterial);
	//Creamos el transform, y el color
	Vector3D pos(50.0, 40.0, -20.0);
	PxTransform* tr = new PxTransform(PxVec3(pos.getX(), pos.getY(), pos.getZ()));
	Vector4* color = new Vector4{ 1.0, 1.0, 1.0, 1.0 };
	//Renderizamos la base
	_base1 = new RenderItem(box, tr, *color);
	//La registramos
	RegisterRenderItem(_base1);

	// ---------- CANION DE AIRE ----------
	//Creamos la geometria del plano
	PxGeometry* box1 = new PxBoxGeometry(5 / 2, 5 / 2, 5 / 2);
	//Creamos la forma con la geometria
	PxShape* boxShape = CreateShape(*box1, gMaterial);
	//Creamos el transform, y el color
	Vector3D pos1(30.0, 45.0, -20.0);
	PxTransform* tr1 = new PxTransform(PxVec3(pos1.getX(), pos1.getY(), pos1.getZ()));
	Vector4* color1 = new Vector4{ 0.0, 0.0, 1.0, 1.0 };
	//Renderizamos la base
	_windCanon = new RenderItem(boxShape, tr1, *color1);
	//La registramos
	RegisterRenderItem(_windCanon);
	_windCanon->color = Vector4(0.2, 0.2, 0.5, 1.0);

	//Niebla - Uniforme
	_airSystem = new ParticleSystem();
	_airGenerator = new UniformParticleGenerator(PxVec3(15.0, 22.0, -10.0), 10,
		PxVec3(15.0, 20.0, -12.0), PxVec3(40.0, 24.0, -8.0),
		PxVec3(-0.3, -0.3, -0.3), PxVec3(0.3, 0.3, 0.3));
	_airSystem->setUseGravity(false);
	_airGenerator->setDuration(1.0);
	_airGenerator->setProbability(0.9);
	_airSystem->addGenerator(_airGenerator);
	//Viento avanzado
	_advancedWind = new WindForce(PxVec3(10.0, 0.0, 0.0), 1.2, 0.5, 0.1,
		PxVec3(-100.0, 0.0, -100.0), PxVec3(100.0, 50.0, 100.0));
	_airSystem->addForceGenerator(_advancedWind);

	// ---------- CANION DE FUEGO ----------
	//Creamos la geometria del plano
	PxGeometry* box2 = new PxBoxGeometry(5 / 2, 5 / 2, 5 / 2);
	//Creamos el transform, y el color
	Vector3D pos2(60.0, 45.0, -5.0);
	PxTransform* tr2 = new PxTransform(PxVec3(pos2.getX(), pos2.getY(), pos2.getZ()));
	Vector4* color2 = new Vector4{ 1.0, 0.0, 0.0, 1.0 };
	//Renderizamos la base
	_fireCanon = new RenderItem(boxShape, tr2, *color2);
	//La registramos
	RegisterRenderItem(_fireCanon);
	_fireCanon->color = Vector4(0.5, 0.2, 0.2, 1.0);

	//Fuego - Gaussiano
	_fireSystem = new ParticleSystem();
	_fireGenerator = new GaussParticleGenerator(PxVec3(60.0, 45.0, -5.0),
		PxVec3(0.0, 3.0, 0.0), PxVec3(1.0, 1.0, 1.0), 10);
	//_fireSystem->setUseGravity(false);
	_fireGenerator->setProbability(0.8);
	_fireSystem->addGenerator(_fireGenerator);
	_inverseGravity = new GravityForce(0.2, PxVec3(0, -500, 0));
	_fireSystem->addForceGenerator(_inverseGravity);

	// ---------- JUGADOR ----------
	_player = new Particle(PxVec3(50.0, 44.0, -10.0), PxVec3(0.0, 0.0, 0.0), 
		Vector4(1.0, 0.0, 0.0, 1.0),5.0);
	//Jugador
	//_playerSystem = new ParticleSystem();
	//_playerGenerator = new UniformParticleGenerator(PxVec3(50.0, 44.0, -10.0), 1,
	//	PxVec3(50.0, 44.0, -10.0), PxVec3(50.0, 44.0, -10.0),
	//	PxVec3(0.0, -10.0, 0.0), PxVec3(20.0, 20.0, 20.0));
	//_playerGenerator->setProbability(0.8);
	//_playerSystem->addGenerator(_playerGenerator);
	//gravity = new GravityForce(0.2, PxVec3(0, 10, 0));
	//_playerSystem->addForceGenerator(gravity);

	// ---------- DISPAROS ----------
	//Direccion de la camara
	PxVec3 dir = PxVec3(GetCamera()->getDir());

	// ---------- CANION ENEMIGO ----------
	//Creamos la geometria del plano
	PxShape* boxGeo3 = CreateShape(*box1, gMaterial);
	//Creamos el transform, y el color
	Vector3D pos3(45.0, 45.0, -25.0);
	PxTransform* tr3 = new PxTransform(PxVec3(pos3.getX(), pos3.getY(), pos3.getZ()));
	Vector4* color3 = new Vector4{ 0.0, 1.0, 1.0, 1.0 };
	//Renderizamos la base
	_bulletCanon = new RenderItem(boxGeo3, tr3, *color3);
	//La registramos
	RegisterRenderItem(_bulletCanon);

	fireworksSystem = new ParticleSystem();
	fireworksGenerator = new HierarchyParticleGenerator(PxVec3(50, 40, 0));
	fireworksSystem->addGenerator(fireworksGenerator);

	//explosionSystem = new ParticleSystem();
}

void Scene3::update(double t)
{
	//Forzamos una gravedad mal hecha //No va porque en integrate se usa Aceleracion con fuerzas
	//_player->setA(PxVec3(0.0, -9.8, 0.0));

	//Actualizamos los sistemas de particulas y las fuerzas
	if (_windActive) 
	{
		_airSystem->update(t);
	}
	if (_fireActive)
	{
		_fireSystem->update(t);
	}
	//_playerSystem->update(t);

	//Lo movemos
	_player->integrate(t, 1);

	// El jugador no puede atravesar el plano (no hay colisines aun)
	// Si baja de la altura del plano
	if (_player->getPos().y < 44.0) {

		//Forzamos que este a la altura del plano
		_player->setPos(PxVec3(_player->getPos().x, 44.0, _player->getPos().z));
		//Y anulamos la velocidad en vertical
		_player->setV(PxVec3(_player->getV().x, 0.0, _player->getV().z));
	}

	//Actualizamos balas
	for (Proyectil* p : proyectils)
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

	//Actualizamos balas
	for (Proyectil* p : _canonProyectils)
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

	//Vamos reduciendo tiempo
	while (_shootingDuration > 0)
	{
		_shootingDuration -= t;
	}

	bool shoot = false; //No ha disparado
	//Si se acaba
	if (_shootingDuration <= 0 && !shoot)
	{
		//Disparamos
		shootEnemyCanon(Proyectil::ProyectilType::Bullet, PxVec3(45.0, 45.0, -25.0), PxVec3(1.0, 0.0, 0.0));
		//Ya ha disparado
		shoot = true;
		//reseteamos el tiempo
		_shootingDuration = 3000;

	}

	shoot = false;

	fireworksSystem->update(t);

}

void Scene3::cleanup()
{
	//Borramos los sistemas
	delete _airSystem;
	_airSystem = nullptr;
	delete _fireSystem;
	_fireSystem = nullptr;

	// Borrar pool de proyectiles
	for (Proyectil* p : proyectils) {
		{
			if (p->getRenderItem() != nullptr)
			{
				DeregisterRenderItem(p->getRenderItem());
				delete p;
			}
		}
	}
	proyectils.clear();

	// Borrar pool de proyectiles
	for (Proyectil* p : _canonProyectils) {
		{
			if (p->getRenderItem() != nullptr)
			{
				DeregisterRenderItem(p->getRenderItem());
				delete p;
			}
		}
	}
	_canonProyectils.clear();
}

void Scene3::handleKey(unsigned char key, const PxTransform& camera)
{
	switch (toupper(key))
	{
		//Izquierda
	case 'A':
		_player->setPos(_player->getPos() + PxVec3(-0.1, 0.0, 0.0));
		_player->setDirection(PxVec3(-1.0, 0.0, 0.0));
		break;
		//Derecha
	case 'D':
		_player->setPos(_player->getPos() + PxVec3(0.1, 0.0, 0.0));
		_player->setDirection(PxVec3(1.0, 0.0, 0.0));
		break;
		//Salto
	case 'W':
		//Si esta en el suelo
		if (_player->getPos().y >= 44 && _player->getPos().y < 45)
		{
			_player->setPos(_player->getPos() + PxVec3(0.0, 10.0, 0.0));
		}
		break;

	case 'Q':
		// disparar desde camara
		shootFromCamera(Proyectil::ProyectilType::Bullet);
		break;

	case 'S':
		//Disparar al frente
		shootFromPlace(Proyectil::ProyectilType::Bullet, _player->getPos(), _player->getDirection());
		break;

	case 'E':
		//Activar y desactivar canion de viento
		_windActive = !_windActive;

		if (!_windActive)
		{
			_windCanon->color = Vector4(0.2, 0.2, 0.5, 1.0);
			_airSystem->setPaused(true);
		}
		else
		{
			_windCanon->color = Vector4(0.0, 0.0, 1.0, 1.0);
			_airSystem->setPaused(false);
		}
		
		break;

	case 'R':
		//Activar y desactivar canion de fuego
		_fireActive = !_fireActive;

		if (!_fireActive)
		{
			_fireCanon->color = Vector4(0.5, 0.2, 0.2, 1.0);
			_fireSystem->setPaused(true);
		}
		else
		{
			_fireCanon->color = Vector4(1.0, 0.0, 0.0, 1.0);
			_fireSystem->setPaused(false);
		}

		break;

	default:
		break;
	}

}

void Scene3::shootFromCamera(Proyectil::ProyectilType type)
{
	for (Proyectil* p : proyectils)
	{
		if (!p->isActive())
		{
			p->shootFromCamera(type);
			break;
		}
	}
}

void Scene3::shootFromPlace(Proyectil::ProyectilType type, PxVec3 position, PxVec3 direction)
{
	for (Proyectil* p : proyectils)
	{
		if (!p->isActive())
		{
			p->shootFromPlace(type, position, direction);
			break;
		}
	}
}

void Scene3::shootEnemyCanon(Proyectil::ProyectilType type, PxVec3 position, PxVec3 direction)
{
	for (Proyectil* p : _canonProyectils)
	{
		if (!p->isActive())
		{
			p->shootFromPlace(type, position, direction);
			break;
		}
	}
}


