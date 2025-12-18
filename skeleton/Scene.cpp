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
// Scene0, Scene1, Scene0 ... 

Scene0::Scene0(PxMaterial* material, PxPhysics* physics, PxScene* scene) :
	_lives(3), _points(0),
	gMaterial(material), gPhysics(physics), gScene(scene),
	_waterHeight(0.0), _objectSize(2.0), _volume(_objectSize* _objectSize* _objectSize), _mass(400),
	_goalPoints(1000), _gameState(0), _isRaining(false), _victory(false)
{
	//Inicializamos 10 proyectiles para el player
	for (int i = 0; i < 10; i++)
	{
		_proyectils.push_back(new Proyectil(
			PxVec3(0, -500, 0),
			PxVec3(0, 0, 0),
			Vector4(0, 1, 0, 0),
			PxVec3(0, -9.8f, 0)
		));
		_proyectils.back()->setActive(false);
	}

	//Inicializamos 16 proyectiles para los enemigos
	for (int i = 0; i < 16; i++)
	{
		_enemyProyectils.push_back(new Proyectil(
			PxVec3(0, -500, 0),
			PxVec3(0, 0, 0),
			Vector4(0, 1, 0, 0),
			PxVec3(0, -9.8f, 0)
		));
		_enemyProyectils.back()->setActive(false);
	}

	//Temporizadores para disparo enemigo
	for (int i = 0; i < 8; i++)
	{
		_enemyShootTimer[i] = 0.0;
		_enemyShootCooldown[i] = (i % 2 == 0) ? 3.0 : 6.0; // 3s y 6s
	}
}

void Scene0::init()
{
	std::cout << "You have " << _lives << " lives." << std::endl;
	std::cout << "You have " << _points << " points. You need " << _goalPoints - _points << " to win." << std::endl;

	// ----- FUERZAS GENERALES -----
	_gravity = new GravityForce(PxVec3(0.0, -9.8, 0.0));
	_floating = new FloatingForce(_waterHeight, _objectSize, _volume, 1000.0f);
	_wind = new WindForce(Vector3(0.002, 0.0, 0.0001), 1.2, 0.5, 1, Vector3(-200, -50, -200), Vector3(200, 150, 200));
	//_explosion1 = new ExplosionForce(PxVec3(-25, 20, -25), 1500.0, 50.0, 5.0);
	//_explosion2 = new ExplosionForce(PxVec3(-25, 20, 25), 1500.0, 50.0, 5.0);
	//_explosion3 = new ExplosionForce(PxVec3(25, 20, -25), 1500.0, 50.0, 5.0);
	//_explosion4 = new ExplosionForce(PxVec3(25, 20, 25), 1500.0, 50.0, 5.0);

	// ----- LLUVIA -----
	createRain();

	// ----- SUELO -----
	createBase();

	// ----- LAGO -----
	createLake();

	// ----- CAJAS DEL LAGO -----
	createWaterCube(PxVec3(0.0, _waterHeight, 0.0), _floatingParticle1, _floatingBox1);
	createWaterCube(PxVec3(-25.0, _waterHeight, -25.0), _floatingParticle2, _floatingBox2);
	createWaterCube(PxVec3(25.0, _waterHeight, -25.0), _floatingParticle3, _floatingBox3);
	createWaterCube(PxVec3(-25.0, _waterHeight, 25.0), _floatingParticle4, _floatingBox4);
	createWaterCube(PxVec3(25.0, _waterHeight, 25.0), _floatingParticle5, _floatingBox5);

	// ----- FUENTES DEL LAGO -----
	createFountain(PxVec3(0, 0, -25), _fountain1, _f1gen);
	createFountain(PxVec3(0, 0, 25), _fountain2, _f2gen);
	createFountain(PxVec3(-25, 0, 0), _fountain3, _f3gen);
	createFountain(PxVec3(25, 0, 0), _fountain4, _f4gen);

	// ----- JUGADOR -----
	createPlayer();

	// ----- ENEMIGOS -----
	createEnemy(PxVec3(110, 0, -12.5), _enemyCannon1);
	createEnemy(PxVec3(110, 0, 87.5), _enemyCannon2);
	createEnemy(PxVec3(12.5, 0, 110), _enemyCannon3);
	createEnemy(PxVec3(-87.5, 0, 110), _enemyCannon4);
	createEnemy(PxVec3(-110, 0, 12.5), _enemyCannon5);
	createEnemy(PxVec3(-110, 0, -87.5), _enemyCannon6);
	createEnemy(PxVec3(-12.5, 0, -110), _enemyCannon7);
	createEnemy(PxVec3(87.5, 0, -110), _enemyCannon8);

	// ----- RECOLECTABLES -----
	createCollectables(_collectable1, PxVec3(0, 10, 0));
	createCollectables(_collectable2, PxVec3(-25, 10, -25));
	createCollectables(_collectable3, PxVec3(-25, 10, 25));
	createCollectables(_collectable4, PxVec3(25, 10, -25));
	createCollectables(_collectable5, PxVec3(25, 10, 25));
	createCollectables(_collectable6, PxVec3(-75, 10, -75));
	createCollectables(_collectable7, PxVec3(-75, 10, 75));
	createCollectables(_collectable8, PxVec3(75, 10, -75));
	createCollectables(_collectable9, PxVec3(75, 10, 75));
}

