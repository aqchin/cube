#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Animals.h"
#include "main.h"
#include <math.h>

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
double static rotato = 0.01;

Animals a = (*new Animals()); // parse bunny and dragon
vector<Vector3> bun = a.getBunny();
vector<Vector3> drag = a.getDragon();
vector<Vector3> bunv = a.getBunnyNorm();
vector<Vector3> dragv = a.getDragonNorm();

Camera Window::c0 = (*new Camera());

Camera Window::c1 = (*new Camera(*new Vector3(0, 10, 10), 
	*new Vector3(0, 0, 0), *new Vector3(0, 1, 0)));

Camera Window::c2 = (*new Camera(*new Vector3(-15, 5, 10), 
	*new Vector3(-5, 0, 0), *new Vector3(0, 1, 0.5)));

Camera camera;
int mode = 0; // 0 = cube, 1 = house, 2 = bunny, 3 = dragon

// This data structure defines a simple house

int nVerts = 42;    // your vertex array needs to have this many entries

// These are the x,y,z coordinates of the vertices of the triangles
float vertices[] = {
            -4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face
            -4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4, // left face
            4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,  // back face
            4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,     // right face
            4,4,4, 4,4,-4, -4,4,-4, -4,4,4,     // top face
            -4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4, // bottom face

            -20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20, // grass
            -4,4,4, 4,4,4, 0,8,4,                       // front attic wall
            4,4,4, 4,4,-4, 0,8,-4, 0,8,4,               // left slope
            -4,4,4, 0,8,4, 0,8,-4, -4,4,-4,             // right slope
            4,4,-4, -4,4,-4, 0,8,-4};                   // rear attic wall

// These are the RGB colors corresponding to the vertices, in the same order
float colors[] = {
            1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front is red
            0,1,0, 0,1,0, 0,1,0, 0,1,0,  // left is green
            1,0,0, 1,0,0, 1,0,0, 1,0,0,  // back is red
            0,1,0, 0,1,0, 0,1,0, 0,1,0,  // right is green
            0,0,1, 0,0,1, 0,0,1, 0,0,1,  // top is blue
            0,0,1, 0,0,1, 0,0,1, 0,0,1,  // bottom is blue
  
            0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0, // grass is dark green
            0,0,1, 0,0,1, 0,0,1,                // front attic wall is blue
            1,0,0, 1,0,0, 1,0,0, 1,0,0,         // left slope is green
            0,1,0, 0,1,0, 0,1,0, 0,1,0,         // right slope is red
            0,0,1, 0,0,1, 0,0,1,};              // rear attic wall is red

