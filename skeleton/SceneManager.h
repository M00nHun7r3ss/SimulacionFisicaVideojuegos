#pragma once
#include <vector>
#include "Scene.h"

class SceneManager {
public:

    //Constructora
    SceneManager() {}

    //Destructora
    ~SceneManager();

    //Aniade escena al vector de escenas
    void addScene(Scene* s);

    //actualiza escena actual
    void update(double t);

    //limpia escena actual
    void cleanup();

    //Getters
    inline Scene* getActiveScene() { return _activeScene; }

    //Setters
    //Activa escena concreta
    void setActive(int index);

private:
    //vector general
    std::vector<Scene*> _scenes;
    //escena actual
    Scene* _activeScene = nullptr;
};