void Scene0::update(double t)
{
	//Mientras se siga en juego
	if (_gameState == 0)
	{
		//Actualizamos las fuentes
		_fountain1->update(t);
		_fountain2->update(t);
		_fountain3->update(t);
		_fountain4->update(t);

		//Actualizamos al jugador
		_player->update(t);

		//Comprobamos las colisiones con el suelo
		checkCollisionWithGround(_playerParticle, PxVec3(0, 0, 0));

		//Comprobamos las colisiones con el agua
		checkCollisionWithWater(_playerParticle);

		//Comprobamos las colisiones con los coleccionables
		checkCollectables(_collectable1);
		checkCollectables(_collectable2);
		checkCollectables(_collectable3);
		checkCollectables(_collectable4);
		checkCollectables(_collectable5);
		checkCollectables(_collectable6);
		checkCollectables(_collectable7);
		checkCollectables(_collectable8);
		checkCollectables(_collectable9);

		//Colisiones balas enemigos - player
		for (Proyectil* p : _enemyProyectils)
		{
			if (!p->isActive()) continue;

			if (checkCollisionWithBullet(_playerParticle, p))
			{
				//Han colisionado
				p->setActive(false);

				//Quitamos vidas
				_lives--;

				//Mensaje por consola
				std::cout << "Player hit! Lives: " << _lives << std::endl;

				// Respawn simple
				_playerParticle->setPos(PxVec3(0.0f, 1.0f, 80.0f));


				break;
			}
		}

		//Actualizamos balas
		for (Proyectil* p : _proyectils)
		{
			if (p->isActive())
			{
				p->integrate(t, 1); // SemiEuler
				PxVec3 pos = p->getPos();
				PxVec3 vel = p->getV();

				// Desactivamos si esta fuera del mundo
				if (pos.x > 150.0 || pos.x < -150.0 || pos.z < -150.0 || pos.z > 150.0 || p->getDuration() <= 0)
				{
					p->setActive(false);
				}
			}
		}

		//Comprobamos las colisiones entre las balas y los coleccionables
		checkBulletCollectables(_collectable1);
		checkBulletCollectables(_collectable2);
		checkBulletCollectables(_collectable3);
		checkBulletCollectables(_collectable4);
		checkBulletCollectables(_collectable5);
		checkBulletCollectables(_collectable6);
		checkBulletCollectables(_collectable7);
		checkBulletCollectables(_collectable8);
		checkBulletCollectables(_collectable9);

		//Actualizamos balas
		for (Proyectil* p : _enemyProyectils)
		{
			if (p->isActive())
			{
				p->integrate(t, 1); // SemiEuler
				PxVec3 pos = p->getPos();
				PxVec3 vel = p->getV();

				// Desactivamos si esta fuera del mundo
				if (pos.x > 150.0 || pos.x < -150.0 || pos.z < -150.0 || pos.z > 150.0 || p->getDuration() <= 0)
				{
					p->setActive(false);
				}
			}
		}

		//Dispara automaticamente
		if (_enemyCannon1 != nullptr)	enemyShoot(0, _enemyCannon1->transform->p, PxVec3(-1, 0, 0), t);
		if (_enemyCannon2 != nullptr)	enemyShoot(1, _enemyCannon2->transform->p, PxVec3(-1, 0, 0), t);
		if (_enemyCannon3 != nullptr)	enemyShoot(2, _enemyCannon3->transform->p, PxVec3(0, 0, -1), t);
		if (_enemyCannon4 != nullptr)	enemyShoot(3, _enemyCannon4->transform->p, PxVec3(0, 0, -1), t);
		if (_enemyCannon5 != nullptr)	enemyShoot(4, _enemyCannon5->transform->p, PxVec3(1, 0, 0), t);
		if (_enemyCannon6 != nullptr)	enemyShoot(5, _enemyCannon6->transform->p, PxVec3(1, 0, 0), t);
		if (_enemyCannon7 != nullptr)	enemyShoot(6, _enemyCannon7->transform->p, PxVec3(0, 0, 1), t);
		if (_enemyCannon8 != nullptr)	enemyShoot(7, _enemyCannon8->transform->p, PxVec3(0, 0, 1), t);

		//Actualizamos los recolectables
		_collectable1->update(t);
		_collectable2->update(t);
		_collectable3->update(t);
		_collectable4->update(t);
		_collectable5->update(t);
		_collectable6->update(t);
		_collectable7->update(t);
		_collectable8->update(t);
		_collectable9->update(t);

		// Condicion de derrota
		if (_lives <= 0)
		{
			_gameState = 2;
		}
		// Condicion de victoria
		else if (_points >= _goalPoints)
		{
			_gameState = 1;
		}
	}

	//Ahora define el final.
	//Si gana hay fuegos artificiales.
	//Si pierde, hay lluvia
	checkEndGame(t);

	//if (_gameState == 1)
	//{
	//	if (_firework1 != nullptr)	_firework1->update(t);
	//	if (_firework2 != nullptr)	_firework2->update(t);
	//	if (_firework3 != nullptr)	_firework3->update(t);
	//	if (_firework4 != nullptr)	_firework4->update(t);
	//}

	if (_gameState == 2)
	{
		//Actualizamos la lluvia
		_rain->update(t);
	}
}

