#pragma once

#include <vector>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene(); 

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init();
	virtual void update();

	//void render(Camera const& cam) const;

protected:
	void destroy();

	void reset();

};

// --- ESCENAS HIJAS ---
// Scene0, Scene1, Scene2 ...

//Practica 0
class Scene0 : public Scene
{
public:
	Scene0() = default;
	void init() override;
};

//Practica 1
class Scene1 : public Scene
{
public:
	Scene1() = default;
	void init() override;
};

//Practica 2
class Scene2 : public Scene
{
public:
	Scene2() = default;
	void init() override;
};


