#include "FloatingForce.h"

FloatingForce::FloatingForce(float waterHeight, float height, float volume, float liquidDensity)
    : _waterHeight(waterHeight), _height(height), _volume(volume), _liquidDensity(liquidDensity)
{
}

void FloatingForce::updateForce(Particle* p, double t)
{
    //Si no hay particula a la que aplicarlo, no hace nada
    if (!p || !p->isActive()) return;

    //Posicion en y
    float y = p->getPos().y;
    //Mitad de la altura
    float halfH = _height * 0.5f;

    //Parte inferior del cubo
    float bottom = y - halfH;
    //Parte superior del cubo
    float top = y + halfH;

    //Altura del agua
    float h = _waterHeight;

    //Porcentaje de inmersion
    float immersed = 0.0f;

    // Completamente fuera por arriba
    if (bottom >= h) {
        immersed = 0.0f;
    }
    // Completamente sumergido
    else if (top <= h) {
        immersed = 1.0f;
    }
    // Parcialmente sumergido
    else {
        // Parte sumergida del cubo
        float submergedHeight = h - bottom;   
        immersed = submergedHeight / _height; 
    }

    //Limites por si acaso
    if (immersed < 0.0f) immersed = 0.0f;
    if (immersed > 1.0f) immersed = 1.0f;

    // Empuje hacia arriba
    PxVec3 f(0, 0, 0);
    f.y = _liquidDensity * _volume * immersed * 9.8f;

    p->addForce(f);
}
