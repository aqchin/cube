#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Camera.h"
#include <vector>

using namespace std;

class Window	  // OpenGL output window related routines
{
  private:
	static void drawHouse();
	static void drawBunny();
	static void drawDragon();

  public:
    static int width, height; 	            // window size
	static Camera c0, c1, c2;

    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	
	static void processSpecialKeys(int, int, int);
	static void processNormalKeys(unsigned char, int, int);
};

#endif

