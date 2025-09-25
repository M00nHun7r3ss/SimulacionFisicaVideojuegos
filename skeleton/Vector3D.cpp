#include "Vector3D.h"

//Constructora vacia
Vector3D::Vector3D() : _x(0), _y(0), _z(0) {}

//Constructora con valores
Vector3D::Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z) {}

//Modulo + normalizar
double Vector3D::modulo()
{
	//Devolvemos modulo
	double m = std::sqrt(_x * _x + _y * _y + _z * _z);

	//Normalizamos
	_x /= m;
	_y /= m;
	_z /= m;

	return m;
}

//Operador =
Vector3D Vector3D::operator=(const Vector3D newV)
{
	//Asignamos los valores nuevos
	_x = newV._x;
	_y = newV._y;
	_z = newV._z;

	return *this;
}

//Operador +
Vector3D Vector3D::operator+(const Vector3D v1)
{
	//Sumamos
	_x += v1._x;
	_y += v1._y;
	_z += v1._z;

	return *this;
}

//Operador -
Vector3D Vector3D::operator-(const Vector3D v1)
{
	//Restamos
	_x -= v1._x;
	_y -= v1._y;
	_z -= v1._z;

	return *this;
}

//Operador * (Producto vectorial)
Vector3D Vector3D::operator*(const Vector3D v1)
{
	//Producto vectorial
	/*
		Truco
	 
				x	y	z
		V1		a	b	c
		V2		d	e	f

		Resultado = (b*f - e*c, a*f - d*c, a*e - d*b);
	 */

	Vector3D resultado;

	resultado.setX(_y * v1._z - v1._y * _z);
	resultado.setY(_x * v1._z - v1._x * _z);
	resultado.setZ(_x * v1._y - v1._x * _y);

	return resultado;
}

//Producto escalar
double Vector3D::productoEscalar(const Vector3D v1)
{
	//Multiplicamos y sumamos todas las componentes
	return _x * v1._x + _y * v1._y + _z * v1._z;
}

Vector3D Vector3D::productoEscalarVector(double escalar)
{
	//Multiplicamos cada componente por el escalar
	_x *= escalar;
	_y *= escalar;
	_z *= escalar;

	return *this;
}

double Vector3D::getX()
{
	return _x;
}

double Vector3D::getY()
{
	return _y;
}

double Vector3D::getZ()
{
	return _y;
}

void Vector3D::setX(double x)
{
	_x = x;
}

void Vector3D::setY(double y)
{
	_y = y;
}

void Vector3D::setZ(double z)
{
	_z = z;
}