// The index data stores the connectivity of the triangles; 
// index 0 refers to the first triangle defined above
int indices[] = {
            0,2,3,    0,1,2,      // front face
            4,6,7,    4,5,6,      // left face
            8,10,11,  8,9,10,     // back face
            12,14,15, 12,13,14,   // right face
            16,18,19, 16,17,18,   // top face
            20,22,23, 20,21,22,   // bottom face
                   
            24,26,27, 24,25,26,   // grass
            28,29,30,             // front attic wall
            31,33,34, 31,32,33,   // left slope
            35,37,38, 35,36,37,   // right slope
            39,40,41};            // rear attic wall

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
  Globals::cube.spin(rotato);   // rotate cube; if it spins too fast try smaller values and vice versa
  displayCallback();         // call display routine to show the cube
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

  // Smooth
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

  // Tell OpenGL what ModelView matrix to use:
  Matrix4 glmatrix;
  glmatrix = Globals::cube.getMatrix();
  glmatrix.transpose();
  //Matrix4 *m;

  switch (mode) {
  case (0) :
	  glEnable(GL_LIGHTING);
	  glLoadMatrixd(glmatrix.getPointer());

	  // Draw all six faces of the cube:
	  glBegin(GL_QUADS);
	  glColor3f(0.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue. 
	  // To change the color of the other faces you will need to repeat this call before each face is drawn.
	  // Draw front face:
	  glNormal3f(0.0, 0.0, 1.0);
	  glVertex3f(-5.0, 5.0, 5.0);
	  glVertex3f(5.0, 5.0, 5.0);
	  glVertex3f(5.0, -5.0, 5.0);
	  glVertex3f(-5.0, -5.0, 5.0);

	  // Draw left side:
	  glNormal3f(-1.0, 0.0, 0.0);
	  glVertex3f(-5.0, 5.0, 5.0);
	  glVertex3f(-5.0, 5.0, -5.0);
	  glVertex3f(-5.0, -5.0, -5.0);
	  glVertex3f(-5.0, -5.0, 5.0);

	  // Draw right side:
	  glNormal3f(1.0, 0.0, 0.0);
	  glVertex3f(5.0, 5.0, 5.0);
	  glVertex3f(5.0, 5.0, -5.0);
	  glVertex3f(5.0, -5.0, -5.0);
	  glVertex3f(5.0, -5.0, 5.0);

	  // Draw back face:
	  glNormal3f(0.0, 0.0, -1.0);
	  glVertex3f(-5.0, 5.0, -5.0);
	  glVertex3f(5.0, 5.0, -5.0);
	  glVertex3f(5.0, -5.0, -5.0);
	  glVertex3f(-5.0, -5.0, -5.0);

	  // Draw top side:
	  glNormal3f(0.0, 1.0, 0.0);
	  glVertex3f(-5.0, 5.0, 5.0);
	  glVertex3f(5.0, 5.0, 5.0);
	  glVertex3f(5.0, 5.0, -5.0);
	  glVertex3f(-5.0, 5.0, -5.0);

	  // Draw bottom side:
	  glNormal3f(0.0, -1.0, 0.0);
	  glVertex3f(-5.0, -5.0, -5.0);
	  glVertex3f(5.0, -5.0, -5.0);
	  glVertex3f(5.0, -5.0, 5.0);
	  glVertex3f(-5.0, -5.0, 5.0);
	  glEnd();
	  break;
	case (1) :
	  glDisable(GL_LIGHTING);
	  glLoadMatrixd(camera.getGLMatrix());
	  drawHouse();
	  break;
	case (2) :
	  glDisable(GL_LIGHTING);
	  glLoadMatrixd(glmatrix.getPointer());
	  drawBunny();
	  break;
	case (3) :
	  glDisable(GL_LIGHTING);
	  glLoadMatrixd(glmatrix.getPointer());
	  drawDragon();
	  break;
  }
  
  glFlush();  
  glutSwapBuffers();
}

void Window::processSpecialKeys(int k, int x, int y) {
	Matrix4 *m = new Matrix4();
	switch (k) {
		case GLUT_KEY_F1:
			if (mode != 0) {
				Globals::cube.getMatrix().identity();
				Globals::cube.setAngle(0.0);
			}
			camera = c0;
			mode = 0;
			rotato = 0.01;
			break;
		case GLUT_KEY_F2:
			camera = c1;
			mode = 1;
			break;
		case GLUT_KEY_F3:
			camera = c2;
			mode = 1;
			break;
		case GLUT_KEY_F4:
			if (mode != 2) {
				Globals::cube.getMatrix().identity();
				Globals::cube.setAngle(0.0);
				double s = 36 * tan(M_PI /6) /
					(a.getLargeBunny().getX() - a.getSmallBunny().getX());
				double x = -(a.getLargeBunny().getX() + a.getSmallBunny().getX()) / 2;
				double y = -(a.getLargeBunny().getY() + a.getSmallBunny().getY()) / 2;
				double z = -(a.getLargeBunny().getZ() + a.getSmallBunny().getZ()) / 2;
				m->makeTranslate(x, y, z);
				m->print("Bunny - Translation matrix: ");
				Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
				m->makeScale(s, s, s);
				m->print("Bunny - Scalar matrix: ");
				Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
			}
			camera = c0;
			mode = 2;
			rotato = 0.5;
			break;
		case GLUT_KEY_F5:
			if (mode != 3) {
				Globals::cube.getMatrix().identity();
				Globals::cube.setAngle(0.0);
				double s = 40 * tan(M_PI / 6) /
					(a.getLargeDragon().getX() - a.getSmallDragon().getX());
				double x = -(a.getLargeBunny().getX() + a.getSmallBunny().getX()) / 2;
				double y = -(a.getLargeBunny().getY() + a.getSmallBunny().getY()) / 2;
				double z = -(a.getLargeBunny().getZ() + a.getSmallBunny().getZ()) / 2;
				m->makeTranslate(x, y, z);
				m->print("Bunny - Translation matrix: ");
				Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
				m->makeScale(s, s, s);
				m->print("Bunny - Scalar matrix: ");
				Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
			}
			camera = c0;
			mode = 3;
			rotato = 0.5;
			break;
	}
}