void Scene0::cleanup()
{
	//Las fuerzas se borran directamente en el registro

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

	// Borrar pool de proyectiles
	for (Proyectil* p : _enemyProyectils) {
		{
			if (p->getRenderItem() != nullptr)
			{
				DeregisterRenderItem(p->getRenderItem());
				delete p;
			}
		}
	}
	_proyectils.clear();

	//Base
	DeregisterRenderItem(_base);
	_base = nullptr;

	//Lago
	DeregisterRenderItem(_lake);
	_lake = nullptr;

	//Cajas del lago
	DeregisterRenderItem(_floatingBox1);
	_floatingBox1 = nullptr;
	DeregisterRenderItem(_floatingBox2);
	_floatingBox2 = nullptr;
	DeregisterRenderItem(_floatingBox3);
	_floatingBox3 = nullptr;
	DeregisterRenderItem(_floatingBox4);
	_floatingBox4 = nullptr;
	DeregisterRenderItem(_floatingBox5);
	_floatingBox5 = nullptr;

	delete _floatingParticle1;
	_floatingParticle1 = nullptr;
	delete _floatingParticle2;
	_floatingParticle2 = nullptr;
	delete _floatingParticle3;
	_floatingParticle3 = nullptr;
	delete _floatingParticle4;
	_floatingParticle4 = nullptr;
	delete _floatingParticle5;
	_floatingParticle5 = nullptr;

	//Fuentes
	delete _fountain1;
	_fountain1 = nullptr;
	delete _fountain2;
	_fountain2 = nullptr;
	delete _fountain3;
	_fountain3 = nullptr;
	delete _fountain4;
	_fountain4 = nullptr;

	//Player
	delete _playerParticle;
	_playerParticle = nullptr;

	//Enemigos
	delete _enemyCannon1;
	_enemyCannon1 = nullptr;
	delete _enemyCannon2;
	_enemyCannon2 = nullptr;
	delete _enemyCannon3;
	_enemyCannon3 = nullptr;
	delete _enemyCannon4;
	_enemyCannon4 = nullptr;
	delete _enemyCannon5;
	_enemyCannon5 = nullptr;
	delete _enemyCannon6;
	_enemyCannon6 = nullptr;
	delete _enemyCannon7;
	_enemyCannon7 = nullptr;
	delete _enemyCannon8;
	_enemyCannon8 = nullptr;

	//Recolectables
	delete _collectable1;
	_collectable1 = nullptr;
	delete _collectable2;
	_collectable2 = nullptr;
	delete _collectable3;
	_collectable3 = nullptr;
	delete _collectable4;
	_collectable4 = nullptr;
	delete _collectable5;
	_collectable5 = nullptr;
	delete _collectable6;
	_collectable6 = nullptr;
	delete _collectable7;
	_collectable7 = nullptr;
	delete _collectable8;
	_collectable8 = nullptr;
	delete _collectable9;
	_collectable9 = nullptr;

	//Lluvia
	delete _rain;
	_rain = nullptr;

} 

