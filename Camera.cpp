#include "Camera.h"

Camera::Camera()
{
	this->e = (*new Vector3());
	this->d = (*new Vector3());
	this->up = (*new Vector3());

	this->C = (*new Matrix4());
	C.identity();
	C.setM4cm(*new Vector3(), *new Vector3(), *new Vector3(), e);
}

Camera::Camera(Vector3 e, Vector3 d, Vector3 up) {
	this->e = e;
	this->d = d;
	this->up = up;
	
	Vector3 z = e - d; // z = (e - d) / ||e - d||
	z.normalize();

	Vector3 x = x.cross(up, z); // z = (up X z) / ||up X z||
	x.normalize();

	Vector3 y = y.cross(z, x); // y = (z X x) / ||z X x||
	y.normalize();

	this->C = (*new Matrix4());
	this->C.setM4cm(x, y, z, e);
}

Camera::~Camera()
{
}

GLdouble* Camera::getGLMatrix() {
	return (this->C.getPointer());
}