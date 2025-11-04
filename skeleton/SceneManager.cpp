#include "SceneManager.h"

SceneManager::~SceneManager()
{
    //Borra las escenas del vector
    for (Scene* s : scenes) 
    {
        delete s;
    }
}

void SceneManager::addScene(Scene* s)
{
    //Aniade escena al vector
    scenes.push_back(s);
}

void SceneManager::setActive(int index)
{
    //Cambia la escena actual
    if (index >= 0 && index < scenes.size()) {
        //Quita la de ahora, si la hay
        if (activeScene != nullptr) 
        {
            activeScene->cleanup();
        }
        //Pone la nueva
        activeScene = scenes[index];
        //Inicializa la nueva
        activeScene->init();
    }
}

void SceneManager::update(double t)
{
    //Actualiza la escena
    if (activeScene != nullptr) 
    {
        activeScene->update(t);
    }
}

void SceneManager::cleanup()
{
    //Limpia la escena
    if (activeScene != nullptr)
    {
        activeScene->cleanup();
    }
}
