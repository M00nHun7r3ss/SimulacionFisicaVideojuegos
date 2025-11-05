#include "Scene.h"
#include <iostream>

// --- ESCENAS HIJAS ---
// Scene0, Scene1, Scene2 ... 

Scene0::Scene0(PxMaterial* material) : Scene(), gMaterial(material)
{}

// ---- SCENE 0 ----
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
		{
			if (p->getRenderItem() != nullptr)
			{
				DeregisterRenderItem(p->getRenderItem());
				delete p;
			}
		}
	}
	proyectils.clear();

#pragma endregion
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
	//WindForce* advancedWind = new WindForce(PxVec3(5.0, 0.0, 0.0), 1.2, 0.5, 0.1,
	//	PxVec3(-10, 0, -10), PxVec3(10, 10, 10));
	//fogSystem->addForceGenerator(advancedWind);

	////PRACTICA 3 - FUERZAS DE VIENTO - TORBELLINO
	WhirlwindForce* whirlwind = new WhirlwindForce(PxVec3(0.0, 5.0, 0.0), 0.9,
		15.0, 1.2, 0.5, 0.2);
	fogSystem->addForceGenerator(whirlwind);

	////Fuego - Gaussiano
	//fireSystem = new ParticleSystem();
	//fireGenerator = new GaussParticleGenerator(PxVec3(0.0, 0.0, 0.0), PxVec3(0.0, 5.0, 0.0), PxVec3(1.0, 1.0, 1.0), 10);
	////fireSystem->setUseGravity(false);
	//fireGenerator->setProbability(0.8);
	//fireSystem->addGenerator(fireGenerator);
	////PRACTICA 3 - FUERZAS DE GRAVEDAD, PERO INVERSA
	//GravityForce* inverseGravity = new GravityForce(0.2, PxVec3(0, -500, 0));
	//fireSystem->addForceGenerator(inverseGravity);

}

void Scene2::update(double t)
{
	//Actualizamos el sistema
	//hoseSystem->update(t);
	fogSystem->update(t);
	//fireSystem->update(t);
}

void Scene2::cleanup()
{
	//Los borra
	//delete hoseSystem;
	//hoseSystem = nullptr;
	delete fogSystem;
	fogSystem = nullptr;
	//delete fireSystem;
	//fireSystem = nullptr;
}

// ---- SCENE 3 - PRACTICA INTERMEDIA ----
Scene3::Scene3(PxMaterial* material) : gMaterial(material)
{}

void Scene3::init()
{

	//Plano base del nivel
	//Creamos la geometria del plano
	PxGeometry* boxGeo = new PxBoxGeometry(50 / 2, 5 / 2, 50 / 2);
	//Creamos la forma con la geometria
	PxShape* box = CreateShape(*boxGeo, gMaterial);
	//Creamos el transform, y el color
	Vector3D pos(50.0, 40.0, -20.0);
	PxTransform* tr = new PxTransform(PxVec3(pos.getX(), pos.getY(), pos.getZ()));
	Vector4* color = new Vector4{ 1.0, 1.0, 1.0, 1.0 };
	//Renderizamos la base
	base1 = new RenderItem(box, tr, *color);
	//La registramos
	RegisterRenderItem(base1);

}

void Scene3::update(double t)
{
}

void Scene3::cleanup()
{
}
