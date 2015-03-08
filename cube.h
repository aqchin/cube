#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"
#include "Vector3.h"

class Cube
{
  protected:
    Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)
    double angle;                   // rotation angle [degrees]

  public:
	Vector3 *v;
    Cube();   // Constructor
    Matrix4& getMatrix();
    void spin(double);      // spin cube [degrees]

	void setAngle(double);
};

#endif

