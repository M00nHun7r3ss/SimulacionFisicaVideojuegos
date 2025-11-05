#include "SceneManager.h"

SceneManager::~SceneManager()
{
    //Limpia todo
    cleanup();
}

void SceneManager::addScene(Scene* s)
{
    //Aniade escena al vector
    _scenes.push_back(s);
}

void SceneManager::setActive(int index)
{
    //Cambia la escena actual
    if (index >= 0 && index < _scenes.size()) {
        //Quita la de ahora, si la hay
        if (_activeScene != nullptr) 
        {
            _activeScene->exitScene();
        }
        //Pone la nueva
        _activeScene = _scenes[index];
        //Inicializa la nueva
        _activeScene->enterScene();
    }
}

void SceneManager::update(double t)
{
    //Actualiza la escena
    if (_activeScene != nullptr) 
    {
        _activeScene->update(t);
    }
}

void SceneManager::cleanup()
{
    //Borra las escenas del vector
    for (Scene* s : _scenes)
    {
        //Si hay escena
        if (s != nullptr)
        {
            //Limpia 
            s->cleanup();
            //Borra
            delete s;
        }
    }

    //Vacía el vector de escneas
    _scenes.clear();
    //La actual pasa a ser nula
    _activeScene = nullptr;
}
