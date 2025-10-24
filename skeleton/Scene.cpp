#include "Scene.h"
#include <iostream>
#include "ParticleForceRegister.h"

void Scene::init()
{
	//// allocate memory and load resources
	//// Lights
	//// Textures

	//// Graphics objects (entities) of the scene
}

void Scene::update()
{

}

Scene::~Scene()
{
	destroy();
}

void
Scene::destroy()
{ // release memory and resources

	//for (Abs_Entity* el : gObjects)
	//	delete el;

	//gObjects.clear();
}

// Para borrar las cosas al cambiar de una escena a otra (ponerla en blanco otra vez).
void Scene::reset()
{
	destroy(); // libera memoria.
	init();
}

// --- ESCENAS HIJAS ---
// Scene0, Scene1, Scene2 ... 

// ---- SCENE 0 ----
void Scene0::init()
{
	Scene::init();

}

// ---- SCENE 1 ----
void Scene1::init()
{
	// -- llama a init del padre
	Scene::init();

}

// ---- SCENE 2 ----
void Scene2::init()
{
	// -- llama a init del padre
	Scene::init();

}