void Scene0::handleKey(unsigned char key, const PxTransform& camera)
{
	double angle = 0.05;
	PxVec3 front = _playerParticle->getFrontOrientation();
	//Mientras se siga en juego
	if (_gameState == 0)
	{
		switch (toupper(key))
		{
			// ----- RELATIVO AL PLAYER, MOVIMIENTO Y DISPAROS -----
			//Izquierda
		case 'A': // gira a la izquierda
			_playerParticle->rotateY(angle);
		break;

		case 'D': // gira a la derecha
			_playerParticle->rotateY(-angle);
		break;

			//Adelante
		case 'W':
			_playerParticle->setPos(_playerParticle->getPos() + front * 0.5f);
		break;

			//Atras
		case 'S':
			_playerParticle->setPos(_playerParticle->getPos() - front * 0.5f);
		break;

		case 'E':
			// disparar desde camara
			shootFromCamera(Proyectil::ProyectilType::Bullet);
			break;

		case 'R':
			//Disparar al frente
			shootFromPlace(Proyectil::ProyectilType::Bullet, _playerParticle->getPos(),front);
			break;

		default:
			break;
		}
	}
}

void Scene0::shootFromCamera(Proyectil::ProyectilType type)
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

void Scene0::shootFromPlace(Proyectil::ProyectilType type, PxVec3 position, PxVec3 direction)
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

void Scene0::shootEnemyCanon(Proyectil::ProyectilType type, PxVec3 position, PxVec3 direction)
{
	for (Proyectil* p : _enemyProyectils)
	{
		if (!p->isActive())
		{
			p->shootFromPlace(type, position, direction);
			break;
		}
	}
}

void Scene0::checkCollisionWithGround(Particle* p, PxVec3 floor)
{
	float radius = p->getSize();
	PxVec3 pos = p->getPos();

	// Suelo
	float groundY = floor.y;      
	float groundHalfSize = 100.0f;

	//Comprobacion
	bool insidePlatform =
		pos.x >= -groundHalfSize && pos.x <= groundHalfSize &&
		pos.z >= -groundHalfSize && pos.z <= groundHalfSize;

	// Encima del suelo
	if (insidePlatform && pos.y - radius < groundY)
	{
		pos.y = groundY + radius;
		p->setPos(pos);

		// No tiene velocidad vertical
		PxVec3 vel = p->getV();
		vel.y = 0.0f;
		p->setV(vel);
	}

	// Se cae
	else if (!insidePlatform && pos.y < groundY - 10.0f)
	{
		// Pierde una vida
		_lives--;

		//Avisamos por consola
		std::cout << "Player fell! Lives: " << _lives << std::endl;

		// Respawn
		p->setPos(PxVec3(0.0f, 1.0f, 80.0f));
		p->setV(PxVec3(0, 0, 0));

	}
}

void Scene0::checkCollisionWithWater(Particle* p)
{
	float radius = p->getSize();
	PxVec3 pos = p->getPos();

	//Agua
	float waterHalfSize = 50.0f;
	float waterSurfaceY = _waterHeight + 0.05f;

	//Comprobacion
	bool insideLake =
		pos.x >= -waterHalfSize && pos.x <= waterHalfSize &&
		pos.z >= -waterHalfSize && pos.z <= waterHalfSize;

	// Si entra en el agua
	if (insideLake && pos.y - radius <= waterSurfaceY)
	{
		//Pierde vida
		_lives--;

		//Mensaje por consola
		std::cout << "Player drowned! Lives: " << _lives << std::endl;

		// Respawn
		p->setPos(PxVec3(0.0f, 1.0f, 80.0f));
		p->setV(PxVec3(0, 0, 0));
	}
}

