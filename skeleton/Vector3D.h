#include <vector> //para el vector en si
#include <iostream> //input output consola 
#include <cmath> //operaciones matematicas

class Vector3D
{
public:

	//Constructora vacia
	Vector3D();

	//Constructora con valores
	Vector3D(double x, double y, double z);

	//Modulo + normalizar
	double modulo();

	//Operador =
	Vector3D operator= (const Vector3D newV);

	//Operador +
	Vector3D operator+ (const Vector3D v1);

	//Operador -
	Vector3D operator- (const Vector3D v1);

	//Operador * (Producto vectorial)
	Vector3D operator* (const Vector3D v1);

	//Producto escalar
	double productoEscalar (const Vector3D v1);

	//Producto vector por escalar
	Vector3D productoEscalarVector(double escalar);

	//Getters
	double getX();
	double getY();
	double getZ();

	//Setters
	void setX(double x);
	void setY(double y);
	void setZ(double z);

private:

	double _x, _y, _z;


};