void Window::processNormalKeys(unsigned char k, int x, int y) {
	Matrix4 *m = new Matrix4();
	Vector3 *v = new Vector3(0, 0, 1);
	switch (k) {
		case 't':
			rotato = -rotato;
			break;
		case 'x':
			m->makeTranslate(-1, 0, 0);
			Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
			break;
		case 'X':
			m->makeTranslate(1, 0, 0);
			Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
			break;
		case 'y':
			m->makeTranslate(0, -1, 0);
			Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
			break;
		case 'Y':
			m->makeTranslate(0, 1, 0);
			Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
			break;
		case 'z':
			m->makeTranslate(0, 0, -1);
			Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
			break;
		case 'Z':
			m->makeTranslate(0, 0, 1);
			Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
			break;
		case 'r':
			if (mode == 0) {
				Globals::cube.getMatrix().identity();
				Globals::cube.setAngle(0.0);
			}
			else if (mode == 2) {
				Globals::cube.getMatrix().identity();
				Globals::cube.setAngle(0.0);
				double s = 36 * tan(M_PI / 6) /
					(a.getLargeBunny().getX() - a.getSmallBunny().getX());
				double x = -(a.getLargeBunny().getX() + a.getSmallBunny().getX()) / 2;
				double y = -(a.getLargeBunny().getY() + a.getSmallBunny().getY()) / 2;
				double z = -(a.getLargeBunny().getZ() + a.getSmallBunny().getZ()) / 2;
				m->makeTranslate(x, y, z);
				m->print("Bunny - Translation matrix: ");
				Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
				m->makeScale(s, s, s);
				m->print("Bunny - Scalar matrix: ");
				Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
			}
			else if (mode == 3) {
				Globals::cube.getMatrix().identity();
				Globals::cube.setAngle(0.0);
				double s = 40 * tan(M_PI / 6) /
					(a.getLargeDragon().getX() - a.getSmallDragon().getX());
				double x = -(a.getLargeBunny().getX() + a.getSmallBunny().getX()) / 2;
				double y = -(a.getLargeBunny().getY() + a.getSmallBunny().getY()) / 2;
				double z = -(a.getLargeBunny().getZ() + a.getSmallBunny().getZ()) / 2;
				m->makeTranslate(x, y, z);
				m->print("Bunny - Translation matrix: ");
				Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
				m->makeScale(s, s, s);
				m->print("Bunny - Scalar matrix: ");
				Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
			}
			break;
		case 'O':
			m->makeRotate(-10, *v);
			Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
			break;
		case 'o':
			m->makeRotate(10, *v);
			Globals::cube.getMatrix() = Globals::cube.getMatrix() * (*m);
			break;
		case 's':
			m->makeScale(0.9, 0.9, 0.9);
			Globals::cube.getMatrix() = (*m) * Globals::cube.getMatrix();
			break;
		case 'S':
			m->makeScale(1.1, 1.1, 1.1);
			Globals::cube.getMatrix() = (*m) * Globals::cube.getMatrix();
			break;
		case 'p':
			a.getSmallBunny().print("Bunny - Smallest X, Y, Z values: ");
			a.getLargeBunny().print("Bunny - Largest X, Y, Z values: ");
			a.getSmallDragon().print("Dragon - Smallest X, Y, Z values: ");
			a.getLargeDragon().print("Dragon - Largest X, Y, Z values: ");
			break;
	}
	Globals::cube.getMatrix().getV3().print("Cube position: ");
}

void Window::drawHouse() {
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 60; i++) {
		glColor3f(colors[indices[i]*3],
			colors[indices[i]*3 +1], colors[indices[i]*3 +2]);
		glVertex3f(vertices[indices[i]*3],
			vertices[indices[i]*3 +1], vertices[indices[i]*3 +2]);
	}
	glEnd();
}

void Window::drawBunny() {
	glBegin(GL_POINTS);
	for (unsigned int i = 0; i < bun.size(); i++) {
		glNormal3d(bunv[i].getX(), bunv[i].getY(), bunv[i].getZ());
		glVertex3d(bun[i].getX(), bun[i].getY(), bun[i].getZ());
	}
	glEnd();
}

void Window::drawDragon() {
	glBegin(GL_POINTS);
	for (unsigned int i = 0; i < drag.size(); i++) {
		glNormal3d(dragv[i].getX(), dragv[i].getY(), dragv[i].getZ());
		glVertex3d(drag[i].getX(), drag[i].getY(), drag[i].getZ());
	}
	glEnd();
}