bool Scene0::checkCollisionWithBullet(Particle* player, Proyectil* bullet)
{
	//Si no hay bala no podemos trabajar
	if (!bullet->isActive()) return false;

	//Cogemos las posiciones de los dos
	PxVec3 pPos = player->getPos();
	PxVec3 bPos = bullet->getPos();

	//Cogemos los radios de ambos
	double playerRadius = player->getSize();
	double bulletRadius = bullet->getSize();
	//Radio total
	double radiusSum = playerRadius + bulletRadius;

	//Distancia de posiciones
	PxVec3 difference = pPos - bPos;
	double distance = difference.dot(difference);

	return distance <= (radiusSum * radiusSum);
}

bool Scene0::checkCollisionWithCollectables(Particle* p, PxRigidDynamic* collectable)
{
	//Si no hay recolectable no podemos trabajar
	if (!collectable) return false;

	//Cogemos las posiciones de los dos
	PxVec3 pPos = p->getPos();
	PxVec3 cPos = collectable->getGlobalPose().p;

	//Cogemos los radios de ambos
	double playerRadius = p->getSize();
	double collectableRadius = 2.0f;
	//Radios totales
	double radiusSum = playerRadius + collectableRadius;

	//Distancia de posiciones
	PxVec3 difference = pPos - cPos;
	double distance = difference.dot(difference);

	return distance <= radiusSum * radiusSum;
}

bool Scene0::checkCollisionBulletCollectables(Proyectil* bullet, PxRigidDynamic* collectable)
{
	//Si no hay recolectable o bala no podemos trabajar
	if (!bullet || !bullet->isActive() || !collectable) return false;

	//Cogemos las posiciones de los dos
	PxVec3 bPos = bullet->getPos();
	PxVec3 cPos = collectable->getGlobalPose().p;

	//Cogemos los radios de ambos
	double bulletRadius = bullet->getSize();
	double collectableRadius = 2.0f;
	//Radios totales
	double radiusSum = bulletRadius + collectableRadius;

	//Distancia de posiciones
	PxVec3 difference = bPos - cPos;
	double distance = difference.dot(difference);

	return distance <= radiusSum * radiusSum;
}

void Scene0::checkEndGame(double t)
{
	//VICTORIA - FUEGOS ARTIFICIALES
	if (_gameState == 1 && !_victory)
	{
		_victory = true;

		//// ----- FUEGOS ARTIFICIALES -----
		////Creamos los juegos artificiales delante de la camara
		//createFirework(PxVec3(-25, 10, -25), _firework1, _fw1gen, Vector4(1, 0, 0, 1), _explosion1);
		//createFirework(PxVec3(-25, 10, 25), _firework2, _fw2gen, Vector4(0, 1, 0, 1), _explosion2);
		//createFirework(PxVec3(25, 10, -25), _firework3, _fw3gen, Vector4(0, 0, 1, 1), _explosion3);
		//createFirework(PxVec3(25, 10, 25), _firework4, _fw4gen, Vector4(1, 1, 0, 1), _explosion4);

		//Mensaje por consola
		std::cout << "Congrats! You win. Let's celebrate" << std::endl;

		//Ya que no van muy bien los fuegos, vamos a modificiar el entorno
		_base->color = Vector4(1.0, 0.0, 1.0, 1.0);
		_lake->color = Vector4(1.0, 0.5, 0.0, 1.0);
		_enemyCannon1->color = Vector4(1.0, 0.5, 0.0, 1.0);
		_enemyCannon2->color = Vector4(1.0, 0.5, 0.0, 1.0);
		_enemyCannon3->color = Vector4(1.0, 0.5, 0.0, 1.0);
		_enemyCannon4->color = Vector4(1.0, 0.5, 0.0, 1.0);
		_enemyCannon5->color = Vector4(1.0, 0.5, 0.0, 1.0);
		_enemyCannon6->color = Vector4(1.0, 0.5, 0.0, 1.0);
		_enemyCannon7->color = Vector4(1.0, 0.5, 0.0, 1.0);
		_enemyCannon8->color = Vector4(1.0, 0.5, 0.0, 1.0);
	}

	//DERROTA - LLUVIA
	if (_gameState == 2 && !_isRaining)
	{
		_isRaining = true;

		//Mensaje por consola
		std::cout << "Today is a sad day, you lost..." << std::endl;
	}

}

void Scene0::createBase()
{
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
	Vector4 color = Vector4(0.2, 1.0, 0.5, 1.0);
	//Aniadimos el actor a la escena
	gScene->addActor(*ground);
	//Lo renderizamos
	_base = new RenderItem(shape, ground, color);
	RegisterRenderItem(_base);
}

void Scene0::createLake()
{
	//Creamos la geometria del objeto
	PxGeometry* waterGeom = new PxBoxGeometry(50.0f, 0.05, 50.0f);
	//Creamos la forma con la geometria
	PxShape* waterShape = CreateShape(*waterGeom, gMaterial);
	//Creamos el transform, y el color
	PxTransform* waterTr = new PxTransform(PxVec3(0, _waterHeight, 0));
	Vector4* waterColor = new Vector4(0.0f, 0.5f, 1.0f, 1.0f);
	_lake = new RenderItem(waterShape, waterTr, *waterColor);
	//La registramos
	RegisterRenderItem(_lake);
}

void Scene0::createWaterCube(PxVec3 position, Particle*& particle, RenderItem*& render)
{
	//Creamos la geometria del objeto
	PxGeometry* boxGeom = new PxBoxGeometry(_objectSize / 2.0f, _objectSize / 2.0f, _objectSize / 2.0f);
	//Creamos la forma con la geometria
	PxShape* boxShape = CreateShape(*boxGeom, gMaterial);
	//Creamos el transform, y el color
	PxTransform* boxTr = new PxTransform(position);
	Vector4* boxColor = new Vector4(0.6f, 0.4f, 0.2f, 1.0f);
	//Renderizamos la base
	render = new RenderItem(boxShape, boxTr, *boxColor);
	//La registramos
	RegisterRenderItem(render);

	//Y particula relacionada, que sera la que se vera sometida a las fuerzas de flotacion
	_particleSystem = new ParticleSystem();
	particle = new Particle(
		position,
		PxVec3(0, 0, 0),
		PxVec4(1, 1, 1, 1),
		PxVec3(0, 0, 0),
		_mass,
		0.3f,
		100.0f,
		1.0f
	);
	particle->setActive(true);
	_particleSystem->addParticle(particle);
	_particleSystem->setPaused(false);

	//Gravedad
	_particleSystem->addForceGenerator(_gravity);

	//Flotacion
	_particleSystem->addForceGenerator(_floating);


}

void Scene0::createFountain(PxVec3 position, ParticleSystem*& particleSystem, GaussParticleGenerator*& generator)
{
	particleSystem = new ParticleSystem();
	generator = new GaussParticleGenerator(position, PxVec3(2.0, 5.0, 2.0), PxVec3(2.0, 2.0, 2.0), 25);
	particleSystem->setUseGravity(true);
	generator->setDuration(2.0);
	generator->setProbability(0.5);
	particleSystem->addGenerator(generator);

	// Se ve afectado por el viento
	particleSystem->addForceGenerator(_wind);
}

void Scene0::createPlayer()
{
	_playerParticle = new Particle(PxVec3(0.0, 1.0, 80.0), PxVec3(0.0, 0.0, 0.0),
		Vector4(1.0, 0.0, 0.0, 1.0), PxVec3(0.0, 0.0, 0.0), 10.0, 0.999, 500.0, 1.0);
	_playerParticle->setActive(true);
	_player = new ParticleSystem();
	_player->addParticle(_playerParticle);

	// Se ve afectado por la gravedad
	_player->addForceGenerator(_gravity);
}

void Scene0::createEnemy(PxVec3 position, RenderItem*& render)
{
	//Creamos la geometria del plano
	PxGeometry* box = new PxBoxGeometry(10 / 2, 10 / 2, 10 / 2);
	PxShape* boxG = CreateShape(*box, gMaterial);
	//Creamos el transform, y el color
	PxTransform* tr3 = new PxTransform(position);
	Vector4* color3 = new Vector4{ 0.0, 1.0, 1.0, 1.0 };
	//Renderizamos la base
	render = new RenderItem(boxG, tr3, *color3);
	//La registramos
	RegisterRenderItem(render);
}

void Scene0::enemyShoot(int index, PxVec3 position, PxVec3 direction, double t)
{
	//Aumenta el tiempo actual
	_enemyShootTimer[index] += t;

	//Cuando se ha cumplido el cooldown
	if (_enemyShootTimer[index] >= _enemyShootCooldown[index])
	{
		//Dispara
		shootEnemyCanon(Proyectil::ProyectilType::Bullet, position, direction);
		//Reinicia el contador
		_enemyShootTimer[index] = 0.0;
	}
}

void Scene0::createCollectables(SolidSystem*& sSystem, PxVec3 position)
{
	sSystem = new SolidSystem(gPhysics, gScene);

	// ----- GENERADOR DE ESFERAS -----
	SolidGenerator* sphereGen = new SolidGenerator(gPhysics);
	sphereGen->setPosition(position);
	sphereGen->setShape(SolidShape::SPHERE);
	sphereGen->setMaterial(SolidMaterialType::RUBBER);
	sphereGen->setSpawnTime(7.5f);
	sphereGen->setDuration(5.0f);

	sSystem->addGenerator(sphereGen);
}

void Scene0::checkCollectables(SolidSystem* sSystem)
{
	//Sin sistema no podemos trabajar
	if (!sSystem) return;

	//Cogemos los actores
	const std::vector<SolidData>& solids = sSystem->getSolids();

	for (const SolidData& s : solids)
	{
		PxRigidDynamic* collectable = s.solid;
		//Si no hay, no hacemos nada
		if (!collectable) continue;

		//Comprobamos colisiones
		if (checkCollisionWithCollectables(_playerParticle, collectable))
		{
			//Sumamos puntos
			_points += 100;

			//Mensaje por consola
			std::cout << "Collectable picked! Points: " << _points << ". You need " << _goalPoints - _points << " to win."  << std::endl;

			//Lo borramos quitandole su duracion
			const_cast<SolidData&>(s).duration = 0.0;

			break; 
		}
	}
}

void Scene0::checkBulletCollectables(SolidSystem* sSystem)
{
	//Sin sistema no podemos trabajar
	if (!sSystem) return;

	//Cogemos los actores
	const std::vector<SolidData>& solids = sSystem->getSolids();

	//Miramos las balas del player
	for (Proyectil* bullet : _proyectils)
	{
		//Si no esta activa, no hacemos nada
		if (!bullet->isActive()) continue;

		for (const SolidData& s : solids)
		{
			PxRigidDynamic* collectable = s.solid;
			//Si no hay, no hacemos nada
			if (!collectable) continue;


			//Comprobamos colisiones
			if (checkCollisionBulletCollectables(bullet, collectable))
			{
				// Desactivar bala
				bullet->setActive(false);

				// Sumamos puntos
				_points += 200;

				//Mensaje por consola
				std::cout << "Collectable destroyed by bullet! Points: " << _points << ". You need " << _goalPoints - _points << " to win." << std::endl;

				// Marcar recolectable como muerto
				const_cast<SolidData&>(s).duration = 0.0;

				return;
			}
		}
	}
}

void Scene0::createRain()
{
	_rain = new ParticleSystem();
	_rainGen = new UniformParticleGenerator(PxVec3(0, 150, 0), 100,
		PxVec3(-150, -150, -150), PxVec3(150, 0, 150),
		PxVec3(-0.3, -0.3, -0.3), PxVec3(0.3, 0.3, 0.3));
	_rain->setUseGravity(true);
	_rainGen->setDuration(5.0);
	_rainGen->setProbability(0.9);
	_rain->addGenerator(_rainGen);

	// Se ve afectado por la gravedad
	_rain->addForceGenerator(_gravity);
	_rain->addForceGenerator(_wind);
}

//void Scene0::createFirework(const PxVec3& position, ParticleSystem*& particleSystem, UniformParticleGenerator*& generator, const Vector4& color, ExplosionForce*& force)
//{
//	particleSystem = new ParticleSystem();
//
//	// Generador de particulas
//	generator = new UniformParticleGenerator(position, 50, PxVec3(-2, -2, -2), PxVec3(2, 2, 2), PxVec3(-10, -10, -10), PxVec3(10, 10, 10), color);
//	particleSystem->setUseGravity(true);
//	generator->setDuration(5.0);
//	generator->setProbability(1.0);
//	particleSystem->addGenerator(generator);
//
//	particleSystem->addForceGenerator(force);
//}